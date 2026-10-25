/**
 * @file task_lcd.h
 * @brief LCD 刷新任务: 把阻塞的 ST7789_FlushArea 包成非阻塞.
 * @note  刷屏算法在 BSP/LCD/st7789.c; 优先级须高于 LVGL, 见 app_config.h.
 */

#ifndef __TASK_LCD_H
#define __TASK_LCD_H

#include <stdint.h>

/* 在 vTaskStartScheduler() 之前调用; 由 app_freertos.c 的 Task_Init() 负责 */
void TaskLcd_Create(void);

/**
  * @brief  提交一块矩形区域刷新, 立即返回
  * @param  x1,y1,x2,y2 区域
  * @param  px 像素数据; count 像素个数
  * @param  on_done 整笔完成回调, 在 lcdflsh 任务里执行
  * @retval 1 已接受; 0 未接受(忙/参数为空)
  * @note   忙时也会回调 on_done, 否则 LVGL 会卡在 wait_for_flushing.
  *         px 须有效到 on_done 返回; 同一时刻只接一笔.
  */
uint8_t LCD_FlushArea(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                      const uint16_t *px, uint32_t count,
                      void (*on_done)(void));

#endif /* __TASK_LCD_H */
