/**
 ****************************************************************************************************
 * @file        sgl_label_demo.c
 * @brief       SGL Label 功能演示例程 — 覆盖所有 Label API 接口
 *             所有坐标均基于 SGL_SCREEN_WIDTH / HEIGHT 动态计算，方便屏幕迁移
 ****************************************************************************************************
 */
#include "sgl_demo.h"
#if SGD_ENABLE_LABEL



/* 屏幕尺寸 — 动态获取，方便迁移 */
#define LBL_MARGIN      4
#define LBL_H           (28)
#define LBL_GAP         2
#define LBL_W           (SGL_SCREEN_WIDTH - LBL_MARGIN * 2)

/* ========== 全局标签对象 ========== */
static sgl_obj_t *label_fmt_buffer;    /* 格式化文本（静态缓冲区） */
static sgl_obj_t *label_fmt_dynamic;   /* 格式化文本（动态内存）   */
static sgl_obj_t *label_update;        /* 演示 update_text        */

static char fmt_buf[64];               /* 格式化文本的静态缓冲区   */
static char update_buf[64];            /* update_text 演示缓冲区   */

static uint32_t fmt_counter = 0;

/* ========== 图标字体 UTF-8 宏 ========== */
#define SGL_ICON_2103_USER_NAME "\xE2\x84\x83"
#define SGL_ICON_E656_USER_NAME "\xEE\x99\x96"
#define SGL_ICON_E65D_USER_NAME "\xEE\x99\x9D"
#define SGL_ICON_E665_USER_NAME "\xEE\x99\xA5"
#define SGL_ICON_E66B_USER_NAME "\xEE\x99\xAB"
#define SGL_ICON_E766_USER_NAME "\xEE\x9D\xA6"

/* ========== 创建一个标签的帮助函数 ==========
 * 注意：必须先设置字体，再设置文本！
 *       sgl_label_set_text 内部会用 font 计算文本框区域，
 *       如果 font 为 NULL，区域会计算为 SGL_AREA_INVALID，导致绘制异常。
 */
static sgl_obj_t *create_label(sgl_obj_t *parent, int16_t x, int16_t y,
                                int16_t w, int16_t h,
                                const char *text,
                                const sgl_font_t *font,
                                sgl_color_t text_color,
                                sgl_color_t bg_color)
{
    sgl_obj_t *lbl = sgl_label_create(parent);
    sgl_obj_set_pos(lbl, x, y);
    sgl_obj_set_size(lbl, w, h);

    /* 字体必须在文本之前设置！ */
    sgl_label_set_font(lbl, font);
    sgl_label_set_text(lbl, text);

    sgl_label_set_text_color(lbl, text_color);
    sgl_label_set_bg_color(lbl, bg_color);
    sgl_label_set_radius(lbl, 4);
    return lbl;
}

/* ========== 按钮事件回调 ========== */

/* FMT+ 按钮：更新两个格式化标签 */
static void on_switch_fmt_btn_click(sgl_event_t *e)
{
    if (e->type == SGL_EVENT_CLICKED)
    {
        fmt_counter++;
        /* 静态缓冲区方式 — 需先设置过 text_buffer */
        sgl_label_set_text_fmt(label_fmt_buffer, "Value = %d", (int)fmt_counter);
        /* 动态内存方式 */
        sgl_label_set_text_fmt_dynamic(label_fmt_dynamic, "Count = %d (0x%04X)",
                                        (int)fmt_counter,
                                        (unsigned int)(fmt_counter & 0xFFFF));
    }
}

/* Update 按钮：修改缓冲区后调用 sgl_label_set_text_fmt 更新区域 */
static void on_switch_btn_click(sgl_event_t *e)
{
    if (e->type == SGL_EVENT_CLICKED)
    {
        static uint32_t cnt = 0;
        cnt++;

        sgl_label_set_text_fmt(label_update, "[6] Updated x%d", (int)cnt);
    }
}

/* ========== 创建所有标签 ========== */
void sgd_label_demo(sgl_obj_t *parent)
{
    int16_t y = 4;
    const int16_t mg = LBL_MARGIN;
    const int16_t lw = LBL_W;
    const int16_t lh = LBL_H;

    /* ---------------------------------------------------------------
     * 1) 静态文本 — 基础用法
     *    API: sgl_label_create, sgl_label_set_text, sgl_label_set_font
     *         sgl_label_set_text_color, sgl_label_set_bg_color, sgl_label_set_radius
     * --------------------------------------------------------------- */
    create_label(parent, mg, y, lw, lh,
                 "[1] Static Label - Hello SGL!",
                 &consolas14, SGL_COLOR_WHITE, SGL_COLOR_DARK_GRAY);
    y += lh + LBL_GAP;

    /* ---------------------------------------------------------------
     * 2) 自定义颜色 + consolas14 字体
     * --------------------------------------------------------------- */
    create_label(parent, mg, y, lw, lh,
                 "[2] Yellow on SaddleBrown",
                 &consolas14, SGL_COLOR_YELLOW, SGL_COLOR_SADDLE_BROWN);
    y += lh + LBL_GAP;

    /* ---------------------------------------------------------------
     * 3) consolas23 大字体
     *    注意：行高要适应大字
     * --------------------------------------------------------------- */
    {
        sgl_obj_t *lbl = sgl_label_create(parent);
        sgl_obj_set_pos(lbl, mg, y);
        sgl_obj_set_size(lbl, lw, 32);
        sgl_label_set_font(lbl, &ChironGoRoundTC_700B_24);
        sgl_label_set_text(lbl,SGL_ICON_E65D_USER_NAME "[3]ICON TEST"SGL_ICON_E656_USER_NAME);
        sgl_label_set_text_color(lbl, SGL_COLOR_CYAN);
        sgl_label_set_bg_color(lbl, SGL_COLOR_NAVY);
        sgl_label_set_radius(lbl, 4);
        y += 32 + LBL_GAP;
    }

    /* ---------------------------------------------------------------
     * 4) 格式化文本（静态缓冲区）— set_text_buffer + set_text_fmt
     *    API: sgl_label_set_text_buffer, sgl_label_set_text_fmt
     * --------------------------------------------------------------- */
    {
        label_fmt_buffer = sgl_label_create(parent);
        sgl_obj_set_pos(label_fmt_buffer, mg, y);
        sgl_obj_set_size(label_fmt_buffer, lw, lh);
        sgl_label_set_font(label_fmt_buffer, &consolas14);
        /* 先设置缓冲区，再使用格式化写入 */
        sgl_label_set_text_buffer(label_fmt_buffer, fmt_buf, sizeof(fmt_buf));
        sgl_label_set_text_fmt(label_fmt_buffer, "[4] Fmt(buf): %d", 0);
        sgl_label_set_text_color(label_fmt_buffer, SGL_COLOR_LIME);
        sgl_label_set_bg_color(label_fmt_buffer, SGL_COLOR_DARK_GREEN);
        sgl_label_set_radius(label_fmt_buffer, 4);
        y += lh + LBL_GAP;
    }

    /* ---------------------------------------------------------------
     * 5) 格式化文本（动态内存）— set_text_fmt_dynamic
     *    API: sgl_label_set_text_fmt_dynamic
     * --------------------------------------------------------------- */
    {
        label_fmt_dynamic = sgl_label_create(parent);
        sgl_obj_set_pos(label_fmt_dynamic, mg, y);
        sgl_obj_set_size(label_fmt_dynamic, lw, lh);
        sgl_label_set_font(label_fmt_dynamic, &consolas14);
        sgl_label_set_text_fmt_dynamic(label_fmt_dynamic, "[5] Fmt(dyn): initial");
        sgl_label_set_text_color(label_fmt_dynamic, SGL_COLOR_MAGENTA);
        sgl_label_set_bg_color(label_fmt_dynamic, SGL_COLOR_DARK_VIOLET);
        sgl_label_set_radius(label_fmt_dynamic, 4);
        y += lh + LBL_GAP;
    }

    /* ---------------------------------------------------------------
     * 6) 格式化文本（手动内存）— 绑定缓冲区后使用 set_text_fmt 更新
     *    API: sgl_label_set_text_buffer, sgl_label_set_text_fmt
     * --------------------------------------------------------------- */
    {
        label_update = sgl_label_create(parent);
        sgl_obj_set_pos(label_update, mg, y);
        sgl_obj_set_size(label_update, lw, lh);
        sgl_label_set_font(label_update, &consolas14);
        /* 先绑定缓冲区（内部会 buf[0]='\0'），再格式化写入并更新区域 */
        sgl_label_set_text_buffer(label_update, update_buf, sizeof(update_buf));
        sgl_label_set_text_fmt(label_update, "[6] Update Text Demo");
        sgl_label_set_text_color(label_update, SGL_COLOR_WHITE);
        sgl_label_set_bg_color(label_update, SGL_COLOR_TEAL);
        sgl_label_set_radius(label_update, 4);
        y += lh + LBL_GAP;
    }

    /* ---------------------------------------------------------------
     * 7) get_text — 读取文本内容并显示
     *    API: sgl_label_get_text
     * --------------------------------------------------------------- */
    {
        /* 源标签（字体在前，文本在后） */
        sgl_obj_t *src = sgl_label_create(parent);
        sgl_obj_set_pos(src, mg, y);
        sgl_obj_set_size(src, lw / 2 - 1, lh);
        sgl_label_set_font(src, &consolas14);
        sgl_label_set_text(src, "GetTextSrc");
        sgl_label_set_text_color(src, SGL_COLOR_WHITE);
        sgl_label_set_bg_color(src, SGL_COLOR_DODGER_BLUE);
        sgl_label_set_radius(src, 4);

        /* 显示 get_text 的结果（字体在前，文本在后）
         * 注意：必须用持久化缓冲区！绝不能将栈上局部变量的地址赋给 label->text，
         *       否则 text 会成为悬空指针，绘制时读取已回收的栈内存产生随机字符。  */
        sgl_obj_t *info = sgl_label_create(parent);
        sgl_obj_set_pos(info, mg + lw / 2 + 1, y);
        sgl_obj_set_size(info, lw / 2 - 1, lh);
        sgl_label_set_font(info, &consolas14);
        {
            static char info_buf[32];   /* 持久缓冲区，不会被回收 */
            char *got = sgl_label_get_text(src);
            snprintf(info_buf, sizeof(info_buf), "Got:\"%s\"", got ? got : "NULL");
            sgl_label_set_text(info, info_buf);
        }
        sgl_label_set_text_color(info, SGL_COLOR_WHITE);
        sgl_label_set_bg_color(info, SGL_COLOR_DARK_CYAN);
        sgl_label_set_radius(info, 4);
        y += lh + LBL_GAP;
    }

    /* ---------------------------------------------------------------
     * 8) 文本对齐演示 — 左 / 中 / 右
     *    API: sgl_label_set_text_align
     * --------------------------------------------------------------- */
    {
        int16_t col_w = lw / 3 - 1;

        sgl_obj_t *l = sgl_label_create(parent);
        sgl_obj_set_pos(l, mg, y);
        sgl_obj_set_size(l, col_w, lh);
        sgl_label_set_font(l, &consolas14);
        sgl_label_set_text(l, "Left");
        sgl_label_set_text_align(l, SGL_ALIGN_LEFT_MID);
        sgl_label_set_text_color(l, SGL_COLOR_WHITE);
        sgl_label_set_bg_color(l, SGL_COLOR_DARK_GRAY);
        sgl_label_set_radius(l, 4);

        sgl_obj_t *c = sgl_label_create(parent);
        sgl_obj_set_pos(c, mg + col_w + 1, y);
        sgl_obj_set_size(c, col_w, lh);
        sgl_label_set_font(c, &consolas14);
        sgl_label_set_text(c, "Center");
        sgl_label_set_text_align(c, SGL_ALIGN_CENTER);
        sgl_label_set_text_color(c, SGL_COLOR_YELLOW);
        sgl_label_set_bg_color(c, SGL_COLOR_DARK_GRAY);
        sgl_label_set_radius(c, 4);

        sgl_obj_t *r = sgl_label_create(parent);
        sgl_obj_set_pos(r, mg + 2 * (col_w + 1), y);
        sgl_obj_set_size(r, col_w, lh);
        sgl_label_set_font(r, &consolas14);
        sgl_label_set_text(r, "Right");
        sgl_label_set_text_align(r, SGL_ALIGN_RIGHT_MID);
        sgl_label_set_text_color(r, SGL_COLOR_CYAN);
        sgl_label_set_bg_color(r, SGL_COLOR_DARK_GRAY);
        sgl_label_set_radius(r, 4);
        y += lh + LBL_GAP;
    }

    /* ---------------------------------------------------------------
     * 9) 文字偏移
     *    API: sgl_label_set_text_offset
     * --------------------------------------------------------------- */
    {
        sgl_obj_t *lbl = sgl_label_create(parent);
        sgl_obj_set_pos(lbl, mg, y);
        sgl_obj_set_size(lbl, lw, lh);
        sgl_label_set_font(lbl, &consolas14);
        sgl_label_set_text(lbl, "[9] Offset(+5)");
        sgl_label_set_text_offset(lbl, 5);
        sgl_label_set_text_color(lbl, SGL_COLOR_WHITE);
        sgl_label_set_bg_color(lbl, SGL_COLOR_OLIVE);
        sgl_label_set_radius(lbl, 4);
        y += lh + LBL_GAP;
    }

    /* ---------------------------------------------------------------
     * 10) 半透明 (alpha)
     *     API: sgl_label_set_alpha
     * --------------------------------------------------------------- */
    {
        sgl_obj_t *lbl = sgl_label_create(parent);
        sgl_obj_set_pos(lbl, mg, y);
        sgl_obj_set_size(lbl, lw, lh);
        sgl_label_set_font(lbl, &consolas14);
        sgl_label_set_text(lbl, "[10] Alpha=100 (semi)");
        sgl_label_set_alpha(lbl, 100);
        sgl_label_set_text_color(lbl, SGL_COLOR_WHITE);
        sgl_label_set_bg_color(lbl, SGL_COLOR_RED);
        sgl_label_set_radius(lbl, 4);
        y += lh + LBL_GAP;
    }

    /* ---------------------------------------------------------------
     * 11) 字体滚动显示 — sgl_label_set_long_mode
     *     API: sgl_label_set_long_mode
     *     @note 文本必须超出标签宽度才会滚动，需先 set_text 再开启
     * --------------------------------------------------------------- */
    {
        sgl_obj_t *lbl = sgl_label_create(parent);
        sgl_obj_set_pos(lbl, mg, y);
        sgl_obj_set_size(lbl, lw, lh);
        sgl_label_set_font(lbl, &consolas14);
        sgl_label_set_text(lbl, "[11] Scrolling text ... long text overflow label width ... ");
        sgl_label_set_text_color(lbl, SGL_COLOR_WHITE);
        sgl_label_set_bg_color(lbl, SGL_COLOR_DARK_VIOLET);
        sgl_label_set_radius(lbl, 4);
        sgl_label_set_long_mode(lbl, 10, true);
        y += lh + LBL_GAP;
    }

    /* ===============================================================
     * 操作按钮 — 点击触发动态更新
     * =============================================================== */
    {
        int16_t btn_w = lw / 3 - 1;
        int16_t btn_h = 30;

        sgl_obj_t *b1 = sgl_button_create(parent);
        sgl_obj_set_pos(b1, mg, y);
        sgl_obj_set_size(b1, btn_w, btn_h);
        sgl_button_set_font(b1, &consolas14);
        sgl_button_set_text(b1, "Fmt+");
        sgl_button_set_radius(b1, 4);
        sgl_obj_set_event_cb(b1, on_switch_fmt_btn_click, NULL);

        sgl_obj_t *b2 = sgl_button_create(parent);
        sgl_obj_set_pos(b2, mg + btn_w + 1, y);
        sgl_obj_set_size(b2, btn_w, btn_h);
        sgl_button_set_font(b2, &consolas14);
        sgl_button_set_text(b2, "Update");
        sgl_button_set_radius(b2, 4);
        sgl_obj_set_event_cb(b2, on_switch_btn_click, NULL);
    }
}
#endif
