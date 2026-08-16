/**
 * @file    sgl_polygon_demo.c
 * @brief   SGL Polygon 多边形控件 Demo — 覆盖所有 sgl_polygon_xxx 接口
 */
#include "sgl_demo.h"
#include <math.h>
#if SGD_ENABLE_POLYGON

static void create_star_polygon(sgl_obj_t *parent,
                                int16_t cx,
                                int16_t cy,
                                int16_t outer_r,
                                float rotate_deg)
{
    sgl_obj_t *star;
    int16_t x[10];
    int16_t y[10];
    float angle_step = 36.0f;
    float inner_r = outer_r * 0.381966f;
    int16_t size = (int16_t)(outer_r * 2 + 4);
    int16_t local_cx = size / 2;
    int16_t local_cy = size / 2;

    for (int i = 0; i < 10; i++) {
        float radius = (i % 2 == 0) ? (float)outer_r : inner_r;
        float angle = (-90.0f + rotate_deg) + angle_step * i;
        float rad = angle * 3.14159265f / 180.0f;
        x[i] = (int16_t)(local_cx + radius * cosf(rad));
        y[i] = (int16_t)(local_cy + radius * sinf(rad));
    }

    star = sgl_polygon_create(parent);
    sgl_obj_set_pos(star, cx - local_cx, cy - local_cy);
    sgl_obj_set_size(star, size, size);
    sgl_polygon_set_vertex_coords(star, x, y, 10);
    sgl_polygon_set_fill_color(star, SGL_COLOR_YELLOW);
    sgl_polygon_set_border_width(star, 1);
    sgl_polygon_set_alpha(star, SGL_ALPHA_MAX);
}

void sgd_polygon_demo(sgl_obj_t *parent)
{
    /* 创建一个三角形 */
    sgl_obj_t *duobian1 = sgl_polygon_create(parent);
    sgl_obj_set_pos(duobian1, 20, 30);
    sgl_obj_set_size(duobian1, 120, 120);

    /* 设置顶点坐标 */
    {
        int16_t x[] = {60, 10, 110};
        int16_t y[] = {10, 110, 110};
        sgl_polygon_set_vertex_coords(duobian1, x, y, 3);
    }

    /* 设置填充颜色（青色）*/
    sgl_polygon_set_fill_color(duobian1, SGL_COLOR_CYAN);

    /* 设置边框颜色 */
    sgl_polygon_set_border_color(duobian1, SGL_COLOR_NAVY);

    /* 设置边框宽度 */
    sgl_polygon_set_border_width(duobian1, 3);

    /* 设置透明度 */
    sgl_polygon_set_alpha(duobian1, 200);

    /* 设置显示文本 */
    sgl_polygon_set_text(duobian1, "Tri");

    /* 设置文本字体 */
    sgl_polygon_set_font(duobian1, &consolas14);

    /* 设置文本颜色 */
    sgl_polygon_set_text_color(duobian1, SGL_COLOR_BLACK);

    /* 创建第二个多边形（五边形，不同颜色）*/
    sgl_obj_t *duobian2 = sgl_polygon_create(parent);
    sgl_obj_set_pos(duobian2, 160, 30);
    sgl_obj_set_size(duobian2, 140, 120);
    {
        int16_t x[] = {70, 10, 30, 110, 130};
        int16_t y[] = {10, 45, 110, 110, 45};
        sgl_polygon_set_vertex_coords(duobian2, x, y, 5);
    }
    sgl_polygon_set_fill_color(duobian2, SGL_COLOR_GOLD);
    sgl_polygon_set_border_color(duobian2, SGL_COLOR_BROWN);
    sgl_polygon_set_border_width(duobian2, 0);
    sgl_polygon_set_alpha(duobian2, 220);
    sgl_polygon_set_text(duobian2, "Pent");
    sgl_polygon_set_font(duobian2, &consolas14);
    sgl_polygon_set_text_color(duobian2, SGL_COLOR_BLACK);

    /* ================================================================
     * 3) 下半屏五星红旗 — 红色矩形作旗面，多边形绘制五角星
     * ================================================================ */
    {
        /*
         * 旗面使用 30:20 的常见国旗比例，优先按屏宽计算，
         * 同时限制在下半屏可用高度内，避免不同分辨率下溢出屏幕。
         */
        int16_t flag_w = SGD_W;
        int16_t flag_h = sgl_min((int16_t)(flag_w * 2 / 3),
                                 (int16_t)(SGL_SCREEN_HEIGHT * 2 / 5));
        int16_t flag_x = SGD_MG;
        int16_t flag_y = SGL_SCREEN_HEIGHT - flag_h - SGD_MG;
        int16_t unit = flag_h / 20;
        int16_t big_cx = 5 * unit;
        int16_t big_cy = 5 * unit;
        const int16_t small_pos[4][2] = {
            {10, 2}, {12, 4}, {12, 7}, {10, 9},
        };

        sgl_obj_t *flag = sgl_rect_create(parent);
        sgl_obj_set_pos(flag, flag_x, flag_y-120);
        sgl_obj_set_size(flag, flag_w, flag_h);
        sgl_rect_set_color(flag, SGL_COLOR_RED);
        sgl_rect_set_alpha(flag, SGL_ALPHA_MAX);
        sgl_rect_set_radius(flag, 0);
        sgl_rect_set_border_width(flag, 0);

        create_star_polygon(flag, big_cx, big_cy, 3 * unit, 0.0f);

        for (int i = 0; i < 4; i++) {
            int16_t star_cx = small_pos[i][0] * unit;
            int16_t star_cy = small_pos[i][1] * unit;
            float toward_big = atan2f((float)(big_cy - star_cy),
                                      (float)(big_cx - star_cx)) * 180.0f / 3.14159265f;

            create_star_polygon(flag, star_cx, star_cy, unit, toward_big + 90.0f);
        }
    }
}
#endif
