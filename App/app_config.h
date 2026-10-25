/**
 * @file app_config.h
 * @brief 应用层全局配置: 任务优先级、栈、最短睡眠及编译期检查.
 * @note  内核参数(tick/堆/优先级级数)在 FreeRTOSConfig.h.
 */

#ifndef __APP_CONFIG_H
#define __APP_CONFIG_H

#include "FreeRTOSConfig.h"


/* 优先级: 数值越大越优先; 0=IDLE, 7=Tmr Svc, 应用只能用 1~6; 4~6 预留给采样/控制 */
#define TASK_LVGL_PRIORITY      2   /* LVGL 渲染与触摸 */
#define TASK_LCD_PRIORITY       3   /* 刷屏, 须高于 LVGL */

/* 栈, 单位: 字(4 字节) */
#define TASK_LVGL_STACK_WORDS   2048   /* 8KB: lv_timer_handler + lv_snprintf */
#define TASK_LCD_STACK_WORDS    256    /* 1KB: on_done 回调 */

#define TASK_LVGL_MIN_SLEEP_MS  1U     /* 返回 0 时的兜底睡眠, 防止饿死 lcdflsh */



/* 编译期检查: 配错了跑起来极难反查, 宁可在编译期拦住 */
#if (TASK_LCD_PRIORITY <= TASK_LVGL_PRIORITY)
#error "TASK_LCD_PRIORITY 必须 > TASK_LVGL_PRIORITY: LVGL 的 flush 等待是忙等"
#endif

#if (TASK_LVGL_PRIORITY < 1) || (TASK_LCD_PRIORITY >= (configMAX_PRIORITIES - 1))
#error "应用优先级须在 1 .. configMAX_PRIORITIES-2: 0 是 IDLE, 最高一级是 Tmr Svc"
#endif

#if (TASK_LVGL_STACK_WORDS < configMINIMAL_STACK_SIZE) || (TASK_LCD_STACK_WORDS < configMINIMAL_STACK_SIZE)
#error "任务栈小于 configMINIMAL_STACK_SIZE, 检查是否把字节数当字数填了"
#endif

#if (((TASK_LVGL_STACK_WORDS + TASK_LCD_STACK_WORDS) * 4U) > (configTOTAL_HEAP_SIZE / 2U))
#error "应用任务栈超过堆的一半, 请减小栈或加大 configTOTAL_HEAP_SIZE"
#endif

#endif /* __APP_CONFIG_H */
