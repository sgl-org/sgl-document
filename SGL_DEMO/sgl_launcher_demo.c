/**
 * @file    sgl_launcher_demo.c
 * @brief   SGL Launcher 启动器控件 Demo — 覆盖所有 sgl_launcher_xxx 接口
 *          展示桌面启动器效果：图标网格 + 滑动翻页 + 底部指示点
 *          点击应用图标进入应用，长按应用页面弹窗确认后返回启动器桌面
 */
#include "sgl_demo.h"
#if SGD_ENABLE_LAUNCHER

/* 图片资源 */
extern const sgl_pixmap_t pic1_pixmap;

/* 应用启动回调：点击应用图标后执行，创建应用页面 */
static void app_start(void *private_data)
{
    const char *name = (const char *)private_data;
    sgl_obj_t *scr = sgl_screen_act();

    /* 创建一个整屏的应用页面 */
    sgl_obj_t *lbl = sgl_label_create(scr);
    sgl_obj_set_pos(lbl, 0, 0);
    sgl_obj_set_size(lbl, SGL_SCREEN_WIDTH, SGL_SCREEN_HEIGHT);
    sgl_label_set_font(lbl, &consolas14);
    sgl_label_set_text(lbl, name);
    sgl_label_set_text_align(lbl, SGL_ALIGN_CENTER);
    sgl_label_set_text_color(lbl, SGL_COLOR_WHITE);
    sgl_label_set_bg_color(lbl, SGL_COLOR_DARK_GRAY);
    sgl_obj_set_clickable(lbl);

    /* 注册退出确认回调：长按应用页面弹窗，确认后重新创建启动器返回桌面 */
    sgl_obj_set_event_cb(lbl, sgl_launcher_exit_msgbox_cb, NULL);
}

/* 应用退出回调：从应用返回启动器时执行 */
static void app_exit(void)
{
    sgl_log("Launcher", "app exit");
}

/* 应用列表：每个应用包含启动/退出回调、图标、名称、图标圆角 */
static const sgl_launcher_app_t apps[] = {
    { .start = app_start, .exit = app_exit, .private_data = "Gallery",    .icon = &pic1_pixmap, .name = "Gallery",    .radius = 8 },
    { .start = app_start, .exit = app_exit, .private_data = "Camera",     .icon = &pic1_pixmap, .name = "Camera",     .radius = 8 },
    { .start = app_start, .exit = app_exit, .private_data = "Music",      .icon = &pic1_pixmap, .name = "Music",      .radius = 8 },
    { .start = app_start, .exit = app_exit, .private_data = "Settings",   .icon = &pic1_pixmap, .name = "Settings",   .radius = 8 },
    { .start = app_start, .exit = app_exit, .private_data = "Browser",    .icon = &pic1_pixmap, .name = "Browser",    .radius = 8 },
    { .start = app_start, .exit = app_exit, .private_data = "Clock",      .icon = &pic1_pixmap, .name = "Clock",      .radius = 8 },
    { .start = app_start, .exit = app_exit, .private_data = "Maps",       .icon = &pic1_pixmap, .name = "Maps",       .radius = 8 },
    { .start = app_start, .exit = app_exit, .private_data = "Notes",      .icon = &pic1_pixmap, .name = "Notes",      .radius = 8 },
    { .start = app_start, .exit = app_exit, .private_data = "Files",      .icon = &pic1_pixmap, .name = "Files",      .radius = 8 },
    { .start = app_start, .exit = app_exit, .private_data = "Calculator", .icon = &pic1_pixmap, .name = "Calculator", .radius = 8 },
    { .start = app_start, .exit = app_exit, .private_data = "Weather",    .icon = &pic1_pixmap, .name = "Weather",    .radius = 8 },
    { .start = app_start, .exit = app_exit, .private_data = "Calendar",   .icon = &pic1_pixmap, .name = "Calendar",   .radius = 8 },
};

/* 启动器属性：图标大小、页面边距、图标网格行列数 */
static const sgl_launcher_attr_t launcher_attr = {
    .icon_size     = 52,
    .margin_left   = 26,
    .margin_top    = 40,
    .margin_right  = 26,
    .margin_bottom = 40,
    .grid_row      = 3,
    .grid_col      = 3,
};

void sgd_launcher_demo(sgl_obj_t *parent)
{
    (void)parent;

    /* 创建启动器控件：传入属性、应用标签字体、应用列表及应用数量（应用通过控件自己的接口注册） */
    sgl_obj_t *qidong = sgl_launcher_create(&launcher_attr, &consolas14, apps, SGL_ARRAY_SIZE(apps), NULL);

    /* 设置应用名称标签颜色 */
    sgl_launcher_set_label_color(qidong, SGL_COLOR_WHITE);

    /* 设置底部翻页指示点颜色 */
    sgl_launcher_set_navigbar_color(qidong, SGL_COLOR_DARK_GRAY);

    /* 获取当前页码 */
    int16_t page = sgl_launcher_get_current_page(qidong);

    /* 设置当前页码 */
    sgl_launcher_set_current_page(qidong, page);
}
#endif
