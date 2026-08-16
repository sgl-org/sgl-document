/**
 * @file    sgl_linechart_demo.c
 * @brief   SGL 折线图控件 Demo — 覆盖所有 sgl_linechart_xxx 接口
 *          展示折线/散点模式 + 填充 + 坐标轴/网格 + 打开动画
 */
#include "sgl_demo.h"
#if SGD_ENABLE_LINECHART

/* 第一条折线：X 用索引，Y 为数据（持久存储，图表只保存指针） */
static const int32_t sgd_line_y1[] = { 20, 45, 30, 70, 50, 90, 60 };

/* 第二条折线：使用完整 X/Y 坐标 */
static const int32_t sgd_line_x2[] = { 0, 10, 20, 30, 40, 50, 60 };
static const int32_t sgd_line_y2[] = { 80, 55, 75, 40, 60, 35, 70 };

/* X 轴标签 */
static const char *sgd_line_x_labels[] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };

void sgd_linechart_demo(sgl_obj_t *parent)
{
    /* 创建折线图控件 */
    sgl_obj_t *chart = sgl_linechart_create(parent);
    sgl_obj_set_pos(chart, 0, 0);
    sgl_obj_set_size(chart, SGL_SCREEN_WIDTH, SGL_SCREEN_HEIGHT/2);

    /* 设置序列数量 */
    sgl_linechart_set_series_count(chart, 2);

    /* 序列0：只绑定 Y 数据（X 自动使用索引 0..n-1） */
    sgl_linechart_set_series_y_array(chart, 0, sgd_line_y1, 7);

    /* 序列1：绑定完整 X/Y 数据 */
    sgl_linechart_set_series_data(chart, 1, sgd_line_x2, sgd_line_y2, 7);

    /* 设置序列模式（折线/散点/折线+点） */
    sgl_linechart_set_series_mode(chart, 0, SGL_LINECHART_SERIES_MODE_LINE_AND_POINT);
    sgl_linechart_set_series_mode(chart, 1, SGL_LINECHART_SERIES_MODE_LINE);

    /* 设置序列线颜色与透明度 */
    sgl_linechart_set_series_line_color(chart, 0, SGL_COLOR_CYAN);
    sgl_linechart_set_series_line_color(chart, 1, SGL_COLOR_ORANGE);
    sgl_linechart_set_series_line_alpha(chart, 0, SGL_ALPHA_MAX);
    sgl_linechart_set_series_line_alpha(chart, 1, SGL_ALPHA_MAX);

    /* 设置序列线宽 */
    sgl_linechart_set_series_line_width(chart, 0, 1);
    sgl_linechart_set_series_line_width(chart, 1, 1);

    /* 使能/关闭数据点标记，并设置点形状与半径 */
    sgl_linechart_enable_series_points(chart, 0, true);
    sgl_linechart_set_series_point_style(chart, 0, SGL_LINECHART_POINT_SHAPE_CIRCLE, 3);
    sgl_linechart_set_series_point_style(chart, 1, SGL_LINECHART_POINT_SHAPE_SQUARE, 3);

    /* 使能序列线下方区域填充，并设置填充颜色与透明度 */
    sgl_linechart_enable_series_fill(chart, 0, true);
    sgl_linechart_set_series_fill_color(chart, 0, SGL_COLOR_CYAN, 40);

    /* 设置序列标签 */
    sgl_linechart_set_series_label(chart, 0, "Series1");
    sgl_linechart_set_series_label(chart, 1, "Series2");

    /* 设置 X 轴标签 */
    sgl_linechart_set_x_labels(chart, sgd_line_x_labels, 7);

    /* Y 轴：设置固定范围（关闭自动缩放） */
    sgl_linechart_set_axis_range(chart, SGL_LINECHART_AXIS_Y, 0, 100);

    /* X 轴：使能自动缩放 */
    sgl_linechart_enable_axis_auto_scale(chart, SGL_LINECHART_AXIS_X, true);

    /* 设置 Y 轴刻度步长 */
    sgl_linechart_set_axis_step(chart, SGL_LINECHART_AXIS_Y, 25);

    /* 设置自动刻度划分数（step 为 0 时生效） */
    sgl_linechart_set_axis_auto_divisions(chart, SGL_LINECHART_AXIS_Y, 4);

    /* 使能 X/Y 轴网格线 */
    sgl_linechart_enable_axis_grid(chart, SGL_LINECHART_AXIS_X, true);
    sgl_linechart_enable_axis_grid(chart, SGL_LINECHART_AXIS_Y, true);

    /* 设置网格线样式（0=实线，非0=虚线） */
    sgl_linechart_set_axis_grid_style(chart, SGL_LINECHART_AXIS_Y, 1);

    /* 设置网格线颜色与透明度 */
    sgl_linechart_set_axis_grid_color(chart, SGL_LINECHART_AXIS_Y, SGL_COLOR_GRAY, 80);

    /* 使能坐标轴刻度标签 */
    sgl_linechart_enable_axis_labels(chart, SGL_LINECHART_AXIS_X, true);
    sgl_linechart_enable_axis_labels(chart, SGL_LINECHART_AXIS_Y, true);

    /* 设置坐标轴标签字体 */
    sgl_linechart_set_axis_label_font(chart, SGL_LINECHART_AXIS_Y, &consolas14);

    /* 设置坐标轴标签颜色与透明度 */
    sgl_linechart_set_axis_label_color(chart, SGL_LINECHART_AXIS_Y, SGL_COLOR_WHITE, SGL_ALPHA_MAX);

    /* 使能坐标轴边缘刻度线 */
    sgl_linechart_enable_axis_ticks(chart, SGL_LINECHART_AXIS_X, true);

    /* 设置图表背景颜色与透明度 */
    sgl_linechart_set_bg_color(chart, SGL_COLOR_BLACK);
    sgl_linechart_set_bg_alpha(chart, SGL_ALPHA_MAX);

    /* 设置图表边框颜色 */
    sgl_linechart_set_border_color(chart, SGL_COLOR_DARK_GRAY);

    /* 设置图表全局透明度 */
    sgl_linechart_set_alpha(chart, SGL_ALPHA_MAX);

    /* 自定义绘图区域（相对控件左上角） */
    sgl_linechart_set_plot_area_rel(chart, 30, 10, 280, 380);

    /* 重置绘图区域为自动布局 */
    sgl_linechart_reset_plot_area(chart);

    /* 使能打开动画（从左到右逐段展开） */
    sgl_linechart_enable_open_anim(chart, true);
    sgl_linechart_set_open_anim_dir(chart, SGL_LINECHART_OPEN_ANIM_FROM_LEFT);
    sgl_linechart_set_open_anim_path(chart, SGL_ANIM_PATH_EASE_OUT);

    /* 请求重绘（数据有更新时使用） */
    sgl_linechart_update(chart);

    /* 更新单个数据点并请求重绘 */
    sgl_linechart_update_value(chart, 0, 0);
}
#endif
