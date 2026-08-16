/**
 * @file    sgl_canvas_demo.c
 * @brief   SGL Canvas 画布控件 Demo — 覆盖所有 sgl_canvas_xxx 接口
 *          上半部分随意画各种图形，下半部分手指触摸画轨迹
 */
#include "sgl_demo.h"
#if SGD_ENABLE_CANVAS

#define RING_SZ  256
#define INVALID_PT  (-1)

/* 环形缓冲区 */
static int16_t g_px[RING_SZ];
static int16_t g_py[RING_SZ];
static int g_head = 0;      /* 写入位置 */
static int g_cnt  = 0;      /* 有效点数 */

static void canvas_add_point(int16_t x, int16_t y)
{
    g_px[g_head] = x;
    g_py[g_head] = y;
    g_head = (g_head + 1) % RING_SZ;
    if (g_cnt < RING_SZ) g_cnt++;
}

static void canvas_add_break(void)
{
    if (g_cnt > 0) {
        int last = (g_head - 1 + RING_SZ) % RING_SZ;
        if (g_px[last] == INVALID_PT) return;
    }
    canvas_add_point(INVALID_PT, INVALID_PT);
}

/* 画布绘制回调 */
static void huabu_painter(sgl_surf_t *surf, sgl_area_t *area, sgl_obj_t *obj)
{
    int x1 = obj->coords.x1, x2 = obj->coords.x2;
    int y1 = obj->coords.y1, y2 = obj->coords.y2;
    int mid_y = (y1 + y2) / 2;

    /* 上半部分 — 各种图形展示 */
    sgl_area_t bg = {x1, y1, x2, mid_y};
    sgl_draw_fill_rect(surf, area, &bg, 0, sgl_rgb(0x15, 0x15, 0x25), 255);

    sgl_area_t r1 = {x1 + 10, y1 + 10, x1 + 70, y1 + 50};
    sgl_draw_fill_rect(surf, area, &r1, 4, SGL_COLOR_CYAN, 200);
    sgl_draw_fill_circle(surf, area, x1 + 120, y1 + 30, 20, SGL_COLOR_RED, 200);
    sgl_area_t r2 = {x1 + 180, y1 + 10, x1 + 260, y1 + 50};
    sgl_draw_fill_rect(surf, area, &r2, 0, SGL_COLOR_GREEN, 180);

    sgl_draw_line_t l1 = {.alpha = 220, .width = 2, .color = SGL_COLOR_YELLOW,
        .x1 = x1 + 10, .y1 = y1 + 70, .x2 = x1 + 70, .y2 = y1 + 110};
    sgl_draw_line(surf, area, &l1);
    sgl_draw_line_t l2 = {.alpha = 220, .width = 2, .color = SGL_COLOR_YELLOW,
        .x1 = x1 + 70, .y1 = y1 + 70, .x2 = x1 + 10, .y2 = y1 + 110};
    sgl_draw_line(surf, area, &l2);
    sgl_draw_fill_circle_border(surf, area, x1 + 120, y1 + 90, 22, SGL_COLOR_MAGENTA, 4, 220);

    for (int y = y1 + 130; y < mid_y; y += 12)
        sgl_draw_fill_hline(surf, area, y, x1 + 10, x2 - 10, 1, SGL_COLOR_ORANGE, 100);
    for (int x = x1 + 10; x < x2; x += 20) {
        sgl_area_t line = {x, y1 + 130, x + 1, mid_y - 5};
        sgl_draw_fill_rect(surf, area, &line, 0, SGL_COLOR_ORANGE, 80);
    }

    /* 下半部分 — 手指触摸轨迹 */
    bg.y1 = mid_y + 1; bg.y2 = y2;
    /* 整屏刷新时才填背景，局部更新只画线不清除旧内容 */
    if (area->y1 <= mid_y + 1 && area->y2 >= y2 - 1) {
        sgl_draw_fill_rect(surf, area, &bg, 0, sgl_rgb(0x10, 0x10, 0x10), 255);
    }
    sgl_draw_fill_hline(surf, area, mid_y, x1, x2, 2, SGL_COLOR_WHITE, 150);

    /* 绘制触摸轨迹连线 + 点 */
    {
        int _start = (g_head - g_cnt + RING_SZ) % RING_SZ;
        for (int _i = 0; _i < g_cnt; _i++) {
            int idx = (_start + _i) % RING_SZ;
            if (g_px[idx] == INVALID_PT) continue;
            sgl_draw_fill_circle(surf, area, g_px[idx], g_py[idx], 3, SGL_COLOR_CYAN, 255);
            if (_i > 0) {
                int prev = (_start + _i - 1) % RING_SZ;
                if (g_px[prev] != INVALID_PT) {
                    sgl_draw_line_t seg = {.alpha = 230, .width = 3, .color = SGL_COLOR_CYAN,
                        .x1 = g_px[prev], .y1 = g_py[prev],
                        .x2 = g_px[idx],  .y2 = g_py[idx]};
                    sgl_draw_line(surf, area, &seg);
                }
            }
        }
    }
}

/* 触摸回调：注册在画布上，sgl_obj_set_movable 确保 MOTION 能到达 */
static void huabu_touch(sgl_event_t *e)
{
    sgl_obj_t *obj = e->obj;
    int mid_y = (obj->coords.y1 + obj->coords.y2) / 2;
    bool in_lower = e->pos.x >= obj->coords.x1 && e->pos.x <= obj->coords.x2 &&
                    e->pos.y > mid_y && e->pos.y <= obj->coords.y2;

    /* 记录坐标（PRESSED / MOVE_* / MOTION）*/
    if (e->type == SGL_EVENT_PRESSED || e->type == SGL_EVENT_MOTION ||
        e->type == SGL_EVENT_MOVE_DOWN || e->type == SGL_EVENT_MOVE_UP ||
        e->type == SGL_EVENT_MOVE_LEFT || e->type == SGL_EVENT_MOVE_RIGHT) {
        if (!in_lower) return;

        int min_x = e->pos.x - 5, min_y = e->pos.y - 5;
        int max_x = e->pos.x + 5, max_y = e->pos.y + 5;
        if (g_cnt > 0) {
            int last = (g_head - 1 + RING_SZ) % RING_SZ;
            if (g_px[last] != INVALID_PT) {
                int px = g_px[last], py = g_py[last];
                if (px < min_x) min_x = px;
                if (py < min_y) min_y = py;
                if (px > max_x) max_x = px;
                if (py > max_y) max_y = py;
            }
        }
        sgl_area_t da = {min_x, min_y, max_x, max_y};
        canvas_add_point(e->pos.x, e->pos.y);
        sgl_dirty_area_push(&da);
        return;
    }

    /* CLICKED 兜底 */
    if (e->type == SGL_EVENT_CLICKED) {
        if (!in_lower) return;
        canvas_add_point(e->pos.x, e->pos.y);
        sgl_area_t da = {e->pos.x - 5, e->pos.y - 5, e->pos.x + 5, e->pos.y + 5};
        sgl_dirty_area_push(&da);
        return;
    }

    /* RELEASED：断笔标记，只标记不刷脏 */
    if (e->type == SGL_EVENT_RELEASED) {
        if (!in_lower && g_cnt == 0) return;
        canvas_add_break();
    }
}

void sgd_canvas_demo(sgl_obj_t *parent)
{
    sgl_obj_t *huabu = sgl_canvas_create(parent);
    sgl_obj_set_pos(huabu, 5, 5);
    sgl_obj_set_size(huabu, SGL_SCREEN_WIDTH - 10, SGL_SCREEN_HEIGHT - 10);
    sgl_canvas_set_painter_cb(huabu, huabu_painter);

    /* 设为可移动，使 MOTION / MOVE_* 事件能到达画布 */
    sgl_obj_set_movable(huabu);

    /* 事件回调注册在画布上 */
    sgl_obj_set_event_cb(huabu, huabu_touch, NULL);
    sgl_canvas_set_private(huabu, NULL);
}
#endif
