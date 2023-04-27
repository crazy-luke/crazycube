// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.0
// LVGL VERSION: 8.2
// PROJECT: CrazyCube_Relax

#ifndef _CRAZYCUBE_RELAX_UI_H
#define _CRAZYCUBE_RELAX_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
#if __has_include("lvgl.h")
#include "lvgl.h"
#elif __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif

extern lv_obj_t * ui_RelaxScreen;
extern lv_obj_t * ui_GameTitleLabel;
extern lv_obj_t * ui_RelaxManualLabel;
extern lv_obj_t * ui_RelaxHintLabel;
extern lv_obj_t * ui_RelaxDirectionHintLabel;
extern lv_obj_t * ui_RelaxDirectionLabel;

void ui_RelaxScreen_screen_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
