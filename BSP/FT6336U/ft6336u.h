/**
 * @file ft6336u.h
 * @brief FT6336U 电容触摸驱动, 软件 I2C, 输出屏幕坐标
 * @note  I2C 引脚见 MyI2C.h
 */
#ifndef __FT6336U_H
#define __FT6336U_H

#include "main.h"   /* HAL + GPIO */

/* INT 上拉, 下降沿触发; RST 低有效 */
#define FT_INT_PORT     GPIOE
#define FT_INT_PIN      GPIO_PIN_2
#define FT_RST_PORT     GPIOF
#define FT_RST_PIN      GPIO_PIN_2

/* ---------- 移植配置区 ---------- */

#define FT6336U_LANDSCAPE       1   /* 须与 st7789.h 的 ST7789_LANDSCAPE 一致 */

#if FT6336U_LANDSCAPE
#define FT6336U_SCREEN_WIDTH    320
#define FT6336U_SCREEN_HEIGHT   240
#else
#define FT6336U_SCREEN_WIDTH    240
#define FT6336U_SCREEN_HEIGHT   320
#endif

/* ---------- 触摸点结构 ---------- */

typedef struct {
    uint8_t  num;       /* 触摸点数, 0=无触摸 */
    uint16_t x[5];      /* 屏幕坐标 x */
    uint16_t y[5];      /* 屏幕坐标 y */
    uint8_t  event[5];  /* 0=按下, 1=抬起, 2=触碰, 3=保留 */
} FT6336U_TouchData;

/* ---------- 对外接口 ---------- */

/**
 * @brief  硬件复位并等待芯片就绪
 */
void FT6336U_Init(void);

/**
 * @brief  轮询 INT 引脚判断是否有触摸
 * @retval 1 有触摸; 0 无
 */
uint8_t FT6336U_IsTouched(void);

/**
 * @brief  读取单点屏幕坐标, 已做方向翻转和边界裁剪
 * @param  x 出参, 0 ~ FT6336U_SCREEN_WIDTH-1
 * @param  y 出参, 0 ~ FT6336U_SCREEN_HEIGHT-1
 * @retval 1 成功; 0 当前无触摸
 */
uint8_t FT6336U_GetTouchPoint(uint16_t *x, uint16_t *y);

/**
 * @brief  读取完整触摸数据
 * @param  data 出参, 点数 / 坐标 / 事件
 */
void FT6336U_GetTouchData(FT6336U_TouchData *data);

/**
 * @brief  读固件 ID, 非 0 表示软件 I2C 通信正常
 * @retval 0x00 或 0xFF 表示总线无应答
 */
uint8_t FT6336U_GetFirmwareID(void);

/**
 * @brief  读单个寄存器, 调试用
 * @param  reg 寄存器地址
 * @retval 寄存器值
 */
uint8_t FT6336U_ReadReg(uint8_t reg);

/**
 * @brief  连续读多个寄存器, 调试用
 * @param  reg 起始寄存器地址
 * @param  buf 接收缓冲
 * @param  len 读取字节数
 */
void FT6336U_ReadRegMulti(uint8_t reg, uint8_t *buf, uint8_t len);

#endif /* __FT6336U_H */