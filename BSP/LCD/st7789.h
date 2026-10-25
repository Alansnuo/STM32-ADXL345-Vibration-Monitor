/**
 * @file st7789.h
 * @brief ST7789 液晶驱动, 依赖 HAL 与 FreeRTOS
 * @note  刷屏期间 CS 必须全程保持低, 否则地址计数错位
 */

#ifndef __ST7789_H
#define __ST7789_H

#include "main.h" /* HAL + GPIO */
#include "spi.h"  /* SPI 句柄 */

/* LCD 引脚, CubeMX 已配成推挽输出 */
#define LCD_CS_PORT     GPIOD
#define LCD_CS_PIN      GPIO_PIN_6
#define LCD_DC_PORT     GPIOD
#define LCD_DC_PIN      GPIO_PIN_4
#define LCD_RESET_PORT  GPIOD
#define LCD_RESET_PIN   GPIO_PIN_5

/* ---------- 移植配置区 ---------- */

#define ST7789_SPI hspi2

#define ST7789_LANDSCAPE 1   /* 0 = 竖屏 240x320, 1 = 横屏 320x240 */

#if ST7789_LANDSCAPE
#define ST7789_WIDTH 320
#define ST7789_HEIGHT 240
#define ST7789_MADCTL 0x60
#else
#define ST7789_WIDTH 240
#define ST7789_HEIGHT 320
#define ST7789_MADCTL 0x00
#endif

#define ST7789_DMA_BUF_PIXELS 4800   /* 分块缓冲, RAM = 2 字节 x 该值 */

/* ---------- 颜色 (RGB565) ---------- */
#define ST7789_BLACK 0x0000
#define ST7789_WHITE 0xFFFF
#define ST7789_RED 0xF800
#define ST7789_GREEN 0x07E0
#define ST7789_BLUE 0x001F
#define ST7789_YELLOW 0xFFE0
#define ST7789_CYAN 0x07FF
#define ST7789_MAGENTA 0xF81F
#define ST7789_GRAY 0x8410

/* ---------- 对外接口 ---------- */

/**
 * @brief  初始化面板, 幂等
 *         硬复位 → 初始化表 → 清屏; 须在 GPIO / SPI 初始化后调用
 */
void ST7789_Init(void);

/**
 * @brief  阻塞铺一块矩形, 不依赖 DMA / 中断 / RTOS
 * @param  x1,y1,x2,y2 区域, 越界自动裁剪
 * @param  color RGB565 颜色
 */
void ST7789_FillRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

/**
 * @brief  整屏铺一个颜色
 * @param  color RGB565 颜色
 */
void ST7789_FillScreen(uint16_t color);

/**
 * @brief  刷一块矩形, 阻塞到发完
 * @param  x1,y1,x2,y2 区域, 越界自动裁剪
 * @param  px 像素数据, 返回前须一直有效
 * @param  count 像素个数, 小于窗口则少发
 * @retval 1 整块发完; 0 参数非法或中途出错
 *         只能在任务上下文调用; 接 LVGL 时走 App 层 LCD_FlushArea()
 */
uint8_t ST7789_FlushArea(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                         const uint16_t *px, uint32_t count);

/**
 * @brief  读调试统计
 * @param  flush_cnt 成功刷屏次数, 不涨说明卡了
 * @param  err_cnt 出错累计
 */
void ST7789_GetStats(uint32_t *flush_cnt, uint32_t *err_cnt);

#endif /* __ST7789_H */
