/**
 * @file    sgl_sprite_demo.c
 * @brief   SGL Sprite 精灵控件 Demo — 覆盖所有 sgl_sprite_xxx 接口
 * 看这名字是不是有点懵？确实，我也有点懵
这个控件是专门用于游戏的速度特别快，
但是只支持 ARGB 4444格式的图片也就是说，
如果你想要点具有透明度的图片推荐使用这个
 */
#include "sgl_demo.h"
#if SGD_ENABLE_SPRITE
extern const sgl_pixmap_t pic1_pixmap;

void sgd_sprite_demo(sgl_obj_t *parent)
{
    sgl_obj_t *jingling1 = sgl_sprite_create(parent);
    sgl_obj_set_pos(jingling1, 60, 60);
    sgl_obj_set_size(jingling1, 64, 64);

    /* 设置精灵图片 */
    sgl_sprite_set_pixmap(jingling1, &pic1_pixmap);

    /* 设置透明度 */
    sgl_sprite_set_alpha(jingling1, 220);

    /* 第二个精灵（不同位置）*/
    sgl_obj_t *jingling2 = sgl_sprite_create(parent);
    sgl_obj_set_pos(jingling2, 180, 60);
    sgl_obj_set_size(jingling2, 64, 64);
    sgl_sprite_set_pixmap(jingling2, &pic1_pixmap);
    sgl_sprite_set_alpha(jingling2, 180);
}
#endif
