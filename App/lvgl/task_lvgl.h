/**
 * @file task_lvgl.h
 * @brief LVGL 主任务: 定时跑 lv_timer_handler, 触摸也在里面读.
 * @note  任务参数见 app_config.h.
 */

#ifndef __TASK_LVGL_H
#define __TASK_LVGL_H

/* 在 ui_init() 之后、vTaskStartScheduler() 之前调用; 由 app_freertos.c 负责 */
void TaskLvgl_Create(void);

#endif /* __TASK_LVGL_H */
