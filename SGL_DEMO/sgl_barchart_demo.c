/**
 * @file    sgl_barchart_demo.c
 * @brief   SGL 柱形图控件 Demo — 覆盖所有 sgl_barchart_xxx 接口
 *          展示分组柱形图 + 坐标轴/网格 + 打开动画
 */
#include "sgl_demo.h"
#if SGD_ENABLE_BARCHART

/* 两组柱状数据（数据必须为持久存储，图表只保存指针） */
static const int32_t sgd_bar_y1[] = { 40, 70, 55, 90, 60 };
static const int32_t sgd_bar_y2[] = { 30, 50, 80, 45, 70 };

/* X 轴分类标签 */
static const char *sgd_bar_x_labels[] = { "A", "B", "C", "D", "E" };

void sgd_barchart_demo(sgl_obj_t *parent)
{
    /* 创建柱形图控件 */
    sgl_obj_t *chart = sgl_barchart_create(parent);
    sgl_obj_set_pos(chart, 0, 0);
    sgl_obj_set_size(chart, SGL_SCREEN_WIDTH, SGL_SCREEN_HEIGHT/2);

    /* 设置序列数量 */
    sgl_barchart_set_series_count(chart, 2);

    /* 绑定序列 Y 数据数组 */
    sgl_barchart_set_series_y_array(chart, 0, sgd_bar_y1, 5);
    sgl_barchart_set_series_y_array(chart, 1, sgd_bar_y2, 5);

    /* 设置序列颜色与透明度 */
    sgl_barchart_set_series_color(chart, 0, SGL_COLOR_DODGER_BLUE, SGL_ALPHA_MAX);
    sgl_barchart_set_series_color(chart, 1, SGL_COLOR_ORANGE, SGL_ALPHA_MAX);

    /* 设置序列标签 */
    sgl_barchart_set_series_label(chart, 0, "Series1");
    sgl_barchart_set_series_label(chart, 1, "Series2");

    /* 设置 X 轴分类标签 */
    sgl_barchart_set_x_labels(chart, sgd_bar_x_labels, 5);

    /* Y 轴：设置固定范围（关闭自动缩放） */
    sgl_barchart_set_axis_range(chart, SGL_BARCHART_AXIS_Y, 0, 100);

    /* X 轴：使能自动缩放 */
    sgl_barchart_enable_axis_auto_scale(chart, SGL_BARCHART_AXIS_X, true);

    /* 设置 Y 轴刻度步长 */
    sgl_barchart_set_axis_step(chart, SGL_BARCHART_AXIS_Y, 25);

    /* 设置自动刻度划分数（step 为 0 时生效） */
    sgl_barchart_set_axis_auto_divisions(chart, SGL_BARCHART_AXIS_Y, 4);

    /* 使能 X/Y 轴网格线 */
    sgl_barchart_enable_axis_grid(chart, SGL_BARCHART_AXIS_X, true);
    sgl_barchart_enable_axis_grid(chart, SGL_BARCHART_AXIS_Y, true);

    /* 设置网格线样式（0=实线，非0=虚线） */
    sgl_barchart_set_axis_grid_style(chart, SGL_BARCHART_AXIS_Y, 1);

    /* 设置网格线颜色与透明度 */
    sgl_barchart_set_axis_grid_color(chart, SGL_BARCHART_AXIS_Y, SGL_COLOR_GRAY, 80);

    /* 使能坐标轴刻度标签 */
    sgl_barchart_enable_axis_labels(chart, SGL_BARCHART_AXIS_X, true);
    sgl_barchart_enable_axis_labels(chart, SGL_BARCHART_AXIS_Y, true);

    /* 设置坐标轴标签字体 */
    sgl_barchart_set_axis_label_font(chart, SGL_BARCHART_AXIS_Y, &consolas14);

    /* 设置坐标轴标签颜色与透明度 */
    sgl_barchart_set_axis_label_color(chart, SGL_BARCHART_AXIS_Y, SGL_COLOR_WHITE, SGL_ALPHA_MAX);
		
    /* 使能坐标轴边缘刻度线 */
    sgl_barchart_enable_axis_ticks(chart, SGL_BARCHART_AXIS_X, true);

    /* 设置图表背景颜色与透明度 */
    sgl_barchart_set_bg_color(chart, SGL_COLOR_BLACK);
    sgl_barchart_set_bg_alpha(chart, SGL_ALPHA_MAX);

    /* 设置图表边框颜色 */
    sgl_barchart_set_border_color(chart, SGL_COLOR_DARK_GRAY);

    /* 设置图表全局透明度 */
    sgl_barchart_set_alpha(chart, SGL_ALPHA_MAX);

    /* 设置柱间距与分类间距 */
    sgl_barchart_set_bar_spacing(chart, 2, 10);

    /* 设置图表方向（垂直/水平） */
    sgl_barchart_set_orientation(chart, SGL_BARCHART_ORIENTATION_VERTICAL);

    /* 使能打开动画 */
    sgl_barchart_enable_open_anim(chart, true);
    sgl_barchart_set_open_anim_dir(chart, SGL_BARCHART_OPEN_ANIM_FROM_BOTTOM);
    sgl_barchart_set_open_anim_duration(chart, 600);
    sgl_barchart_set_open_anim_path(chart, SGL_ANIM_PATH_EASE_OUT);

    /* 自定义绘图区域（相对控件左上角） */
    sgl_barchart_set_plot_area_rel(chart, 0, 0, 280, 380);

    /* 重置绘图区域为自动布局 */
    sgl_barchart_reset_plot_area(chart);

    /* 设置自动布局内边距 */
    //sgl_barchart_set_layout_padding(chart, 30, 20, 10, 20);

    /* 请求重绘（数据有更新时使用） */
    sgl_barchart_update(chart);

    /* 更新单个数据点并请求重绘 */
    sgl_barchart_update_value(chart, 0, 0);
}
#endif
