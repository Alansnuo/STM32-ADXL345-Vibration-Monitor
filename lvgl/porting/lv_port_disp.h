/**
 * @file lv_port_disp.h
 * @brief 显示驱动对接接口
 */

#if 1

#ifndef LV_PORT_DISP_TEMPL_H
#define LV_PORT_DISP_TEMPL_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lvgl.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
/**
 * @brief  初始化显示并注册 LVGL 显示设备
 */
void lv_port_disp_init(void);

/* ===================== 本工程加的接口 ===================== */

/**
 * @brief  取刷屏统计
 * @param  flush_cnt 已完成刷屏次数
 * @param  err_cnt   SPI 出错 / DMA 超时次数
 */
void lv_port_disp_get_stats(uint32_t * flush_cnt, uint32_t * err_cnt);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_PORT_DISP_TEMPL_H*/

#endif /*Disable/Enable content*/
