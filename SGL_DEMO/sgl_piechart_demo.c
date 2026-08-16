/**
 * @file    sgl_piechart_demo.c
 * @brief   SGL 饼图控件 Demo — 覆盖所有 sgl_piechart_xxx 接口
 *          展示环形/实心饼图 + 图例 + 打开动画
 */
#include "sgl_demo.h"
#if SGD_ENABLE_PIECHART

void sgd_piechart_demo(sgl_obj_t *parent)
{
    /* 创建饼图控件 */
    sgl_obj_t *pie = sgl_piechart_create(parent);
    sgl_obj_set_pos(pie, 0, 0);
    sgl_obj_set_size(pie, SGL_SCREEN_WIDTH, SGL_SCREEN_HEIGHT);

    /* 设置扇区数量 */
    sgl_piechart_set_slice_count(pie, 4);

    /* 逐项设置扇区：数值 / 颜色 / 透明度 / 图例文字 */
    sgl_piechart_set_slice_value(pie, 0, 30);
    sgl_piechart_set_slice_color(pie, 0, SGL_COLOR_RED);
    sgl_piechart_set_slice_alpha(pie, 0, SGL_ALPHA_MAX);
    sgl_piechart_set_slice_label(pie, 0, "Red");

    /* 便捷函数：一次设置数值、颜色与图例文字 */
    sgl_piechart_set_slice(pie, 1, 25, SGL_COLOR_GREEN, "Green");
    sgl_piechart_set_slice(pie, 2, 20, SGL_COLOR_BLUE, "Blue");
    sgl_piechart_set_slice(pie, 3, 15, SGL_COLOR_ORANGE, "Orange");

    /* 设置全局透明度 */
    sgl_piechart_set_alpha(pie, SGL_ALPHA_MAX);

    /* 设置第一块扇区的起始角度 */
    sgl_piechart_set_start_angle(pie, 0);

    /* 设置内径比例（0=实心饼，>0=环形图） */
    sgl_piechart_set_inner_radius_rate(pie, 0);

    /* 设置外径（0=按控件尺寸自动计算） */
    sgl_piechart_set_radius(pie, 0);

    /* 使能扇区边缘平滑 */
    sgl_piechart_set_smooth(pie, true);

    /* 使能图例 */
    sgl_piechart_enable_legend(pie, true);

    /* 设置图例位置（左侧/右侧/顶部/底部） */
    sgl_piechart_set_legend_pos(pie, SGL_PIECHART_LEGEND_POS_RIGHT);

    /* 设置图例排列方向（垂直/水平） */
    sgl_piechart_set_legend_dir(pie, SGL_PIECHART_LEGEND_DIR_VERTICAL);

    /* 设置图例区域大小（左右时是宽度，上下时是高度） */
    sgl_piechart_set_legend_area_size(pie, 100);

    /* 设置图例字体 */
    sgl_piechart_set_legend_font(pie, &consolas14);

    /* 设置图例文字颜色 */
    sgl_piechart_set_legend_text_color(pie, SGL_COLOR_WHITE);

    /* 设置图例透明度 */
    sgl_piechart_set_legend_alpha(pie, SGL_ALPHA_MAX);

    /* 设置图例色块大小 */
    sgl_piechart_set_legend_box_size(pie, 10);

    /* 设置图例内边距 */
    sgl_piechart_set_legend_padding(pie, 6);

    /* 设置图例项间距 */
    sgl_piechart_set_legend_item_gap(pie, 4);

    /* 使能图例背景块 */
    sgl_piechart_enable_legend_bg(pie, true);
    sgl_piechart_set_legend_bg_color(pie, SGL_COLOR_DARK_GRAY);
    sgl_piechart_set_legend_border_color(pie, SGL_COLOR_GRAY);

    /* 使能打开动画（首帧 0->360 度展开） */
    sgl_piechart_enable_open_anim(pie, true);
    sgl_piechart_set_open_anim_path(pie, SGL_ANIM_PATH_EASE_OUT);
}
#endif
