// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.0
// LVGL VERSION: 8.2.0
// PROJECT: CrazyCube_Assistant

#ifndef _CRAZYCUBE_ASSISTANT_UI_H
#define _CRAZYCUBE_ASSISTANT_UI_H

#ifdef __cplusplus
extern "C" {
#endif

    #include "lvgl.h"

void assistant_wave_Animation( lv_obj_t *TargetObject, int delay);
extern lv_obj_t *ui_AssistantScreen;
extern lv_obj_t *ui_AssistantPanel;
extern lv_obj_t *ui_AssistantAudioPanel;
extern lv_obj_t *ui_AssistantAudioBgPanel;
extern lv_obj_t *ui_AssistantWavePanel;
extern lv_obj_t *ui_AssistantWaveImage;
extern lv_obj_t *ui_AssistantMicSpinner;
extern lv_obj_t *ui_AssistantMicImage;
extern lv_obj_t *ui_AssistantMicLabel;
extern lv_obj_t *ui_AssistantHitLabel;
extern lv_obj_t *ui_AssistantMicTimePanel;
extern lv_obj_t *ui_AssistantMicTimeBar;
extern lv_obj_t *ui_AssistantMicTimeImage;


LV_IMG_DECLARE( ui_img_assistant_soundwaves_png);   // assets/assistant_soundwaves.png
LV_IMG_DECLARE( ui_img_assistant_mic_png);   // assets/assistant_mic.png
LV_IMG_DECLARE( ui_img_clockwise_png);   // assets/clockwise.png


// LV_FONT_DECLARE( ui_font_SourceHanCrazyCube22);
// LV_FONT_DECLARE( ui_font_SourceHanCrazyCube26);


void ui_AssistantScreen_screen_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
