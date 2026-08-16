/**
 * @file    sgl_analogclock_demo.c
 * @brief   SGL AnalogClock 模拟时钟控件 Demo — 覆盖所有接口
 *          接入 SGL 定时器，每秒走一秒，实时运行
 */
#include "sgl_demo.h"
#if SGD_ENABLE_ANALOGCLOCK

static sgl_obj_t *g_zhong = NULL;
static uint8_t g_hour = 10, g_min = 30, g_sec = 45;

/* 定时器回调：每秒加一秒 */
static void clock_timer_cb(const sgl_timer_t *timer, void *user_data)
{
    (void)timer;
    (void)user_data;
    if (g_zhong == NULL) return;

    g_sec++;
    if (g_sec >= 60) {
        g_sec = 0;
        g_min++;
        if (g_min >= 60) {
            g_min = 0;
            g_hour++;
            if (g_hour >= 24) g_hour = 0;
        }
    }
    sgl_analogclock_set_time(g_zhong, g_hour, g_min, g_sec);
}

void sgd_analogclock_demo(sgl_obj_t *parent)
{
    g_zhong = sgl_analogclock_create(parent);
    sgl_obj_set_pos(g_zhong, (SGL_SCREEN_WIDTH - 160) / 2, 20);
    sgl_obj_set_size(g_zhong, 160, 160);

    /* 设置初始时间 */
    sgl_analogclock_set_time(g_zhong, g_hour, g_min, g_sec);

    /* 设置字体 */
    sgl_analogclock_set_font(g_zhong, &consolas14);

    /* 设置背景颜色 */
    sgl_analogclock_set_bg_color(g_zhong, SGL_COLOR_DARK_GRAY);

    /* 设置边框颜色 */
    sgl_analogclock_set_border_color(g_zhong, SGL_COLOR_CYAN);

    /* 设置刻度颜色 */
    sgl_analogclock_set_scale_color(g_zhong, SGL_COLOR_WHITE);

    /* 设置时针颜色 */
    sgl_analogclock_set_hour_ptr_color(g_zhong, SGL_COLOR_CYAN);

    /* 设置分针颜色 */
    sgl_analogclock_set_min_ptr_color(g_zhong, SGL_COLOR_LIME);

    /* 设置秒针颜色 */
    sgl_analogclock_set_sec_ptr_color(g_zhong, SGL_COLOR_RED);

    /* 设置中心轴颜色 */
    sgl_analogclock_set_hub_color(g_zhong, SGL_COLOR_GRAY);

    /* 设置文字颜色 */
    sgl_analogclock_set_text_color(g_zhong, SGL_COLOR_WHITE);

    /* 设置边框宽度 */
    sgl_analogclock_set_border_width(g_zhong, 5);

    /* 设置中心轴半径 */
    sgl_analogclock_set_hub_radius(g_zhong, 5);

    /* 设置刻度宽度 */
    sgl_analogclock_set_scale_width(g_zhong, 2);

    /* 设置时针宽度 */
    sgl_analogclock_set_hour_ptr_width(g_zhong, 3);

    /* 设置分针宽度 */
    sgl_analogclock_set_min_ptr_width(g_zhong, 2);

    /* 设置秒针宽度 */
    sgl_analogclock_set_sec_ptr_width(g_zhong, 1);

    /* 设置透明度 */
    sgl_analogclock_set_alpha(g_zhong, 220);

    /* 创建定时器：每秒触发一次，更新时钟 */
    {
        sgl_timer_t *t = sgl_timer_create();
        if (t) {
            sgl_timer_setup(t, clock_timer_cb, 1000, -1, NULL);
        }
    }
}
#endif
