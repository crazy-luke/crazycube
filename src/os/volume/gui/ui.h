// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.0
// LVGL VERSION: 8.2.0
// PROJECT: CrazyCube_Volume

#ifndef _CRAZYCUBE_VOLUME_UI_H
#define _CRAZYCUBE_VOLUME_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

void volume_hide_Animation( lv_obj_t *TargetObject, int delay, lv_anim_ready_cb_t ready_cb);
void volume_show_Animation( lv_obj_t *TargetObject, int delay);
// extern lv_obj_t *ui_VolumeScreen;
extern lv_obj_t *ui_VolumePanel;
extern lv_obj_t *ui_VolumeLabel;
extern lv_obj_t *ui_VolumeBar;




// LV_FONT_DECLARE( ui_font_SourceHanCrazyCube22);


void ui_VolumeScreen_screen_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
