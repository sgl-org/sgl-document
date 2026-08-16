/**
 * @file    sgl_battery_demo.c
 * @brief   SGL Battery 电池控件 Demo — 覆盖所有 sgl_battery_xxx 接口
 */
#include "sgl_demo.h"
#if SGD_ENABLE_BATTERY
void sgd_battery_demo(sgl_obj_t *parent)
{
    sgl_obj_t *dianchi1 = sgl_battery_create(parent);
    sgl_obj_set_pos(dianchi1, 60, 30);
    sgl_obj_set_size(dianchi1, 200, 60);

    /* 设置电量百分比 */
    sgl_battery_set_level(dianchi1, 75);

    /* 设置边框颜色 */
    sgl_battery_set_border_color(dianchi1, SGL_COLOR_GRAY);

    /* 设置填充颜色 */
    sgl_battery_set_fill_color(dianchi1, SGL_COLOR_LIME);

    /* 设置低电量颜色 */
    sgl_battery_set_low_color(dianchi1, SGL_COLOR_RED);

    /* 设置中等电量颜色 */
    sgl_battery_set_medium_color(dianchi1, SGL_COLOR_YELLOW);

    /* 设置高电量颜色 */
    sgl_battery_set_high_color(dianchi1, SGL_COLOR_LIME);

    /* 设置背景颜色 */
    sgl_battery_set_bg_color(dianchi1, SGL_COLOR_DARK_GRAY);

    /* 设置电池节数 */
    sgl_battery_set_num_cells(dianchi1, 5);

    /* 设置方向（水平）*/
    sgl_battery_set_direction(dianchi1, SGL_BATTERY_DIR_HORIZONTAL);

    /* 设置电池头大小 */
    sgl_battery_set_cap_size(dianchi1, 8);

    /* 设置电池头位置 */
    sgl_battery_set_cap_pos(dianchi1, SGL_BATTERY_CAP_RIGHT);

    /* 设置充电状态 */
    sgl_battery_set_charging(dianchi1, true);

    /* 设置充电指示颜色 */
    sgl_battery_set_charging_color(dianchi1, SGL_COLOR_CYAN);

    /* 显示百分比文字 */
    sgl_battery_show_percentage(dianchi1, true);

    /* 设置字体 */
    sgl_battery_set_font(dianchi1, &consolas14);

    /* 设置文字颜色 */
    sgl_battery_set_text_color(dianchi1, SGL_COLOR_WHITE);

    /* 第二个电池（纵向，无百分比）*/
    sgl_obj_t *dianchi2 = sgl_battery_create(parent);
    sgl_obj_set_pos(dianchi2, 120, 120);
    sgl_obj_set_size(dianchi2, 40, 100);
    sgl_battery_set_level(dianchi2, 30);
    sgl_battery_set_border_color(dianchi2, SGL_COLOR_GRAY);
    sgl_battery_set_fill_color(dianchi2, SGL_COLOR_RED);
    sgl_battery_set_bg_color(dianchi2, SGL_COLOR_DARK_GRAY);
    sgl_battery_set_direction(dianchi2, SGL_BATTERY_DIR_VERTICAL);
    sgl_battery_set_cap_pos(dianchi2, SGL_BATTERY_CAP_TOP);
    sgl_battery_set_charging(dianchi2, false);
    sgl_battery_show_percentage(dianchi2, false);
}
#endif
