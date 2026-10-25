/**
 * @file lv_port_disp.c
 * @brief ST7789 显示对接 LVGL
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_disp.h"
#include <stdbool.h>
#include "st7789.h"         /* ST7789 驱动 */
#include "task_lcd.h"       /* LCD_FlushArea 刷屏任务 */

/*********************
 *      DEFINES
 *********************/
/* 分辨率取自 st7789.h, 下方模板默认值不参与编译 */

#define MY_DISP_HOR_RES    ST7789_WIDTH
#define MY_DISP_VER_RES    ST7789_HEIGHT

#ifndef MY_DISP_HOR_RES
    #warning Please define or replace the macro MY_DISP_HOR_RES with the actual screen width, default value 320 is used for now.
    #define MY_DISP_HOR_RES    320
#endif

#ifndef MY_DISP_VER_RES
    #warning Please define or replace the macro MY_DISP_VER_RES with the actual screen height, default value 240 is used for now.
    #define MY_DISP_VER_RES    240
#endif

#define BYTE_PER_PIXEL (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_RGB565)) /* RGB565 下为 2 */

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void disp_init(void);

static void disp_flush(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map);

static void disp_flush_done_cb(void);

/**********************
 *  STATIC VARIABLES
 **********************/

/* 刷屏完成回调据此调 lv_display_flush_ready() */
static lv_display_t * s_disp = NULL;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * @brief  初始化显示并注册 LVGL 显示设备
 */
void lv_port_disp_init(void)
{
    /* 初始化屏幕 */
    disp_init();

    /* 创建显示设备并注册 flush 回调 */
    lv_display_t * disp = lv_display_create(MY_DISP_HOR_RES, MY_DISP_VER_RES);
    lv_display_set_flush_cb(disp, disp_flush);

    /* RGB565_SWAPPED: 高字节在前, ST7789 可零拷贝 DMA.
     * 须在 set_buffers 之前调用. */
    lv_display_set_color_format(disp, LV_COLOR_FORMAT_RGB565_SWAPPED);
    /* 缓冲: 320x32x2 = 20KB, 约 1/10 屏 */
    LV_ATTRIBUTE_MEM_ALIGN
    static uint8_t buf_1_1[MY_DISP_HOR_RES * 32 * BYTE_PER_PIXEL];            /* 32 行缓冲 */

    /* 第二块: 一块绘制时另一块正在 DMA 输出 */
    LV_ATTRIBUTE_MEM_ALIGN
    static uint8_t buf_1_2[MY_DISP_HOR_RES * 32 * BYTE_PER_PIXEL];            /* 32 行缓冲 */
    lv_display_set_buffers(disp, buf_1_1, buf_1_2, sizeof(buf_1_1), LV_DISPLAY_RENDER_MODE_PARTIAL);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * @brief  初始化 ST7789
 */
static void disp_init(void)
{
    /* 复位 / 初始化表 / 清屏均在 BSP 驱动内 */

    ST7789_Init();
}

/**
 * @brief  把一块像素交给 LCD 任务刷到屏上
 * @param  disp_drv 显示设备
 * @param  area     刷新区域
 * @param  px_map   像素数据
 */
static void disp_flush(lv_display_t * disp_drv, const lv_area_t * area, uint8_t * px_map)
{
    s_disp = disp_drv;

    /* 交给 LCD 任务分块 DMA 刷新, 完成后由回调调 flush_ready */
    LCD_FlushArea((uint16_t)area->x1, (uint16_t)area->y1,
                  (uint16_t)area->x2, (uint16_t)area->y2,
                  (const uint16_t *)px_map,
                  (uint32_t)(area->x2 - area->x1 + 1) *
                  (uint32_t)(area->y2 - area->y1 + 1),
                  disp_flush_done_cb);
}

/**
 * @brief  刷屏完成, 在 lcdflsh 任务上下文调用
 */
static void disp_flush_done_cb(void)
{
    if(s_disp) lv_display_flush_ready(s_disp);
}

/* ===================== 本工程加的调试接口 ===================== */

/**
 * @brief  取刷屏 / 出错计数
 * @param  flush_cnt 已完成刷屏次数
 * @param  err_cnt   SPI 出错 / DMA 超时次数
 */
void lv_port_disp_get_stats(uint32_t * flush_cnt, uint32_t * err_cnt)
{
    ST7789_GetStats(flush_cnt, err_cnt);
}
