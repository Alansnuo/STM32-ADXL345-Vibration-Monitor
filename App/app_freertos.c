/**
 * @file app_freertos.c
 * @brief 应用层 OS 入口: 建任务 + 两个 FreeRTOS 钩子.
 */

#include "app_freertos.h"

#include "FreeRTOS.h"
#include "task.h"

#include "task_lcd.h"
#include "task_lvgl.h"

void Task_Init(void)
{
    TaskLcd_Create();
    TaskLvgl_Create();
}

/* 任务爆栈; configCHECK_FOR_STACK_OVERFLOW = 2 */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    (void)xTask;
    (void)pcTaskName;

    taskDISABLE_INTERRUPTS();
    for(;;) { }
}

/* pvPortMalloc 失败; configUSE_MALLOC_FAILED_HOOK = 1 */
void vApplicationMallocFailedHook(void)
{
    taskDISABLE_INTERRUPTS();
    for(;;) { }
}
