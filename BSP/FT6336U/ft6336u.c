/**
 * @file ft6336u.c
 * @brief FT6336U 驱动实现, 软件 I2C 读寄存器
 * @note  方向翻转与边界裁剪在本文件完成
 */

#include "ft6336u.h"
#include "MyI2C.h"

/* FT6336U 7 位地址 0x38, 读写字节 = 0x38 << 1 | R/W */
#define FT6336U_ADDR_W   0x70   /* 写地址 */
#define FT6336U_ADDR_R   0x71   /* 读地址 */

/* ---------- 寄存器 ---------- */
#define REG_DEV_MODE     0x00   /* 工作模式 */
#define REG_GEST_ID      0x01   /* 手势 ID */
#define REG_TD_STATUS    0x02   /* [3:0] 触摸点数 */
#define REG_P1_XH        0x03   /* bit7-6 事件, bit3-0 X 高 4 位 */
#define REG_P1_XL        0x04   /* X 低 8 位 */
#define REG_P1_YH        0x05   /* bit3-0 Y 高 4 位 */
#define REG_P1_YL        0x06   /* Y 低 8 位 */
#define REG_P2_XH        0x09   /* 点 2, 偏移 = P1 + 6 */
#define REG_FIRMID       0xA6   /* 固件 ID */

/* 每个触摸点 6 字节: XH XL YH YL W M */
#define POINT_BYTES      6

/* ---------- 底层: 软件 I2C 读写寄存器 ---------- */

/**
 * @brief  发起读事务
 * @param  reg 寄存器地址
 *         Start + 写地址 + 寄存器地址, 之后由调用方发 ReStart
 */
static void ft6336u_prepare_read(uint8_t reg)
{
    MyI2C_Start();
    MyI2C_SendByte(FT6336U_ADDR_W);
    MyI2C_ReceiveAck();
    MyI2C_SendByte(reg);
    MyI2C_ReceiveAck();
}

/**
 * @brief  读单个寄存器
 * @param  reg 寄存器地址
 * @retval 寄存器值
 */
uint8_t FT6336U_ReadReg(uint8_t reg)
{
    uint8_t val;

    ft6336u_prepare_read(reg);
    MyI2C_Start();                          /* ReStart */
    MyI2C_SendByte(FT6336U_ADDR_R);
    MyI2C_ReceiveAck();
    val = MyI2C_ReceiveByte();
    MyI2C_SendAck(1);                       /* NACK = 只读这一个 */
    MyI2C_Stop();
    return val;
}

/**
 * @brief  连续读多个寄存器
 * @param  reg 起始寄存器地址
 * @param  buf 接收缓冲
 * @param  len 读取字节数
 */
void FT6336U_ReadRegMulti(uint8_t reg, uint8_t *buf, uint8_t len)
{
    ft6336u_prepare_read(reg);
    MyI2C_Start();                          /* ReStart */
    MyI2C_SendByte(FT6336U_ADDR_R);
    MyI2C_ReceiveAck();
    for(uint8_t i = 0; i < len; i++) {
        buf[i] = MyI2C_ReceiveByte();
        MyI2C_SendAck(i < (len - 1) ? 0 : 1);   /* 中间 ACK, 最后 NACK */
    }
    MyI2C_Stop();
}

/**
 * @brief  读固件 ID, 非 0 表示 I2C 通信正常
 * @retval 0x00 或 0xFF 表示总线无应答
 */
uint8_t FT6336U_GetFirmwareID(void)
{
    return FT6336U_ReadReg(REG_FIRMID);
}

/* ---------- 初始化 ---------- */

/**
 * @brief  硬件复位并等待芯片就绪
 */
void FT6336U_Init(void)
{
    /* RST 拉低 >= 10ms, 放开后等 300ms 再访问 I2C */
    HAL_GPIO_WritePin(FT_RST_PORT, FT_RST_PIN, GPIO_PIN_RESET);
    HAL_Delay(20);
    HAL_GPIO_WritePin(FT_RST_PORT, FT_RST_PIN, GPIO_PIN_SET);
    HAL_Delay(300);

    /* 读一次确认芯片活着, 为 0 时查引脚宏和上拉 */
    FT6336U_ReadReg(REG_FIRMID);
}

/* ---------- 触摸检测 ---------- */

/**
 * @brief  轮询 INT 引脚判断是否有触摸
 * @retval 1 有触摸; 0 无
 */
uint8_t FT6336U_IsTouched(void)
{
    /* 读 INT 引脚, 低有效; 未接好时可改读 REG_TD_STATUS & 0x0F */
    return (HAL_GPIO_ReadPin(FT_INT_PORT, FT_INT_PIN) == GPIO_PIN_RESET) ? 1U : 0U;
}

/**
 * @brief  读取单点屏幕坐标
 * @param  x 出参, 屏幕坐标 x
 * @param  y 出参, 屏幕坐标 y
 * @retval 1 成功; 0 当前无触摸或参数为空
 */
uint8_t FT6336U_GetTouchPoint(uint16_t *x, uint16_t *y)
{
    uint8_t num;
    uint8_t buf[POINT_BYTES];
    uint16_t raw_x, raw_y;

    if(x == NULL || y == NULL) return 0U;

    num = FT6336U_ReadReg(REG_TD_STATUS) & 0x0F;
    if(num == 0U) return 0U;

    /* 从 P1_XH 连续读 6 字节: X / Y / 重量 / 面积 */
    FT6336U_ReadRegMulti(REG_P1_XH, buf, POINT_BYTES);

    raw_x = (uint16_t)(((buf[0] & 0x0F) << 8) | buf[1]);   /* XH[3:0] + XL */
    raw_y = (uint16_t)(((buf[2] & 0x0F) << 8) | buf[3]);   /* YH[3:0] + YL */

    /* 原生坐标是竖屏 240x320, 横屏时 swap 并翻转一条轴 */
#if FT6336U_LANDSCAPE
    *x = raw_y;
    *y = FT6336U_SCREEN_HEIGHT - 1U - raw_x;
#else
    *x = raw_x;
    *y = raw_y;
#endif

    /* 边界裁剪 */
    if(*x >= FT6336U_SCREEN_WIDTH)  *x = FT6336U_SCREEN_WIDTH - 1U;
    if(*y >= FT6336U_SCREEN_HEIGHT) *y = FT6336U_SCREEN_HEIGHT - 1U;

    return 1U;
}

/* ---------- 多点 / 调试 ---------- */

/**
 * @brief  读取完整触摸数据, 含点数 / 坐标 / 事件
 * @param  data 出参, 为空时直接返回
 */
void FT6336U_GetTouchData(FT6336U_TouchData *data)
{
    uint8_t num;
    uint8_t buf[POINT_BYTES];

    if(data == NULL) return;

    num = FT6336U_ReadReg(REG_TD_STATUS) & 0x0F;
    data->num = num;
    if(num == 0U) return;

    /* 第 1 点, LVGL 只用第一点 */
    FT6336U_ReadRegMulti(REG_P1_XH, buf, POINT_BYTES);
    data->event[0] = (uint8_t)((buf[0] >> 6) & 0x03);
    data->x[0] = (uint16_t)(((buf[0] & 0x0F) << 8) | buf[1]);
    data->y[0] = (uint16_t)(((buf[2] & 0x0F) << 8) | buf[3]);

#if FT6336U_LANDSCAPE
    {
        uint16_t tmp = data->x[0];
        data->x[0] = data->y[0];
        data->y[0] = FT6336U_SCREEN_HEIGHT - 1U - tmp;
    }
#endif

    if(data->x[0] >= FT6336U_SCREEN_WIDTH)  data->x[0] = FT6336U_SCREEN_WIDTH - 1U;
    if(data->y[0] >= FT6336U_SCREEN_HEIGHT) data->y[0] = FT6336U_SCREEN_HEIGHT - 1U;
}