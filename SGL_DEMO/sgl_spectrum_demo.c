/**
 * @file    sgl_spectrum_demo.c
 * @brief   SGL Spectrum 频谱控件 Demo — 覆盖所有接口
 *          接入定时器，按《小星星》旋律跳动
 */
#include "sgl_demo.h"
#if SGD_ENABLE_SPECTRUM

/* 《小星星》简谱（1=C, 2=D, 3=E, 4=F, 5=G, 6=A），0=休止 */
static const uint8_t g_melody[] = {
    1,1,5,5,6,6,5, 0,
    4,4,3,3,2,2,1, 0,
    5,5,4,4,3,3,2, 0,
    5,5,4,4,3,3,2, 0,
    1,1,5,5,6,6,5, 0,
    4,4,3,3,2,2,1, 0,
};

static sgl_obj_t *g_pu = NULL;
static int g_note_idx = 0;

/* 定时器回调：按节拍更新频谱柱状图 */
static void spec_timer_cb(const sgl_timer_t *timer, void *user_data)
{
    (void)timer;
    (void)user_data;
    if (g_pu == NULL) return;

    uint8_t note = g_melody[g_note_idx];
    g_note_idx++;
    if (g_note_idx >= (int)(sizeof(g_melody) / sizeof(g_melody[0]))) {
        g_note_idx = 0;
    }

    /* 将音符映射到频谱柱：每个音符点亮对应位置的主柱 + 两侧谐波 */
    for (int i = 0; i < 16; i++) {
        uint16_t val = 0;
        if (note > 0) {
            /* 音符 1~6 映射到柱索引 2~13 范围 */
            int center = 2 + note * 2;
            int dist = i - center;
            if (dist == 0) {
                val = 180;          /* 主柱最高 */
            } else if (dist == 1 || dist == -1) {
                val = 120;          /* 邻柱 */
            } else if (dist == 2 || dist == -2) {
                val = 60;           /* 次邻柱 */
            }
            /* 叠加随机微动使频谱更自然 */
            val += (uint16_t)((i * 7 + g_note_idx * 3) % 20);
            if (val > 200) val = 200;
        }
        sgl_spectrum_set_bar_value(g_pu, i, val);
    }
}

void sgd_spectrum_demo(sgl_obj_t *parent)
{
    g_pu = sgl_spectrum_create(parent);
    sgl_obj_set_pos(g_pu, 20, 20);
    sgl_obj_set_size(g_pu, 280, 200);

    /* 设置柱状数量 */
    sgl_spectrum_set_bar_number(g_pu, 16);

    /* 设置柱状模式（柱状带顶线）*/
    sgl_spectrum_set_bar_mode(g_pu, SGL_SPECTRUM_MODE_BAR_HAT);

    /* 设置柱状颜色 */
    sgl_spectrum_set_bar_color(g_pu, SGL_COLOR_CYAN);

    /* 设置顶线颜色 */
    sgl_spectrum_set_bar_hat_color(g_pu, SGL_COLOR_RED);

    /* 设置顶线高度 */
    sgl_spectrum_set_bar_hat_height(g_pu, 4);

    /* 设置透明度 */
    sgl_spectrum_set_alpha(g_pu, 220);

    /* 创建定时器：按节拍播放《小星星》*/
    {
        sgl_timer_t *t = sgl_timer_create();
        if (t) {
            sgl_timer_setup(t, spec_timer_cb, 300, -1, NULL);
        }
    }
}
#endif
