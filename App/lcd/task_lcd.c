/**
 * @file task_lcd.c
 * @brief LCD 刷新任务实现: 接到通知后刷屏, 完成后回调 LVGL.
 */

#include "task_lcd.h"

#include "FreeRTOS.h"
#include "task.h"
#include "st7789.h"
#include "app_config.h"

#define FLAG_FLUSH_START (1U << 1)      /* 有新 flush 要做, 用任务通知, 不另建队列 */

static TaskHandle_t s_flush_task = NULL;
static uint16_t s_x1, s_y1, s_x2, s_y2;
static uint32_t s_total;
static const uint16_t *s_px;
static void (*s_on_done)(void) = NULL;
static volatile uint8_t s_active = 0;   /* 有一笔在飞, 调用方和任务都会读写 */

/* 等通知 → 阻塞刷完 → 清活动标志 → 回调 */
static void lcd_flush_task(void *arg)
{
    (void)arg;

    for(;;)
    {
        xTaskNotifyWait(0U, FLAG_FLUSH_START, NULL, portMAX_DELAY);

        /* 块间驱动自己睡在 DMA 信号量上, 把 CPU 让给 LVGL 渲染 */
        (void)ST7789_FlushArea(s_x1, s_y1, s_x2, s_y2, s_px, s_total);

        s_active = 0U;

        {
            void (*cb)(void) = s_on_done;
            s_on_done = NULL;
            if(cb) cb();
        }
    }
}

/* 建不出来就没救了: 屏幕永远不刷, 所以停在断言里 */
void TaskLcd_Create(void)
{
    s_flush_task = NULL;
    if(xTaskCreate(lcd_flush_task,
                   "lcdflsh",
                   TASK_LCD_STACK_WORDS,
                   NULL,
                   TASK_LCD_PRIORITY,
                   &s_flush_task) != pdPASS)
    {
        s_flush_task = NULL;
    }

    configASSERT(s_flush_task != NULL);
}

uint8_t LCD_FlushArea(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                      const uint16_t *px, uint32_t count,
                      void (*on_done)(void))
{
    if(px == NULL || on_done == NULL) return 0U;

    if(s_active) {
        /* 忙也当场回调, 否则 flush_ready 永远不来, LVGL 卡在 wait_for_flushing */
        on_done();
        return 0U;
    }

    s_x1 = x1; s_y1 = y1; s_x2 = x2; s_y2 = y2;
    s_px = px;
    s_total = count;
    s_on_done = on_done;
    s_active = 1U;

    xTaskNotify(s_flush_task, FLAG_FLUSH_START, eSetBits);
    return 1U;
}
