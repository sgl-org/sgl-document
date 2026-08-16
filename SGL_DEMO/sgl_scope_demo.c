/**
 * @file    sgl_scope_demo.c
 * @brief   SGL Scope 示波器控件 Demo — 正弦波实时显示
 */
#include "sgl_demo.h"
#include <math.h>
#if SGD_ENABLE_SCOPE

/* ---------- 配置 ---------- */

#define SCOPE_DATA_LEN       (128)   /* 环形缓冲区长度 */
#define SCOPE_TIMER_INTERVAL (30)    /* 定时器间隔 ms */
#define SCOPE_MAX_POINTS     (64)   /* 最大显示点数 */

/* 正弦波参数 */
#define SINE_FREQ_HZ         (2.0)   /* 信号频率 Hz */
#define SINE_AMPLITUDE       (1500)  /* 信号幅值 */
#define SINE_OFFSET          (1500)  /* 直流偏置 (0~3000 范围) */

/* ---------- 静态数据 ---------- */

static sgl_obj_t      *scope_obj   = NULL;
static sgl_timer_t    *scope_timer = NULL;
static int16_t        *sine_buffer = NULL;
static uint32_t        sample_count = 0;  /* 累计采样计数，用于生成连续正弦波 */

/**
 * @brief 定时器回调：生成正弦波采样点并追加到示波器
 */
static void scope_timer_callback(const sgl_timer_t *timer, void *user_data)
{
    (void)timer;
    (void)user_data;

    if (scope_obj == NULL || sine_buffer == NULL) return;

    float sample_rate = 1000.0f / (float)SCOPE_TIMER_INTERVAL;
    float angle = 2.0f * 3.14159265f * SINE_FREQ_HZ * (float)sample_count / sample_rate;
    int16_t value = (int16_t)(SINE_OFFSET + SINE_AMPLITUDE * sinf(angle));

    /* 追加到示波器通道 0 */
    sgl_scope_append_data(scope_obj, 0, value);
    sample_count++;
}

void sgd_scope_demo(sgl_obj_t *parent)
{
    int screen_w = SGL_SCREEN_WIDTH;
    int screen_h = SGL_SCREEN_HEIGHT;

    /* 创建示波器控件对象 */
    scope_obj = sgl_scope_create(parent);
    if (scope_obj == NULL) {
        SGL_LOG_ERROR("Failed to create scope");
        return;
    }

    /* 设置控件位置（水平居中） */
    sgl_obj_set_pos(scope_obj, (screen_w - screen_w * 4 / 5) / 2,
                              (screen_h - screen_h * 3 / 4) / 2);
    /* 设置控件大小（占屏幕 4/5 宽 × 3/4 高） */
    sgl_obj_set_size(scope_obj, screen_w * 4 / 5, screen_h * 3 / 8);

    /* 设置示波器通道数为 1 */
    sgl_scope_set_channel_count(scope_obj, 1);

    /* 分配数据缓冲区（环形）*/
    sine_buffer = (int16_t *)sgl_malloc(sizeof(int16_t) * SCOPE_DATA_LEN);
    if (sine_buffer == NULL) {
        SGL_LOG_ERROR("Failed to allocate sine buffer");
        return;
    }
    memset(sine_buffer, 0, sizeof(int16_t) * SCOPE_DATA_LEN);

    /* 将缓冲区绑定到通道 0 */
    sgl_scope_set_channel_data_buffer(scope_obj, 0, sine_buffer, SCOPE_DATA_LEN);

    /* 设置通道 0 的波形颜色（绿色）*/
    sgl_scope_set_channel_waveform_color(scope_obj, 0, sgl_rgb(0x00, 0xFF, 0x80));

    /* 设置背景颜色（深色主题）*/
    sgl_scope_set_bg_color(scope_obj, sgl_rgb(0x0A, 0x0A, 0x1A));

    /* 设置网格线颜色 */
    sgl_scope_set_grid_color(scope_obj, sgl_rgb(0x33, 0x33, 0x55));

    /* 设置边框颜色 */
    sgl_scope_set_border_color(scope_obj, sgl_rgb(0x44, 0x44, 0x66));

    /* 设置边框宽度 */
    sgl_scope_set_border_width(scope_obj, 2);

    /* 设置透明度 */
    sgl_scope_set_alpha(scope_obj, 255);

    /* 设置波形线宽 */
    sgl_scope_set_line_width(scope_obj, 1);

    /* 设置网格为虚线样式（参数 大于等于1 代表虚线间隔）*/
    sgl_scope_set_grid_line(scope_obj, 6);

    /* 显示 Y 轴刻度标签 */
    sgl_scope_show_y_labels(scope_obj, true);

    /* 设置 Y 轴标签字体 */
    sgl_scope_set_y_label_font(scope_obj, &consolas32);

    /* 设置 Y 轴标签颜色 */
    sgl_scope_set_y_label_color(scope_obj, sgl_rgb(0xAA, 0xAA, 0xCC));

    /* 启用自动量程（根据数据动态调整 Y 轴范围）*/
    sgl_scope_enable_auto_scale(scope_obj, true);

    /* 限制最大显示点数（防止波型过密）*/
    sgl_scope_set_max_display_points(scope_obj, SCOPE_MAX_POINTS);

    /* 创建定时器，用于周期性追加正弦波数据 */
    sample_count = 0;
    scope_timer = sgl_timer_create();
    if (scope_timer == NULL) {
        SGL_LOG_ERROR("Failed to create scope timer");
        return;
    }

    /* 设置定时器：周期 30ms，无限循环，回调追加数据 */
    if (!sgl_timer_setup(scope_timer, scope_timer_callback,
                         SCOPE_TIMER_INTERVAL, -1, NULL)) {
        SGL_LOG_ERROR("Failed to setup scope timer");
        sgl_timer_delete(scope_timer);
        scope_timer = NULL;
        return;
    }

    SGL_LOG_INFO("Scope demo initialized (sine wave, %d Hz, %d samples/s)",
                 (int)SINE_FREQ_HZ, (int)(1000 / SCOPE_TIMER_INTERVAL));
}
#endif
