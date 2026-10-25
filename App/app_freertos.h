/**
 * @file app_freertos.h
 * @brief 应用层 OS 入口: 创建全部任务.
 * @note  任务参数见 app_config.h; 必须在 vTaskStartScheduler() 之前调用.
 */

#ifndef __APP_FREERTOS_H
#define __APP_FREERTOS_H

void Task_Init(void);

#endif /* __APP_FREERTOS_H */
