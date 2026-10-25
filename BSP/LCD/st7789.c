/**
 * @file st7789.c
 * @brief ST7789 刷屏实现, 分块 DMA + 信号量等待
 * @note  零拷贝, 像素按 RGB565_SWAPPED 字节序直接送 DMA
 */

#include "st7789.h"

#include "FreeRTOS.h"   /* portMAX_DELAY */
#include "semphr.h"     /* 二值信号量 */

/* ---------- 引脚 ---------- */
#define CS_LOW() HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET)
#define CS_HIGH() HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET)
#define DC_CMD() HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET)
#define DC_DATA() HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET)
#define RST_LOW() HAL_GPIO_WritePin(LCD_RESET_PORT, LCD_RESET_PIN, GPIO_PIN_RESET)
#define RST_HIGH() HAL_GPIO_WritePin(LCD_RESET_PORT, LCD_RESET_PIN, GPIO_PIN_SET)

/* ---------- ST7789 命令 ---------- */
#define CMD_SWRESET 0x01
#define CMD_SLPOUT  0x11
#define CMD_INVON   0x21
#define CMD_DISPON  0x29
#define CMD_CASET   0x2A
#define CMD_RASET   0x2B
#define CMD_RAMWR   0x2C
#define CMD_MADCTL  0x36
#define CMD_COLMOD  0x3A

/* ---------- 时序 ---------- */
#define RESET_LOW_MS 100U        /* RESX 拉低时长 */
#define RESET_HIGH_MS 150U       /* 释放后等待, 手册要求 >= 120ms */
#define SPI_BYTE_TIMEOUT_MS 10U  /* 单字节发送超时, 仅用于命令和参数 */

/* 格式: 命令, 参数个数, 参数...; 结束标记 0x00, 0xFF
 * SLPOUT 必须第一, INVON 须在 DISPON 前; 0xB7/0xBB/0xC3 电压勿改 */
static const uint8_t init_cmds[] = {
    CMD_SLPOUT, 0,                                       /* 出睡眠, 必须第一, 等 120ms */
    CMD_MADCTL, 1, ST7789_MADCTL,                        /* 显存方向, 横屏 0x60 */
    CMD_COLMOD, 1, 0x55,                                 /* 16bit RGB565 */
    0xB2, 5, 0x0C, 0x0C, 0x00, 0x33, 0x33,               /* Porch 控制 */
    0xB7, 1, 0x35,                                       /* 栅极控制 VGH/VGL */
    0xBB, 1, 0x19,                                       /* VCOM */
    0xC0, 1, 0x2C,                                       /* 电源控制 */
    0xC2, 1, 0x01,                                       /* VDV/VRH 使能 */
    0xC3, 1, 0x12,                                       /* VRH 电压 */
    0xC4, 1, 0x20,                                       /* VDV 电压 */
    0xC6, 1, 0x0F,                                       /* 帧率控制 */
    0xD0, 2, 0xA4, 0xA1,                                 /* 电源控制 1 */
    0xE0, 14, 0xD0, 0x04, 0x0D, 0x11, 0x13, 0x2B, 0x3F,
              0x54, 0x4C, 0x18, 0x0D, 0x0B, 0x1F, 0x23,  /* 正极性伽马 */
    0xE1, 14, 0xD0, 0x04, 0x0C, 0x11, 0x13, 0x2C, 0x3F,
              0x44, 0x51, 0x2F, 0x1F, 0x1F, 0x20, 0x23,  /* 负极性伽马 */
    CMD_INVON, 0,                                        /* 反色, 不开则颜色成底片 */
    CMD_DISPON, 0,                                       /* 开显示, 等 20ms */
    0x00, 0xFF                                           /* 结束标记 */
};

/* ---------- 内部状态 ---------- */
static volatile uint32_t flush_cnt = 0;     /* 成功刷屏次数, 任务写 ui 读 */
static volatile uint32_t err_cnt = 0;       /* 出错次数, 中断写 ui 读 */

static uint16_t dma_buffer[ST7789_DMA_BUF_PIXELS];  /* 清屏铺同色用的缓冲 */

/* ---------- 底层: 命令 / 窗口 ---------- */

/**
 * @brief  写一条命令及其参数
 * @param  cmd 命令字
 * @param  data 参数指针, length 为 0 时可为 NULL
 * @param  length 参数字节数
 *         命令和参数由 DC 区分, CS 包住整条事务
 */
static void ST7789_WriteReg(uint8_t cmd, const uint8_t *data, uint16_t length)
{
    CS_LOW();                               /* CS 包住整条事务 */
    DC_CMD();                               /* 命令/参数靠 DC 区分 */
    HAL_SPI_Transmit(&ST7789_SPI, &cmd, 1, SPI_BYTE_TIMEOUT_MS);

    if(length != 0U && data != NULL) {
        DC_DATA();
        HAL_SPI_Transmit(&ST7789_SPI, (uint8_t *)data, length, SPI_BYTE_TIMEOUT_MS);
    }
    CS_HIGH();
}

/**
 * @brief  设地址窗口并准备接收像素
 * @param  x1,y1 窗口左上角
 * @param  x2,y2 窗口右下角
 *         返回时 CS 为低, DC 已切到数据模式
 */
static void ST7789_SetRangeAndPrepareGram(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    const uint8_t caset[4] = { (uint8_t)(x1 >> 8), (uint8_t)x1,
                               (uint8_t)(x2 >> 8), (uint8_t)x2 };
    const uint8_t raset[4] = { (uint8_t)(y1 >> 8), (uint8_t)y1,
                               (uint8_t)(y2 >> 8), (uint8_t)y2 };
    uint8_t ramwr = CMD_RAMWR;

    ST7789_WriteReg(CMD_CASET, caset, 4);
    ST7789_WriteReg(CMD_RASET, raset, 4);

    /* RAMWR 后接像素流, CS 从此必须保持低, 抬 CS 会断地址计数 */
    CS_LOW();
    DC_CMD();
    HAL_SPI_Transmit(&ST7789_SPI, &ramwr, 1, SPI_BYTE_TIMEOUT_MS);
    DC_DATA();
}

/* ---------- 像素流 ---------- */

/* 单次 DMA 上限: HAL 的 size 为 uint16_t 字节数, 即 16383 像素 */
#define ST7789_MAX_CHUNK_PIXELS \
    ((ST7789_DMA_BUF_PIXELS > 16383U) ? 16383U : ST7789_DMA_BUF_PIXELS)

/* DMA 完成信号量, 中断 give, 刷屏任务 take */
static SemaphoreHandle_t s_dma_done = NULL;

/**
 * @brief  刷一块矩形, 阻塞到发完
 * @param  x1,y1,x2,y2 区域, 越界自动裁剪
 * @param  px 像素数据, 返回前须一直有效
 * @param  count 像素个数, 小于窗口则少发
 * @retval 1 成功; 0 参数非法或中途出错
 *         只能在任务上下文调用
 */
uint8_t ST7789_FlushArea(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                         const uint16_t *px, uint32_t count)
{
    if(px == NULL || count == 0U) return 0U;

    if(x1 >= ST7789_WIDTH)  x1 = ST7789_WIDTH  - 1U;    /* 裁剪到屏幕内 */
    if(y1 >= ST7789_HEIGHT) y1 = ST7789_HEIGHT - 1U;
    if(x2 >= ST7789_WIDTH)  x2 = ST7789_WIDTH  - 1U;
    if(y2 >= ST7789_HEIGHT) y2 = ST7789_HEIGHT - 1U;
    if(x1 > x2 || y1 > y2) return 0U;

    uint32_t left = (uint32_t)(x2 - x1 + 1U) * (uint32_t)(y2 - y1 + 1U);
    if(count < left) left = count;
    if(left == 0U) return 0U;

    ST7789_SetRangeAndPrepareGram(x1, y1, x2, y2);

    while(left > 0U)
    {
        uint32_t chunk = (left > ST7789_MAX_CHUNK_PIXELS) ? ST7789_MAX_CHUNK_PIXELS : left;

        if(HAL_SPI_Transmit_DMA(&ST7789_SPI, (uint8_t *)px,
                                (uint16_t)(chunk * 2U)) != HAL_OK) {
            err_cnt++;
            CS_HIGH();                      /* 起不出去也要抬 CS */
            return 0U;
        }
        px   += chunk;
        left -= chunk;

        /* 等本块发完, 睡眠期间 CPU 让给 LVGL; 故意不设超时 */
        xSemaphoreTake(s_dma_done, portMAX_DELAY);
    }

    CS_HIGH();

    flush_cnt++;                            /* 整块发完才计数 */
    return 1U;
}

/* ---------- 初始化 ---------- */

/* 硬复位: RESX 拉低 100ms, 释放后等 150ms 再发命令 */
static void ST7789_Reset(void)
{
    CS_HIGH();
    DC_DATA();
    RST_LOW();
    HAL_Delay(RESET_LOW_MS);
    RST_HIGH();
    HAL_Delay(RESET_HIGH_MS);
}

/**
 * @brief  阻塞铺一块矩形
 * @param  x1,y1,x2,y2 区域, 越界直接裁剪
 * @param  color RGB565 颜色
 *         走阻塞 SPI, 供上电自检和清屏使用
 */
void ST7789_FillRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    if(x1 >= ST7789_WIDTH || y1 >= ST7789_HEIGHT) return;
    if(x2 >= ST7789_WIDTH)  x2 = ST7789_WIDTH - 1U;
    if(y2 >= ST7789_HEIGHT) y2 = ST7789_HEIGHT - 1U;
    if(x1 > x2 || y1 > y2) return;

    /* 面板要高字节在前, 这里手工交换一次 */
    uint16_t v = (uint16_t)((color >> 8) | (color << 8));
    uint32_t left = (uint32_t)(x2 - x1 + 1U) * (uint32_t)(y2 - y1 + 1U);

    for(uint32_t n = 0; n < ST7789_DMA_BUF_PIXELS; n++) {
        dma_buffer[n] = v;
    }

    ST7789_SetRangeAndPrepareGram(x1, y1, x2, y2);

    while(left > 0U) {
        uint32_t chunk = (left > ST7789_MAX_CHUNK_PIXELS) ? ST7789_MAX_CHUNK_PIXELS : left;
        if(HAL_SPI_Transmit(&ST7789_SPI, (uint8_t *)dma_buffer,
                            (uint16_t)(chunk * 2U), 100U) != HAL_OK) {
            break;                          /* 失败留给 LVGL 首帧覆盖 */
        }
        left -= chunk;
    }
    CS_HIGH();
}

/**
 * @brief  整屏铺一个颜色
 * @param  color RGB565 颜色
 */
void ST7789_FillScreen(uint16_t color)
{
    ST7789_FillRect(0, 0, ST7789_WIDTH - 1U, ST7789_HEIGHT - 1U, color);
}

/**
 * @brief  初始化面板, 幂等
 *         硬复位 → 下发初始化表 → 清屏; 须在 GPIO / SPI 初始化后调用
 */
void ST7789_Init(void)
{
    static uint8_t s_inited = 0;
    if(s_inited) return;

    /* 建了就一直用; 调度器起来前创建只是从堆里切一块 */
    s_dma_done = xSemaphoreCreateBinary();
    configASSERT(s_dma_done != NULL);

    uint32_t i = 0;

    ST7789_Reset();

    while(init_cmds[i + 1] != 0xFF) {
        uint8_t cmd = init_cmds[i];
        uint8_t len = init_cmds[i + 1];

        ST7789_WriteReg(cmd, &init_cmds[i + 2], len);
        i += 2U + len;

        if(cmd == CMD_SLPOUT) HAL_Delay(120);   /* 等振荡器稳定 */
        if(cmd == CMD_DISPON) HAL_Delay(20);    /* 等一帧 */
    }

    /* 上电清屏刷黑, 不要改颜色, 否则界面出来前会闪一下 */
    ST7789_FillScreen(ST7789_BLACK);

    s_inited = 1;
}

/* ---------- SPI 中断 ----------
 * HAL 全局回调只能定义一份, 新增 DMA SPI 设备时需合并判断 */

/**
 * @brief  SPI 发送完成回调
 * @param  hspi SPI 句柄
 *         中断内只用 FromISR 版本
 */
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
    BaseType_t yield = pdFALSE;

    if(hspi->Instance == ST7789_SPI.Instance) {
        xSemaphoreGiveFromISR(s_dma_done, &yield);
        portYIELD_FROM_ISR(yield);
    }
}

/**
 * @brief  SPI 出错回调
 * @param  hspi SPI 句柄
 *         出错时 HAL 不再派发 TxCplt, 这里必须照样放行一次
 */
void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
    BaseType_t yield = pdFALSE;

    if(hspi->Instance == ST7789_SPI.Instance) {
        err_cnt++;                          /* 屏上 E 计数 */
        xSemaphoreGiveFromISR(s_dma_done, &yield);
        portYIELD_FROM_ISR(yield);
    }
}

/* ---------- 查询 ---------- */

/**
 * @brief  读调试统计
 * @param  flush_cnt_out 成功刷屏次数, 不涨说明卡了
 * @param  err_cnt_out 出错累计
 */
void ST7789_GetStats(uint32_t *flush_cnt_out, uint32_t *err_cnt_out)
{
    if(flush_cnt_out) *flush_cnt_out = flush_cnt;
    if(err_cnt_out)   *err_cnt_out   = err_cnt;
}
