/**
 * @file task_lvgl.c
 * @brief LVGL 主任务实现: 喂心跳, 跑定时器, 按返回值休眠.
 */

#include "task_lvgl.h"

#include "FreeRTOS.h"
#include "task.h"
#include "lvgl.h"
#include "ui.h"
#include "app_config.h"

static TaskHandle_t s_lvgl_task = NULL;

static void lvgl_task(void *arg);

void TaskLvgl_Create(void)
{
    s_lvgl_task = NULL;
    if(xTaskCreate(lvgl_task,
                   "lvgl",
                   TASK_LVGL_STACK_WORDS,
                   NULL,
                   TASK_LVGL_PRIORITY,      /* 须低于 lcdflsh */
                   &s_lvgl_task) != pdPASS)
    {
        s_lvgl_task = NULL;
    }

    configASSERT(s_lvgl_task != NULL);
}

static void lvgl_task(void *arg)
{
    (void)arg;

    for(;;)
    {
        uint32_t t;

        ui_heartbeat();
        t = lv_timer_handler();     /* 返回下次该跑的毫秒数 */

        vTaskDelay(pdMS_TO_TICKS(t > 0U ? t : TASK_LVGL_MIN_SLEEP_MS));
    }
}
