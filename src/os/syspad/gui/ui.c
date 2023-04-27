// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.0
// LVGL VERSION: 8.2.0
// PROJECT: CrazyCube_Syspad_Mini

#include "ui.h"
#include "lv/ui_helpers.h"

///////////////////// VARIABLES ////////////////////
void syspad_lock_shake_Animation( lv_obj_t *TargetObject, int delay);
lv_obj_t *ui_SyspadMiniScreen;
lv_obj_t *ui_SyspadMiniPanel;
lv_obj_t *ui_SyspadMiniAssistantImage;
lv_obj_t *ui_SyspadMiniWifiImage;
lv_obj_t *ui_SyspadMiniLockImage;
lv_obj_t *ui_SyspadMiniMicImage;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////
void syspad_lock_shake_Animation( lv_obj_t *TargetObject, int delay)
{
lv_anim_t PropertyAnimation_0;
lv_anim_init(&PropertyAnimation_0);
lv_anim_set_time(&PropertyAnimation_0, 50);
lv_anim_set_user_data(&PropertyAnimation_0,TargetObject);
lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_x );
lv_anim_set_values(&PropertyAnimation_0, 0, 5 );
lv_anim_set_path_cb( &PropertyAnimation_0, lv_anim_path_ease_out);
lv_anim_set_delay( &PropertyAnimation_0, delay + 0 );
lv_anim_set_playback_time(&PropertyAnimation_0, 0);
lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
lv_anim_set_early_apply( &PropertyAnimation_0, false );
lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_x );
lv_anim_start(&PropertyAnimation_0);
lv_anim_t PropertyAnimation_1;
lv_anim_init(&PropertyAnimation_1);
lv_anim_set_time(&PropertyAnimation_1, 100);
lv_anim_set_user_data(&PropertyAnimation_1,TargetObject);
lv_anim_set_custom_exec_cb(&PropertyAnimation_1, _ui_anim_callback_set_x );
lv_anim_set_values(&PropertyAnimation_1, 5, -5 );
lv_anim_set_path_cb( &PropertyAnimation_1, lv_anim_path_ease_out);
lv_anim_set_delay( &PropertyAnimation_1, delay + 50 );
lv_anim_set_playback_time(&PropertyAnimation_1, 0);
lv_anim_set_playback_delay(&PropertyAnimation_1, 0);
lv_anim_set_repeat_count(&PropertyAnimation_1, 0);
lv_anim_set_repeat_delay(&PropertyAnimation_1, 0);
lv_anim_set_early_apply( &PropertyAnimation_1, false );
lv_anim_set_get_value_cb(&PropertyAnimation_1, &_ui_anim_callback_get_x );
lv_anim_start(&PropertyAnimation_1);
lv_anim_t PropertyAnimation_2;
lv_anim_init(&PropertyAnimation_2);
lv_anim_set_time(&PropertyAnimation_2, 50);
lv_anim_set_user_data(&PropertyAnimation_2,TargetObject);
lv_anim_set_custom_exec_cb(&PropertyAnimation_2, _ui_anim_callback_set_x );
lv_anim_set_values(&PropertyAnimation_2, -5, 0 );
lv_anim_set_path_cb( &PropertyAnimation_2, lv_anim_path_ease_out);
lv_anim_set_delay( &PropertyAnimation_2, delay + 150 );
lv_anim_set_playback_time(&PropertyAnimation_2, 0);
lv_anim_set_playback_delay(&PropertyAnimation_2, 0);
lv_anim_set_repeat_count(&PropertyAnimation_2, 0);
lv_anim_set_repeat_delay(&PropertyAnimation_2, 0);
lv_anim_set_early_apply( &PropertyAnimation_2, false );
lv_anim_set_get_value_cb(&PropertyAnimation_2, &_ui_anim_callback_get_x );
lv_anim_start(&PropertyAnimation_2);

}

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////
void ui_SyspadMiniScreen_screen_init(void)
{
ui_SyspadMiniScreen = lv_obj_create(lv_layer_sys());
lv_obj_clear_flag( ui_SyspadMiniScreen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_SyspadMiniScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_SyspadMiniScreen, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_SyspadMiniScreen, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadMiniPanel = lv_obj_create(ui_SyspadMiniScreen);
lv_obj_set_height( ui_SyspadMiniPanel, 30);
lv_obj_set_width( ui_SyspadMiniPanel, lv_pct(100));
lv_obj_set_align( ui_SyspadMiniPanel, LV_ALIGN_TOP_MID );
lv_obj_clear_flag( ui_SyspadMiniPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_SyspadMiniPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_SyspadMiniPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_SyspadMiniPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_SyspadMiniPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_SyspadMiniPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_SyspadMiniPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_SyspadMiniPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadMiniAssistantImage = lv_img_create(ui_SyspadMiniPanel);
lv_img_set_src(ui_SyspadMiniAssistantImage, &ui_img_assistant_on_png);
lv_obj_set_width( ui_SyspadMiniAssistantImage, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadMiniAssistantImage, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadMiniAssistantImage, -44 );
lv_obj_set_y( ui_SyspadMiniAssistantImage, 0 );
lv_obj_set_align( ui_SyspadMiniAssistantImage, LV_ALIGN_TOP_RIGHT );
lv_obj_add_flag( ui_SyspadMiniAssistantImage, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_SyspadMiniAssistantImage, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_SyspadMiniWifiImage = lv_img_create(ui_SyspadMiniPanel);
lv_img_set_src(ui_SyspadMiniWifiImage, &ui_img_wifi_on_png);
lv_obj_set_width( ui_SyspadMiniWifiImage, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadMiniWifiImage, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadMiniWifiImage, -10 );
lv_obj_set_y( ui_SyspadMiniWifiImage, 0 );
lv_obj_set_align( ui_SyspadMiniWifiImage, LV_ALIGN_TOP_RIGHT );
lv_obj_add_flag( ui_SyspadMiniWifiImage, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_SyspadMiniWifiImage, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_SyspadMiniLockImage = lv_img_create(ui_SyspadMiniPanel);
lv_img_set_src(ui_SyspadMiniLockImage, &ui_img_lock_png);
lv_obj_set_width( ui_SyspadMiniLockImage, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadMiniLockImage, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadMiniLockImage, 20 );
lv_obj_set_y( ui_SyspadMiniLockImage, 0 );
lv_obj_add_flag( ui_SyspadMiniLockImage, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_SyspadMiniLockImage, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_SyspadMiniMicImage = lv_img_create(ui_SyspadMiniPanel);
lv_img_set_src(ui_SyspadMiniMicImage, &ui_img_mic_on_png);
lv_obj_set_width( ui_SyspadMiniMicImage, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadMiniMicImage, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadMiniMicImage, 30 );
lv_obj_set_y( ui_SyspadMiniMicImage, 0 );
lv_obj_set_align( ui_SyspadMiniMicImage, LV_ALIGN_TOP_MID );
lv_obj_add_flag( ui_SyspadMiniMicImage, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_SyspadMiniMicImage, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

}

// void ui_init( void )
// {
// lv_disp_t *dispp = lv_disp_get_default();
// lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
// lv_disp_set_theme(dispp, theme);
// ui_SyspadMiniScreen_screen_init();
// lv_disp_load_scr( ui_SyspadMiniScreen);
// }
