// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.0
// LVGL VERSION: 8.2.0
// PROJECT: CrazyCube_Syspad_Mini

#ifndef _CRAZYCUBE_SYSPAD_MINI_UI_H
#define _CRAZYCUBE_SYSPAD_MINI_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <lvgl.h>

void syspad_lock_shake_Animation( lv_obj_t *TargetObject, int delay);
extern lv_obj_t *ui_SyspadMiniScreen;
extern lv_obj_t *ui_SyspadMiniPanel;
extern lv_obj_t *ui_SyspadMiniAssistantImage;
extern lv_obj_t *ui_SyspadMiniWifiImage;
extern lv_obj_t *ui_SyspadMiniLockImage;
extern lv_obj_t *ui_SyspadMiniMicImage;


LV_IMG_DECLARE( ui_img_assistant_on_png);   // assets/assistant_on.png
LV_IMG_DECLARE( ui_img_wifi_on_png);   // assets/wifi_on.png
LV_IMG_DECLARE( ui_img_lock_png);   // assets/lock.png
LV_IMG_DECLARE( ui_img_mic_on_png);   // assets/mic_on.png

void ui_SyspadMiniScreen_screen_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
