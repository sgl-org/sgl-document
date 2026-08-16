/**
 * @file    sgl_switch_demo.c
 * @brief   SGL Switch 开关控件 Demo — 覆盖所有 sgl_switch_xxx 接口
 *          开关控件用于切换两种状态（开/关），支持自定义颜色
 */
#include "sgl_demo.h"
#if SGD_ENABLE_SWITCH

static void on_sw_event(sgl_event_t *e)
{
    if (e->type == SGL_EVENT_PRESSED )//|| e->type == SGL_EVENT_RELEASED
    {
        sgl_obj_t *SW = sgl_event_get_target(e);
        if (SW) {
            sgl_log("[SWITCH_DEMO_1]","SW=%d",sgl_switch_get_status(SW));
        }
    }
}

void sgd_switch_demo(sgl_obj_t *parent) {
    int16_t y = SGD_MG;
    sgl_obj_t *sw;

    /* 创建开关对象 */
    sw = sgl_switch_create(parent);
    sgl_obj_set_pos(sw, SGD_MG, y);  sgl_obj_set_size(sw, 60, SGD_H);

    /* 设置开关状态（true=开，false=关） */
    sgl_switch_set_status(sw, true);

    /* 设置开关主体颜色（开启时的颜色） */
    sgl_switch_set_color(sw, SGL_COLOR_GREEN);

    /* 设置开关背景颜色（关闭时的颜色） */
    sgl_switch_set_bg_color(sw, SGL_COLOR_DARK_GRAY);

    /* 设置拖动球（knob）的颜色 */
    sgl_switch_set_knob_color(sw, SGL_COLOR_WHITE);

    /* 设置边框颜色 */
    sgl_switch_set_border_color(sw, SGL_COLOR_DARK_GRAY);

    /* 设置边框宽度 */
    sgl_switch_set_border_width(sw, 1);

    /* 设置圆角半径 */
    sgl_switch_set_radius(sw, 12);

    /* 设置透明度 */
    sgl_switch_set_alpha(sw, 200);

    /* 设置拖动球与边框的间距 */
    sgl_switch_set_knob_margin(sw, 2);

    /* 读取开关状态（演示 get_status 接口） */
    sgl_switch_get_status(sw);
		    /* 注册事件回调，拖动滑块时实时更新标签显示 */
    sgl_obj_set_event_cb(sw, on_sw_event, NULL);
		//sgl_log("[SWITCH_DEMO_1]","SW=%d",sgl_switch_get_status(sw));
    y += SGD_H + SGD_GAP;

    /* 长方形开关 — 关闭状态 + 红色 */
    sw = sgl_switch_create(parent);
    sgl_obj_set_pos(sw, SGD_MG, y);  sgl_obj_set_size(sw, 100, SGD_H - 5);
    sgl_switch_set_status(sw, false);
    sgl_switch_set_color(sw, SGL_COLOR_RED);
    sgl_switch_set_bg_color(sw, SGL_COLOR_DARK_GRAY);
    sgl_switch_set_knob_color(sw, SGL_COLOR_WHITE);
    sgl_switch_set_radius(sw, (SGD_H - 5)/2);
    y += SGD_H + SGD_GAP;

    /* 长方形开关 — 开启状态 + 蓝色 */
    sw = sgl_switch_create(parent);
    sgl_obj_set_pos(sw, SGD_MG, y);  sgl_obj_set_size(sw, 100, SGD_H - 10);
    sgl_switch_set_status(sw, true);
    sgl_switch_set_color(sw, SGL_COLOR_DODGER_BLUE);
    sgl_switch_set_bg_color(sw, SGL_COLOR_DARK_GRAY);
    sgl_switch_set_knob_color(sw, SGL_COLOR_WHITE);
    sgl_switch_set_radius(sw, 4);
    y += SGD_H + SGD_GAP;
}
#endif