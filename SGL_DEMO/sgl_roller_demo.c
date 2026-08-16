/**
 * @file    sgl_roller_demo.c
 * @brief   SGL Roller 滚轮选择器控件 Demo — 覆盖所有 sgl_roller_xxx 接口
 */
#include "sgl_demo.h"
#if SGD_ENABLE_ROLLER

static sgl_obj_t *g_roller_label1 = NULL;
static sgl_obj_t *g_roller_label2 = NULL;

static void roller_update_label(sgl_obj_t *roller, sgl_obj_t *label, const char *prefix)
{
    char buf[32];
    int idx = sgl_roller_get_selected_index(roller);

    if (label == NULL) {
        return;
    }

    if (sgl_roller_get_selected_text(roller, buf, sizeof(buf))) {
        sgl_label_set_text_fmt_dynamic(label, "%s: [%d] %s", prefix, idx, buf);
    } else {
        sgl_label_set_text_fmt_dynamic(label, "%s: [-1] <none>", prefix);
    }
}

static void roller_event_cb(sgl_event_t *e)
{
    if (e->type == SGL_EVENT_PRESSED || e->type == SGL_EVENT_RELEASED ||
        e->type == SGL_EVENT_MOVE_DOWN || e->type == SGL_EVENT_MOVE_UP ||
        e->type == SGL_EVENT_KEY_UP || e->type == SGL_EVENT_KEY_DOWN ||
        e->type == SGL_EVENT_KEY_LEFT || e->type == SGL_EVENT_KEY_RIGHT) {
        sgl_obj_t *label = (sgl_obj_t *)sgl_event_get_data(e);

        if (label == g_roller_label1) {
            roller_update_label(e->obj, label, "Roller 1");
        } else if (label == g_roller_label2) {
            roller_update_label(e->obj, label, "Roller 2");
        }
    }
}

void sgd_roller_demo(sgl_obj_t *parent)
{
    sgl_obj_t *gunlun1 = sgl_roller_create(parent);
    sgl_obj_set_pos(gunlun1, 30, 30);
    sgl_obj_set_size(gunlun1, 120, 120);

    /* 设置选项（动态文本）*/
    sgl_roller_set_option_dynamic(gunlun1, "Red\nGreen\nBlue\nYellow\nPink\nCyan");

    /* 设置可见行数 */
    sgl_roller_set_visible_rows(gunlun1, 5);

    /* 设置文字颜色 */
    sgl_roller_set_text_color(gunlun1, SGL_COLOR_WHITE);

    /* 设置选中项颜色 */
    sgl_roller_set_selected_color(gunlun1, SGL_COLOR_NAVY);

    /* 设置背景颜色 */
    sgl_roller_set_bg_color(gunlun1, SGL_COLOR_DARK_GRAY);

    /* 设置边框颜色 */
    sgl_roller_set_border_color(gunlun1, SGL_COLOR_CYAN);

    /* 设置字体 */
    sgl_roller_set_text_font(gunlun1, &consolas14);

    /* 设置透明度 */
    sgl_roller_set_alpha(gunlun1, 220);

    /* 设置圆角 */
    sgl_roller_set_radius(gunlun1, 4);

    /* 设置边框宽度 */
    sgl_roller_set_border_width(gunlun1, 1);

    /* 获取选中索引和文本 */
    sgl_roller_get_selected_index(gunlun1);
    {
        char buf[32];
        sgl_roller_get_selected_text(gunlun1, buf, sizeof(buf));
    }

    /* 第一个滚轮下方标签：显示当前选中项 */
    g_roller_label1 = sgl_label_create(parent);
    sgl_obj_set_pos(g_roller_label1, 30, 160);
    sgl_obj_set_size(g_roller_label1, 120, 24);
    sgl_label_set_font(g_roller_label1, &consolas14);
    //sgl_label_set_text_color(g_roller_label1, SGL_COLOR_WHITE);

    /* 注册事件：滚动时用 FMT 动态更新下方标签 */
    sgl_obj_set_event_cb(gunlun1, roller_event_cb, g_roller_label1);
    roller_update_label(gunlun1, g_roller_label1, "Roller 1");

    /* 第二个滚轮（静态文本）*/
    sgl_obj_t *gunlun2 = sgl_roller_create(parent);
    sgl_obj_set_pos(gunlun2, 170, 30);
    sgl_obj_set_size(gunlun2, 120, 120);
    sgl_roller_set_option_static(gunlun2, "A\nB\nC\nD\nE\nF");

    /* 打开环形模式：滚到末尾后会继续接回开头 */
    sgl_roller_set_infinite_mode(gunlun2, true);

    sgl_roller_set_visible_rows(gunlun2, 3);
    sgl_roller_set_text_color(gunlun2, SGL_COLOR_GOLD);
    sgl_roller_set_selected_color(gunlun2, SGL_COLOR_GRAY);
    sgl_roller_set_bg_color(gunlun2, SGL_COLOR_DARK_GRAY);
    sgl_roller_set_border_color(gunlun2, SGL_COLOR_GOLD);
    sgl_roller_set_text_font(gunlun2, &consolas23);
    sgl_roller_set_alpha(gunlun2, 200);
    sgl_roller_set_radius(gunlun2, 6);
    sgl_roller_set_border_width(gunlun2, 2);

    /* 第二个滚轮下方标签：显示环形滚轮当前选中项 */
    g_roller_label2 = sgl_label_create(parent);
    sgl_obj_set_pos(g_roller_label2, 170, 160);
    sgl_obj_set_size(g_roller_label2, 120, 24);
    sgl_label_set_font(g_roller_label2, &consolas14);
    //sgl_label_set_text_color(g_roller_label2, SGL_COLOR_WHITE);

    /* 环形滚轮同样通过 FMT 接口动态显示当前选中内容 */
    sgl_obj_set_event_cb(gunlun2, roller_event_cb, g_roller_label2);
    roller_update_label(gunlun2, g_roller_label2, "Roller 2");
}
#endif
