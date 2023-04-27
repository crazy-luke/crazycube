// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.0
// LVGL VERSION: 8.2.0
// PROJECT: CrazyCube_Volume

#include "ui.h"
#include "lv/ui_helpers.h"

///////////////////// VARIABLES ////////////////////
void volume_hide_Animation( lv_obj_t *TargetObject, int delay, lv_anim_ready_cb_t ready_cb);
void volume_show_Animation( lv_obj_t *TargetObject, int delay);
lv_obj_t *ui_VolumeScreen;
lv_obj_t *ui_VolumePanel;
lv_obj_t *ui_VolumeLabel;
lv_obj_t *ui_VolumeBar;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////
void volume_hide_Animation( lv_obj_t *TargetObject, int delay, lv_anim_ready_cb_t ready_cb)
{
lv_anim_t PropertyAnimation_0;
lv_anim_init(&PropertyAnimation_0);
lv_anim_set_time(&PropertyAnimation_0, 50);
lv_anim_set_user_data(&PropertyAnimation_0,TargetObject);
lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_opacity );
lv_anim_set_values(&PropertyAnimation_0, 255, 0 );
lv_anim_set_path_cb( &PropertyAnimation_0, lv_anim_path_ease_in);
lv_anim_set_delay( &PropertyAnimation_0, delay + 0 );
lv_anim_set_playback_time(&PropertyAnimation_0, 0);
lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
lv_anim_set_early_apply( &PropertyAnimation_0, false );
lv_anim_set_ready_cb(&PropertyAnimation_0, ready_cb);
lv_anim_start(&PropertyAnimation_0);

}
void volume_show_Animation( lv_obj_t *TargetObject, int delay)
{
lv_anim_t PropertyAnimation_0;
lv_anim_init(&PropertyAnimation_0);
lv_anim_set_time(&PropertyAnimation_0, 500);
lv_anim_set_user_data(&PropertyAnimation_0,TargetObject);
lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_opacity );
lv_anim_set_values(&PropertyAnimation_0, 0, 255 );
lv_anim_set_path_cb( &PropertyAnimation_0, lv_anim_path_linear);
lv_anim_set_delay( &PropertyAnimation_0, delay + 0 );
lv_anim_set_playback_time(&PropertyAnimation_0, 0);
lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
lv_anim_set_early_apply( &PropertyAnimation_0, false );
lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_opacity );
lv_anim_start(&PropertyAnimation_0);

}

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////
void ui_VolumeScreen_screen_init(void)
{
// ui_VolumeScreen = lv_obj_create(NULL);
// lv_obj_clear_flag( ui_VolumeScreen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
// lv_obj_set_style_bg_color(ui_VolumeScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
// lv_obj_set_style_bg_opa(ui_VolumeScreen, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_VolumePanel = lv_obj_create(lv_layer_sys());
lv_obj_set_width( ui_VolumePanel, 36);
lv_obj_set_height( ui_VolumePanel, 180);
lv_obj_set_align( ui_VolumePanel, LV_ALIGN_BOTTOM_RIGHT );
lv_obj_clear_flag( ui_VolumePanel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN );    /// Flags
lv_obj_set_style_bg_color(ui_VolumePanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_VolumePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_VolumePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_VolumePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_VolumePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_VolumePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_VolumePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_VolumeLabel = lv_label_create(ui_VolumePanel);
lv_obj_set_width( ui_VolumeLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_VolumeLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_VolumeLabel, LV_ALIGN_BOTTOM_MID );
lv_label_set_text(ui_VolumeLabel,"50");
lv_obj_set_style_text_font(ui_VolumeLabel, &ui_font_SourceHanCrazyCube22, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_VolumeBar = lv_bar_create(ui_VolumePanel);
lv_bar_set_value(ui_VolumeBar,25,LV_ANIM_OFF);
lv_obj_set_width( ui_VolumeBar, 10);
lv_obj_set_height( ui_VolumeBar, 150);
lv_obj_set_align( ui_VolumeBar, LV_ALIGN_TOP_MID );
lv_obj_set_style_radius(ui_VolumeBar, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_set_style_radius(ui_VolumeBar, 0, LV_PART_INDICATOR| LV_STATE_DEFAULT);

}

// void ui_init( void )
// {
// lv_disp_t *dispp = lv_disp_get_default();
// lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
// lv_disp_set_theme(dispp, theme);
// ui_VolumeScreen_screen_init();
// lv_disp_load_scr( ui_VolumeScreen);
// }
