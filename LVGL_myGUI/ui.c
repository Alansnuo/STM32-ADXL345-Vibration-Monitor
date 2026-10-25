/**
 * @file ui.c
 * @brief 界面实现: 全屏背景与主循环心跳
 * @note  背景须用全屏矩形对象铺设, 不能用屏幕自身背景.
 */

/*********************
 *      INCLUDES
 *********************/
#include "ui.h"
#include "lvgl.h"
#include "lv_port_disp.h"     /* 刷屏统计 */
#include "lv_port_indev.h"    /* 触摸调试 */

/**********************
 *  STATIC PROTOTYPES
 **********************/


/**********************
 *  STATIC VARIABLES
 **********************/

/* 主循环心跳, 由 ui_heartbeat() 累加 */
static volatile uint32_t hb_cnt = 0;

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * @brief  主循环心跳, 每圈加一
 */
void ui_heartbeat(void)
{
    hb_cnt++;
}

/**
 * @brief  创建界面, 当前仅保留示例代码
 */
void ui_init(void)
{

    // lv_obj_t * scr = lv_screen_active();

    // lv_obj_t * obj1= lv_obj_create(scr);
    // lv_obj_set_size(obj1,40,40);
    // lv_obj_set_pos(obj1, 10, 10);

    // lv_obj_t * obj2= lv_obj_create(scr);
    // lv_obj_set_size(obj2,40,40);
    // lv_obj_set_pos(obj2, 60, 10);

    // //按钮
    // lv_obj_t* bth = lv_btn_create(obj);
    // lv_obj_set_size(bth,40,40);
    // lv_obj_set_pos(bth, 10, 10);

    // //滑块
    // lv_obj_t* slider = lv_slider_create(obj);
    // lv_obj_set_size(slider, 60, 10); //设置滑块大小, 60px 宽, 10px 高
    // lv_obj_set_pos(slider, 10, 80); //设置滑块位置, 左上角坐标为 (10, 80)
    // lv_slider_set_range(slider, 0, 5); //设置滑块范围, 最小值为 0, 最大值为 5
    // lv_slider_set_value(slider, 0, LV_ANIM_OFF); //设置滑块初始值, 不使用动画





    
}

