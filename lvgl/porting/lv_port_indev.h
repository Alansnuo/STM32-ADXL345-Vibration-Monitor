/**
 * @file lv_port_indev.h
 * @brief 触摸输入对接接口
 */

#if 1

#ifndef LV_PORT_INDEV_TEMPL_H
#define LV_PORT_INDEV_TEMPL_H

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
 * @brief  初始化触摸输入设备
 */
void lv_port_indev_init(void);

/* ===================== 本工程加的接口 ===================== */

/**
 * @brief  取触摸调试状态 (ID / S 两行)
 * @param  raw_x FT6336U 固件 ID, 非 0 表示 I2C 通
 * @param  raw_y 固定 0, 占位
 * @param  x     最近一次触摸的 x 坐标
 * @param  y     最近一次触摸的 y 坐标
 */
void lv_port_indev_get_debug(uint16_t * raw_x, uint16_t * raw_y, int32_t * x, int32_t * y);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_PORT_INDEV_TEMPL_H*/

#endif /*Disable/Enable content*/
