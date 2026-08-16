/**
 * @file    sgl_rectangle_demo.c
 * @brief   SGL Rectangle 矩形控件 Demo — 覆盖所有 sgl_rect_xxx 接口

 */
#include "sgl_demo.h"
#if SGD_ENABLE_RECTANGLE

/* 图片资源 */
extern const sgl_pixmap_t pic1_pixmap;

void sgd_rectangle_demo(sgl_obj_t *parent)
{
    /*
     * 本 demo 里所有主要尺寸都按当前屏幕分辨率换算，
     * 这样在 320x480 之外的分辨率下仍能保持接近的视觉比例。
     */
    const int16_t page_top = SGD_MG;
    const int16_t block_gap = SGD_GAP * 3;
    const int16_t rect_h = (int16_t)(SGL_SCREEN_HEIGHT * 7 / 48);      /* 480 高屏时约等于 70 */
    const int16_t panel_h = (int16_t)(SGL_SCREEN_HEIGHT * 5 / 24);     /* 480 高屏时约等于 100 */
    const int16_t vbox_h = (int16_t)(SGL_SCREEN_HEIGHT * 3 / 8);       /* 480 高屏时约等于 180 */
    const int16_t panel_btn_h = (int16_t)(panel_h * 3 / 10);           /* 100 高面板时约等于 30 */
    const int16_t panel_btn_gap = SGD_MG;
    const int16_t panel_btn_x = panel_btn_gap;
    const int16_t panel_btn_y = panel_btn_gap;
    const int16_t panel_btn_w = (int16_t)(SGD_W * 7 / 31);             /* 320 宽屏时约等于 70 */
    const int16_t panel_btn_wide_w = (int16_t)(SGD_W * 15 / 31);       /* 320 宽屏时约等于 150 */

    int16_t y = page_top;
    sgl_layout_desc_t layout;

    /* ================================================================
     * 1) 基础矩形 — 完整功能，演示所有 sgl_rect_xxx 接口
     * ================================================================ */
    sgl_obj_t *juxing1 = sgl_rect_create(parent);
    sgl_obj_set_pos(juxing1, SGD_MG, y);
    sgl_obj_set_size(juxing1, SGD_W, rect_h);

    /* 设置矩形填充颜色（青色）*/
    sgl_rect_set_color(juxing1, SGL_COLOR_CYAN);

    /* 设置矩形整体透明度 */
    sgl_rect_set_alpha(juxing1, 200);

    /* 设置矩形主体透明度（覆盖整体透明度）*/
    sgl_rect_set_main_alpha(juxing1, 180);

    /* 设置圆角半径 */
    sgl_rect_set_radius(juxing1, 8);

    /* 设置边框宽度 */
    sgl_rect_set_border_width(juxing1, 3);

    /* 设置边框颜色 */
    sgl_rect_set_border_color(juxing1, SGL_COLOR_NAVY);

    /* 设置边框透明度 */
    sgl_rect_set_border_alpha(juxing1, 200);

    /* 设置矩形背景图片 */
    sgl_rect_set_pixmap(juxing1, &pic1_pixmap);
    y += rect_h + block_gap;

    /* ================================================================
     * 2) 基础矩形 — 不同颜色，无图片
     * ================================================================ */
    sgl_obj_t *juxing2 = sgl_rect_create(parent);
    sgl_obj_set_pos(juxing2, SGD_MG, y);
    sgl_obj_set_size(juxing2, SGD_W, rect_h);
    sgl_rect_set_color(juxing2, SGL_COLOR_GOLD);
    sgl_rect_set_alpha(juxing2, 220);
    sgl_rect_set_main_alpha(juxing2, 200);
    sgl_rect_set_radius(juxing2, 12);
    sgl_rect_set_border_width(juxing2, 2);
    sgl_rect_set_border_color(juxing2, SGL_COLOR_BROWN);
    sgl_rect_set_border_alpha(juxing2, 180);
    y += rect_h + block_gap;

    /* ================================================================
     * 3) 矩形作为容器 — 面板内嵌套子控件
     *    所有子控件坐标相对于面板左上角
     * ================================================================ */
    sgl_obj_t *panel = sgl_rect_create(parent);
    sgl_obj_set_pos(panel, SGD_MG, y);
    sgl_obj_set_size(panel, SGD_W, panel_h);
    sgl_rect_set_color(panel, SGL_COLOR_DARK_GRAY);
    sgl_rect_set_radius(panel, 6);
    sgl_rect_set_border_width(panel, 2);
    sgl_rect_set_border_color(panel, SGL_COLOR_CYAN);

    /* 面板内的按钮（坐标相对于 panel）*/
    {
        sgl_obj_t *btn1 = sgl_button_create(panel);
        sgl_obj_set_pos(btn1, panel_btn_x, panel_btn_y);
        sgl_obj_set_size(btn1, panel_btn_w, panel_btn_h);
        sgl_button_set_text(btn1, "Btn A");
        sgl_button_set_font(btn1, &consolas14);
        sgl_button_set_color(btn1, SGL_COLOR_DODGER_BLUE);
        sgl_button_set_radius(btn1, 4);

        sgl_obj_t *btn2 = sgl_button_create(panel);
        sgl_obj_set_pos(btn2, panel_btn_x + panel_btn_w + panel_btn_gap, panel_btn_y);
        sgl_obj_set_size(btn2, panel_btn_w, panel_btn_h);
        sgl_button_set_text(btn2, "Btn B");
        sgl_button_set_font(btn2, &consolas14);
        sgl_button_set_color(btn2, SGL_COLOR_TOMATO);
        sgl_button_set_radius(btn2, 4);

        sgl_obj_t *btn3 = sgl_button_create(panel);
        sgl_obj_set_pos(btn3, panel_btn_x, panel_btn_y + panel_btn_h + panel_btn_gap);
        sgl_obj_set_size(btn3, panel_btn_wide_w, panel_btn_h);
        sgl_button_set_text(btn3, "Btn C (Wide)");
        sgl_button_set_font(btn3, &consolas14);
        sgl_button_set_color(btn3, SGL_COLOR_DARK_GREEN);
        sgl_button_set_radius(btn3, 4);
    }
    y += panel_h + block_gap;



    /* ================================================================
     * 4) 自动布局 — 垂直排列（不手动设置子控件 pos/size）
     * ================================================================ */
    {
        sgl_obj_t *vbox = sgl_rect_create(parent);
        sgl_obj_set_pos(vbox, SGD_MG, y);
        sgl_obj_set_size(vbox, SGD_W, vbox_h);
        sgl_rect_set_color(vbox, SGL_COLOR_DARK_GRAY);
        sgl_rect_set_radius(vbox, 4);

        /*
         * 自动布局目前只有 sgl_obj_set_layout() 这一个总接口，
         * 没有单独的 set_row_space / set_padding 之类接口，
         * 所以这里直接填写 sgl_layout_desc_t 结构体。
         */

        /* 垂直布局：子控件沿 Y 方向从上到下排列 */
        layout.type = SGL_LAYOUT_VERTICAL;

        /* 垂直布局不需要列数，填 0 表示不使用该字段 */
        layout.col_num = 0;

        /* 垂直布局也不需要固定行数，按当前 child 数量自动分配 */
        layout.row_num = 0;

        /* 垂直布局不使用列间距，所以这里设为 0 */
        layout.col_space = 0;

        /* 每个按钮之间保留 4 像素纵向间距，避免控件贴在一起 */
        layout.row_space = 4;

        /* 左侧留 6 像素，让按钮不要紧贴容器边框 */
        layout.left_space = 6;

        /* 右侧留 6 像素，与左侧形成对称内边距 */
        layout.right_space = 6;

        /* 顶部留 6 像素，给第一项留出呼吸空间 */
        layout.top_space = 6;

        /* 底部留 6 像素，给最后一项留出收边空间 */
        layout.bottom_space = 6;
				/*
				sgl_obj_set_layout(container, SGL_LAYOUT_HORIZONTAL); // 水平排列
				sgl_obj_set_layout(container, SGL_LAYOUT_VERTICAL);   // 垂直排列
				sgl_obj_set_layout(container, SGL_LAYOUT_GRID);       // 网格布局（需额外配置） 
				共有上面三种布局，就是上面这些结构体，并不一定要全部写出来，
				可以把想要微调的写出来就行了。				
				*/
				
        /* 垂直排列的子按钮（不设 pos，宽度填满容器）*/
        sgl_obj_t *item1 = sgl_button_create(vbox);
        sgl_button_set_text(item1, "Item 1");
        sgl_button_set_font(item1, &consolas14);
        sgl_button_set_color(item1, SGL_COLOR_DODGER_BLUE);
        sgl_button_set_radius(item1, 4);

        sgl_obj_t *item2 = sgl_button_create(vbox);
        sgl_button_set_text(item2, "Item 2");
        sgl_button_set_font(item2, &consolas14);
        sgl_button_set_color(item2, SGL_COLOR_TOMATO);
        sgl_button_set_radius(item2, 4);

        sgl_obj_t *item3 = sgl_button_create(vbox);
        sgl_button_set_text(item3, "Item 3");
        sgl_button_set_font(item3, &consolas14);
        sgl_button_set_color(item3, SGL_COLOR_DARK_GREEN);
        sgl_button_set_radius(item3, 4);

        /* 子控件创建完成后再应用布局 */
        sgl_obj_set_layout(vbox, &layout);
    }
}
#endif
