// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.0
// LVGL VERSION: 8.2.0
// PROJECT: CrazyCube_Assistant

#include "ui.h"
#include "lv/ui_helpers.h"

///////////////////// VARIABLES ////////////////////
void assistant_wave_Animation( lv_obj_t *TargetObject, int delay);
lv_obj_t *ui_AssistantScreen;
lv_obj_t *ui_AssistantPanel;
lv_obj_t *ui_AssistantAudioPanel;
lv_obj_t *ui_AssistantAudioBgPanel;
lv_obj_t *ui_AssistantWavePanel;
lv_obj_t *ui_AssistantWaveImage;
lv_obj_t *ui_AssistantMicSpinner;
lv_obj_t *ui_AssistantMicImage;
lv_obj_t *ui_AssistantMicLabel;
lv_obj_t *ui_AssistantHitLabel;
lv_obj_t *ui_AssistantMicTimePanel;
lv_obj_t *ui_AssistantMicTimeBar;
lv_obj_t *ui_AssistantMicTimeImage;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////
void assistant_wave_Animation( lv_obj_t *TargetObject, int delay)
{
lv_anim_t PropertyAnimation_0;
lv_anim_init(&PropertyAnimation_0);
lv_anim_set_time(&PropertyAnimation_0, 2000);
lv_anim_set_user_data(&PropertyAnimation_0,TargetObject);
lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_x );
lv_anim_set_values(&PropertyAnimation_0, -64, 64 );
lv_anim_set_path_cb( &PropertyAnimation_0, lv_anim_path_linear);
lv_anim_set_delay( &PropertyAnimation_0, delay + 0 );
lv_anim_set_playback_time(&PropertyAnimation_0, 0);
lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE );
lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
lv_anim_set_early_apply( &PropertyAnimation_0, false );
lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_x );
lv_anim_start(&PropertyAnimation_0);

}

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////
void ui_AssistantScreen_screen_init(void)
{
ui_AssistantScreen = lv_obj_create(lv_layer_sys());
lv_obj_clear_flag( ui_AssistantScreen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_AssistantScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_AssistantScreen, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_AssistantPanel = lv_obj_create(ui_AssistantScreen);
lv_obj_set_width( ui_AssistantPanel, lv_pct(100));
lv_obj_set_height( ui_AssistantPanel, lv_pct(66));
lv_obj_set_align( ui_AssistantPanel, LV_ALIGN_BOTTOM_MID );
lv_obj_clear_flag( ui_AssistantPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_AssistantPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_AssistantPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_AssistantPanel, 125, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_grad_color(ui_AssistantPanel, lv_color_hex(0x767676), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_grad_dir(ui_AssistantPanel, LV_GRAD_DIR_VER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_AssistantPanel, 1, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_side(ui_AssistantPanel, LV_BORDER_SIDE_TOP, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_AssistantPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_AssistantPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_AssistantPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_AssistantPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_AssistantAudioPanel = lv_obj_create(ui_AssistantPanel);
lv_obj_set_width( ui_AssistantAudioPanel, 92);
lv_obj_set_height( ui_AssistantAudioPanel, 92);
lv_obj_set_x( ui_AssistantAudioPanel, 0 );
lv_obj_set_y( ui_AssistantAudioPanel, -18 );
lv_obj_set_align( ui_AssistantAudioPanel, LV_ALIGN_BOTTOM_MID );
lv_obj_add_flag( ui_AssistantAudioPanel, LV_OBJ_FLAG_HIDDEN );   /// Flags
lv_obj_clear_flag( ui_AssistantAudioPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_AssistantAudioPanel, 92, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_AssistantAudioPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_AssistantAudioPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_AssistantAudioPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_AssistantAudioPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_AssistantAudioPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_AssistantAudioPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_AssistantAudioPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_AssistantAudioBgPanel = lv_obj_create(ui_AssistantAudioPanel);
lv_obj_set_width( ui_AssistantAudioBgPanel, 90);
lv_obj_set_height( ui_AssistantAudioBgPanel, 90);
lv_obj_set_align( ui_AssistantAudioBgPanel, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_AssistantAudioBgPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_AssistantAudioBgPanel, 90, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_AssistantAudioBgPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_AssistantAudioBgPanel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_AssistantAudioBgPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_AssistantAudioBgPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_AssistantAudioBgPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_AssistantAudioBgPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_AssistantAudioBgPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_AssistantWavePanel = lv_obj_create(ui_AssistantAudioPanel);
lv_obj_set_width( ui_AssistantWavePanel, 90);
lv_obj_set_height( ui_AssistantWavePanel, 90);
lv_obj_set_align( ui_AssistantWavePanel, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_AssistantWavePanel, LV_OBJ_FLAG_HIDDEN );   /// Flags
lv_obj_clear_flag( ui_AssistantWavePanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_AssistantWavePanel, 90, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_AssistantWavePanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_AssistantWavePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_clip_corner(ui_AssistantWavePanel, true, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_AssistantWavePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_side(ui_AssistantWavePanel, LV_BORDER_SIDE_NONE, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_AssistantWavePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_AssistantWavePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_AssistantWavePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_AssistantWavePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_AssistantWaveImage = lv_img_create(ui_AssistantWavePanel);
lv_img_set_src(ui_AssistantWaveImage, &ui_img_assistant_soundwaves_png);
lv_obj_set_width( ui_AssistantWaveImage, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_AssistantWaveImage, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_AssistantWaveImage, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_AssistantWaveImage, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_AssistantWaveImage, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_AssistantMicSpinner = lv_spinner_create(ui_AssistantAudioPanel,1000,90);
lv_obj_set_width( ui_AssistantMicSpinner, 92);
lv_obj_set_height( ui_AssistantMicSpinner, 92);
lv_obj_set_align( ui_AssistantMicSpinner, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_AssistantMicSpinner, LV_OBJ_FLAG_CLICKABLE );    /// Flags

ui_AssistantMicImage = lv_img_create(ui_AssistantMicSpinner);
lv_img_set_src(ui_AssistantMicImage, &ui_img_assistant_mic_png);
lv_obj_set_width( ui_AssistantMicImage, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_AssistantMicImage, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_AssistantMicImage, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_AssistantMicImage, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_AssistantMicImage, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_AssistantMicLabel = lv_label_create(ui_AssistantMicSpinner);
lv_obj_set_width( ui_AssistantMicLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_AssistantMicLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_AssistantMicLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_AssistantMicLabel,"连接中");
lv_obj_add_flag( ui_AssistantMicLabel, LV_OBJ_FLAG_HIDDEN );   /// Flags
lv_obj_set_style_text_color(ui_AssistantMicLabel, lv_color_hex(0x00499E), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_AssistantMicLabel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_AssistantMicLabel, &ui_font_SourceHanCrazyCube22, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_AssistantHitLabel = lv_label_create(ui_AssistantPanel);
lv_obj_set_width( ui_AssistantHitLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_AssistantHitLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_AssistantHitLabel, 0 );
lv_obj_set_y( ui_AssistantHitLabel, 10 );
lv_obj_set_align( ui_AssistantHitLabel, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_AssistantHitLabel,"语音助手");
lv_obj_set_style_text_font(ui_AssistantHitLabel, &ui_font_SourceHanCrazyCube26, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_AssistantMicTimePanel = lv_obj_create(ui_AssistantPanel);
lv_obj_set_width( ui_AssistantMicTimePanel, 240);
lv_obj_set_height( ui_AssistantMicTimePanel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_AssistantMicTimePanel, LV_ALIGN_BOTTOM_MID );
lv_obj_clear_flag( ui_AssistantMicTimePanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_AssistantMicTimePanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_AssistantMicTimePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_AssistantMicTimePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_AssistantMicTimePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_AssistantMicTimePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_AssistantMicTimePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_AssistantMicTimePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_AssistantMicTimeBar = lv_bar_create(ui_AssistantMicTimePanel);
lv_bar_set_value(ui_AssistantMicTimeBar,50,LV_ANIM_OFF);
lv_obj_set_width( ui_AssistantMicTimeBar, 240);
lv_obj_set_height( ui_AssistantMicTimeBar, 10);
lv_obj_set_align( ui_AssistantMicTimeBar, LV_ALIGN_BOTTOM_RIGHT );
lv_obj_set_style_radius(ui_AssistantMicTimeBar, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_AssistantMicTimeBar, lv_color_hex(0x545454), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_AssistantMicTimeBar, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_set_style_radius(ui_AssistantMicTimeBar, 0, LV_PART_INDICATOR| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_AssistantMicTimeBar, lv_color_hex(0x4694EF), LV_PART_INDICATOR | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_AssistantMicTimeBar, 200, LV_PART_INDICATOR| LV_STATE_DEFAULT);


ui_AssistantMicTimeImage = lv_img_create(ui_AssistantMicTimePanel);
lv_img_set_src(ui_AssistantMicTimeImage, &ui_img_clockwise_png);
lv_obj_set_width( ui_AssistantMicTimeImage, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_AssistantMicTimeImage, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_AssistantMicTimeImage, 2 );
lv_obj_set_y( ui_AssistantMicTimeImage, 0 );
lv_obj_set_align( ui_AssistantMicTimeImage, LV_ALIGN_BOTTOM_LEFT );
lv_obj_add_flag( ui_AssistantMicTimeImage, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_AssistantMicTimeImage, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

}

// void ui_init( void )
// {
// lv_disp_t *dispp = lv_disp_get_default();
// lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
// lv_disp_set_theme(dispp, theme);
// ui_AssistantScreen_screen_init();
// lv_disp_load_scr( ui_AssistantScreen);
// }
