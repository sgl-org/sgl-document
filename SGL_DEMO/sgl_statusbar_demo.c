/**
 * @file    sgl_statusbar_demo.c
 * @brief   SGL Statusbar 状态栏控件 Demo — 覆盖所有 sgl_statusbar_xxx 接口
 *          同时演示把 battery 控件作为状态栏子控件放到右侧
 */
#include "sgl_demo.h"
#if SGD_ENABLE_STATUSBAR

void sgd_statusbar_demo(sgl_obj_t *parent)
{
    int16_t bar_h = sgl_max((int16_t)26, (int16_t)(SGL_SCREEN_HEIGHT / 16));
    int16_t battery_w = 28;
    int16_t battery_h = 14;
    int16_t battery_x = SGL_SCREEN_WIDTH - battery_w - 8;
    int16_t battery_y = (bar_h - battery_h) / 2;

    /* ================================================================
     * 1) 创建状态栏对象
     * ================================================================ */
    sgl_obj_t *zhuangtai = sgl_statusbar_create(parent);
    sgl_obj_set_pos(zhuangtai, 0, 0);
    sgl_obj_set_size(zhuangtai, SGL_SCREEN_WIDTH, bar_h);

    /* 设置字体：状态栏左右槽位文本共用这一套字体 */
    sgl_statusbar_set_font(zhuangtai, &consolas14);

    /* 设置背景颜色 */
    sgl_statusbar_set_bg_color(zhuangtai, sgl_rgb(26, 30, 36));

    /* 设置背景透明度 */
    sgl_statusbar_set_bg_alpha(zhuangtai, 235);

    /* 设置背景圆角：状态栏一般贴屏幕边缘，这里用 0 保持平直 */
    sgl_statusbar_set_bg_radius(zhuangtai, 0);

    /*
     * 设置槽位间距：控制左侧多个槽位、右侧多个槽位之间的文字距离。
     * 这里设为 8，让相邻信息之间不要挤在一起。
     */
    sgl_statusbar_set_slot_space(zhuangtai, 8);

    /*
     * 设置左右边距。
     * 右边距额外预留给 battery 子控件，避免右侧文字和电池重叠。
     */
    sgl_statusbar_set_slot_margin(zhuangtai, 10, battery_w + 18);

    /* ================================================================
     * 2) 左侧槽位接口演示
     * ================================================================ */

    /* 添加左侧槽位 0：先放一个简短标题 */
    sgl_statusbar_add_left_slot(zhuangtai, 0, "SGL");

    /* 添加左侧槽位 1：放当前页面说明 */
    sgl_statusbar_add_left_slot(zhuangtai, 1, "Status Demo");

    /*
     * 再添加一个临时槽位，后面会演示 remove_left_slot。
     * 这样既能覆盖删除接口，也不会影响最终展示内容。
     */
    sgl_statusbar_add_left_slot(zhuangtai, 2, "TMP");

    /* 设置左侧槽位内容：把槽位 0 从初始标题改成更完整的显示文本 */
    sgl_statusbar_set_left_slot(zhuangtai, 0, "SGL UI");

    /* 设置左侧槽位透明度 */
    sgl_statusbar_set_left_slot_alpha(zhuangtai, 0, 255);
    sgl_statusbar_set_left_slot_alpha(zhuangtai, 1, 220);

    /* 设置左侧槽位颜色 */
    sgl_statusbar_set_left_slot_color(zhuangtai, 0, SGL_COLOR_CYAN);
    sgl_statusbar_set_left_slot_color(zhuangtai, 1, SGL_COLOR_WHITE);

    /* 获取左侧槽位索引：用于演示查询接口 */
    int16_t left_idx = sgl_statusbar_get_left_slot_index(zhuangtai, "Status Demo");
    (void)left_idx;

    /* 删除左侧临时槽位，恢复最终布局 */
    sgl_statusbar_remove_left_slot(zhuangtai, 2);

    /* ================================================================
     * 3) 右侧槽位接口演示
     * ================================================================ */

    /* 添加右侧槽位 0：时间 */
    sgl_statusbar_add_right_slot(zhuangtai, 0, "17:49");

    /* 添加右侧槽位 1：连接状态 */
    sgl_statusbar_add_right_slot(zhuangtai, 1, "WiFi");

    /*
     * 添加一个临时右侧槽位，后面会演示 remove_right_slot。
     * 这样可以把所有接口都跑一遍，同时保留清晰的最终效果。
     */
    sgl_statusbar_add_right_slot(zhuangtai, 2, "TMP");

    /* 设置右侧槽位内容：把时间槽位改成更像状态栏的格式 */
    sgl_statusbar_set_right_slot(zhuangtai, 0, "17:49");

    /* 设置右侧槽位透明度 */
    sgl_statusbar_set_right_slot_alpha(zhuangtai, 0, 255);
    sgl_statusbar_set_right_slot_alpha(zhuangtai, 1, 220);

    /* 设置右侧槽位颜色 */
    sgl_statusbar_set_right_slot_color(zhuangtai, 0, SGL_COLOR_WHITE);
    sgl_statusbar_set_right_slot_color(zhuangtai, 1, SGL_COLOR_CYAN);

    /* 获取右侧槽位索引：用于演示查询接口 */
    int16_t right_idx = sgl_statusbar_get_right_slot_index(zhuangtai, "WiFi");
    (void)right_idx;

    /* 删除右侧临时槽位，恢复最终布局 */
    sgl_statusbar_remove_right_slot(zhuangtai, 2);

    /* ================================================================
     * 4) 电池控件作为状态栏子控件
     *    这里不是状态栏自带接口，而是把 battery 直接挂在状态栏上
     * ================================================================ */
    sgl_obj_t *battery = sgl_battery_create(zhuangtai);
    sgl_obj_set_pos(battery, battery_x, battery_y);
    sgl_obj_set_size(battery, battery_w, battery_h);

    /* 设置电量 */
    sgl_battery_set_level(battery, 76);

    /* 设置边框颜色 */
    sgl_battery_set_border_color(battery, SGL_COLOR_WHITE);

    /* 设置填充颜色 */
    sgl_battery_set_fill_color(battery, SGL_COLOR_LIME);

    /* 设置低 / 中 / 高电量颜色 */
    sgl_battery_set_low_color(battery, SGL_COLOR_RED);
    sgl_battery_set_medium_color(battery, SGL_COLOR_YELLOW);
    sgl_battery_set_high_color(battery, SGL_COLOR_LIME);

    /* 设置背景颜色，使它和状态栏底色一致 */
    sgl_battery_set_bg_color(battery, sgl_rgb(26, 30, 36));

    /* 设置电池节数 */
    sgl_battery_set_num_cells(battery, 4);

    /* 设置方向：状态栏里通常使用横向电池 */
    sgl_battery_set_direction(battery, SGL_BATTERY_DIR_HORIZONTAL);

    /* 设置电池头大小和位置 */
    sgl_battery_set_cap_size(battery, 2);
    sgl_battery_set_cap_pos(battery, SGL_BATTERY_CAP_RIGHT);

    /* 设置充电状态和充电颜色 */
    sgl_battery_set_charging(battery, false);
    sgl_battery_set_charging_color(battery, SGL_COLOR_CYAN);

    /* 状态栏空间紧凑，这里隐藏百分比文字 */
    sgl_battery_show_percentage(battery, false);
    sgl_battery_set_font(battery, &consolas14);
    sgl_battery_set_text_color(battery, SGL_COLOR_WHITE);
}

#endif
