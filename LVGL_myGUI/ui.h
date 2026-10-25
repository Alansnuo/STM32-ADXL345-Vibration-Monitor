/**
 * @file ui.h
 * @brief 界面初始化与心跳接口
 */

#ifndef __UI_H
#define __UI_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief  创建界面, 须在 lv_init() 与各 porting 初始化之后
 */
void ui_init(void);

/**
 * @brief  主循环每圈调用一次, 累加心跳计数
 */
void ui_heartbeat(void);

#ifdef __cplusplus
}
#endif

#endif /* __UI_H */
