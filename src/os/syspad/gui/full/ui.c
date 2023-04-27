// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.1
// LVGL VERSION: 8.2.0
// PROJECT: CrazyCube_Syspad_Full

#include "ui.h"
#include "lv/ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t *ui_SyspadFullScreen;
lv_obj_t *ui_SyspadFullPanel;
lv_obj_t *ui_SyspadHintPanel;
lv_obj_t *ui_SyspadPanelHint2;
lv_obj_t *ui_SyspadHintLabel2;
lv_obj_t *ui_SyspadHintLabel1;
lv_obj_t *ui_SyspadHintRightImage;
lv_obj_t *ui_SyspadHintLeftImage;
lv_obj_t *ui_SyspadVolumePanel;
lv_obj_t *ui_SyspadVolumeHitImage1;
lv_obj_t *ui_SyspadBrightnessLabel1;
lv_obj_t *ui_SyspadVolumeHitImage2;
lv_obj_t *ui_SyspadBrightnessLabe2;
lv_obj_t *ui_SyspadVolumeImage;
lv_obj_t *ui_SyspadVolumeHitLabel;
lv_obj_t *ui_SyspadVolumeBar;
lv_obj_t *ui_SyspadBrightnessPanel;
lv_obj_t *ui_SyspadBrightnessHitImage2;
lv_obj_t *ui_SyspadBrightnessLabel3;
lv_obj_t *ui_SyspadBrightnessHitImage1;
lv_obj_t *ui_SyspadBrightnessLabel4;
lv_obj_t *ui_SyspadBrightnessImage;
lv_obj_t *ui_SyspadBrightnessBar;
lv_obj_t *ui_SyspadBrightnessHitLabel;
lv_obj_t *ui_SyspadManualPanel;
lv_obj_t *ui_SyspadManualTitleLabel;
lv_obj_t *ui_SyspadManualContentLabel;
lv_obj_t *ui_SyspadLEDPanel;
lv_obj_t *ui_SyspadLEDHitImage;
lv_obj_t *ui_SyspadLEDLabel;
lv_obj_t *ui_SyspadLEDHitImage1;
lv_obj_t *ui_SyspadLEDLabel5;
lv_obj_t *ui_SyspadLEDImage1;
lv_obj_t *ui_SyspadLEDBar;
lv_obj_t *ui_SyspadLEDHitLabel;
lv_obj_t *ui_SyspadLEDHitLabel1;
lv_obj_t *ui_SyspadAboutPanel;
lv_obj_t *ui_SyspadAboutHitRebootLabel;
lv_obj_t *ui_SyspadAboutLabel;
lv_obj_t *ui_SyspadAboutHintRebootImage;
lv_obj_t *ui_SyspadAboutDebugLabel;
lv_obj_t *ui_SyspadKeyboardPanel;
lv_obj_t *ui_SyspadKeyboardHitTitleLabel;
lv_obj_t *ui_SyspadKeyboardHitTitleLabel1;
lv_obj_t *ui_SyspadKeyboardHintImage;
lv_obj_t *ui_SyspadKeyboardHintSwitchLabel;
lv_obj_t *ui_SyspadKeyboardSwitch;
lv_obj_t *ui_SyspadKeyboardHintActImage;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////
void ui_SyspadFullScreen_screen_init(void)
{
ui_SyspadFullScreen = lv_obj_create(lv_layer_sys());
lv_obj_clear_flag( ui_SyspadFullScreen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_SyspadFullScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_SyspadFullScreen, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadFullPanel = lv_obj_create(ui_SyspadFullScreen);
lv_obj_set_width( ui_SyspadFullPanel, lv_pct(100));
lv_obj_set_height( ui_SyspadFullPanel, lv_pct(84));
lv_obj_set_align( ui_SyspadFullPanel, LV_ALIGN_TOP_MID );
lv_obj_clear_flag( ui_SyspadFullPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_SyspadFullPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_SyspadFullPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_SyspadFullPanel, 125, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_grad_color(ui_SyspadFullPanel, lv_color_hex(0x767676), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_grad_dir(ui_SyspadFullPanel, LV_GRAD_DIR_VER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_SyspadFullPanel, 1, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_side(ui_SyspadFullPanel, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_SyspadFullPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_SyspadFullPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_SyspadFullPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_SyspadFullPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadHintPanel = lv_obj_create(ui_SyspadFullPanel);
lv_obj_set_height( ui_SyspadHintPanel, 40);
lv_obj_set_width( ui_SyspadHintPanel, lv_pct(100));
lv_obj_set_x( ui_SyspadHintPanel, 0 );
lv_obj_set_y( ui_SyspadHintPanel, -4 );
lv_obj_set_align( ui_SyspadHintPanel, LV_ALIGN_BOTTOM_MID );
lv_obj_add_flag( ui_SyspadHintPanel, LV_OBJ_FLAG_HIDDEN );   /// Flags
lv_obj_clear_flag( ui_SyspadHintPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_SyspadHintPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_SyspadHintPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_SyspadHintPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_SyspadHintPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_SyspadHintPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_SyspadHintPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_SyspadHintPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadPanelHint2 = lv_obj_create(ui_SyspadHintPanel);
lv_obj_set_height( ui_SyspadPanelHint2, 40);
lv_obj_set_width( ui_SyspadPanelHint2, lv_pct(100));
lv_obj_set_align( ui_SyspadPanelHint2, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_SyspadPanelHint2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_SyspadPanelHint2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_SyspadPanelHint2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_SyspadPanelHint2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_SyspadPanelHint2, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_SyspadPanelHint2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_SyspadPanelHint2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_SyspadPanelHint2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_SyspadPanelHint2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_SyspadPanelHint2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadHintLabel2 = lv_label_create(ui_SyspadPanelHint2);
lv_obj_set_width( ui_SyspadHintLabel2, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadHintLabel2, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadHintLabel2, -40 );
lv_obj_set_y( ui_SyspadHintLabel2, 0 );
lv_obj_set_align( ui_SyspadHintLabel2, LV_ALIGN_RIGHT_MID );
lv_label_set_text(ui_SyspadHintLabel2,"右");
lv_obj_set_style_text_font(ui_SyspadHintLabel2, &ui_font_SourceHanCrazyCube22, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadHintLabel1 = lv_label_create(ui_SyspadPanelHint2);
lv_obj_set_width( ui_SyspadHintLabel1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadHintLabel1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadHintLabel1, 40 );
lv_obj_set_y( ui_SyspadHintLabel1, 0 );
lv_obj_set_align( ui_SyspadHintLabel1, LV_ALIGN_LEFT_MID );
lv_label_set_text(ui_SyspadHintLabel1,"左");
lv_obj_set_style_text_font(ui_SyspadHintLabel1, &ui_font_SourceHanCrazyCube22, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadHintRightImage = lv_img_create(ui_SyspadHintPanel);
lv_img_set_src(ui_SyspadHintRightImage, &ui_img_right_png);
lv_obj_set_width( ui_SyspadHintRightImage, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadHintRightImage, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadHintRightImage, -10 );
lv_obj_set_y( ui_SyspadHintRightImage, 0 );
lv_obj_set_align( ui_SyspadHintRightImage, LV_ALIGN_RIGHT_MID );
lv_obj_add_flag( ui_SyspadHintRightImage, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_SyspadHintRightImage, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_SyspadHintLeftImage = lv_img_create(ui_SyspadHintPanel);
lv_img_set_src(ui_SyspadHintLeftImage, &ui_img_left_png);
lv_obj_set_width( ui_SyspadHintLeftImage, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadHintLeftImage, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadHintLeftImage, 10 );
lv_obj_set_y( ui_SyspadHintLeftImage, 0 );
lv_obj_set_align( ui_SyspadHintLeftImage, LV_ALIGN_LEFT_MID );
lv_obj_add_flag( ui_SyspadHintLeftImage, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_SyspadHintLeftImage, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_SyspadVolumePanel = lv_obj_create(ui_SyspadFullPanel);
lv_obj_set_width( ui_SyspadVolumePanel, lv_pct(100));
lv_obj_set_height( ui_SyspadVolumePanel, lv_pct(100));
lv_obj_set_align( ui_SyspadVolumePanel, LV_ALIGN_TOP_MID );
lv_obj_add_flag( ui_SyspadVolumePanel, LV_OBJ_FLAG_HIDDEN );   /// Flags
lv_obj_clear_flag( ui_SyspadVolumePanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_SyspadVolumePanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_SyspadVolumePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_SyspadVolumePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_SyspadVolumePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_SyspadVolumePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_SyspadVolumePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_SyspadVolumePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadVolumeHitImage1 = lv_img_create(ui_SyspadVolumePanel);
lv_img_set_src(ui_SyspadVolumeHitImage1, &ui_img_anticlockwise_png);
lv_obj_set_width( ui_SyspadVolumeHitImage1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadVolumeHitImage1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadVolumeHitImage1, -30 );
lv_obj_set_y( ui_SyspadVolumeHitImage1, -8 );
lv_obj_set_align( ui_SyspadVolumeHitImage1, LV_ALIGN_BOTTOM_MID );
lv_obj_add_flag( ui_SyspadVolumeHitImage1, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_SyspadVolumeHitImage1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_SyspadBrightnessLabel1 = lv_label_create(ui_SyspadVolumeHitImage1);
lv_obj_set_width( ui_SyspadBrightnessLabel1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadBrightnessLabel1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadBrightnessLabel1, 0 );
lv_obj_set_y( ui_SyspadBrightnessLabel1, 1 );
lv_obj_set_align( ui_SyspadBrightnessLabel1, LV_ALIGN_CENTER );
lv_label_set_text(ui_SyspadBrightnessLabel1,"-");
lv_obj_set_style_text_font(ui_SyspadBrightnessLabel1, &ui_font_SourceHanCrazyCube30, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadVolumeHitImage2 = lv_img_create(ui_SyspadVolumePanel);
lv_img_set_src(ui_SyspadVolumeHitImage2, &ui_img_clockwise_png);
lv_obj_set_width( ui_SyspadVolumeHitImage2, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadVolumeHitImage2, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadVolumeHitImage2, 30 );
lv_obj_set_y( ui_SyspadVolumeHitImage2, -8 );
lv_obj_set_align( ui_SyspadVolumeHitImage2, LV_ALIGN_BOTTOM_MID );
lv_obj_add_flag( ui_SyspadVolumeHitImage2, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_SyspadVolumeHitImage2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_SyspadBrightnessLabe2 = lv_label_create(ui_SyspadVolumeHitImage2);
lv_obj_set_width( ui_SyspadBrightnessLabe2, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadBrightnessLabe2, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadBrightnessLabe2, 0 );
lv_obj_set_y( ui_SyspadBrightnessLabe2, 2 );
lv_obj_set_align( ui_SyspadBrightnessLabe2, LV_ALIGN_CENTER );
lv_label_set_text(ui_SyspadBrightnessLabe2,"+");
lv_obj_set_style_text_font(ui_SyspadBrightnessLabe2, &ui_font_SourceHanCrazyCube26, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadVolumeImage = lv_img_create(ui_SyspadVolumePanel);
lv_img_set_src(ui_SyspadVolumeImage, &ui_img_volume_png);
lv_obj_set_width( ui_SyspadVolumeImage, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadVolumeImage, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadVolumeImage, 25 );
lv_obj_set_y( ui_SyspadVolumeImage, 24 );
lv_obj_add_flag( ui_SyspadVolumeImage, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_SyspadVolumeImage, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_SyspadVolumeHitLabel = lv_label_create(ui_SyspadVolumePanel);
lv_obj_set_width( ui_SyspadVolumeHitLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadVolumeHitLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadVolumeHitLabel, 0 );
lv_obj_set_y( ui_SyspadVolumeHitLabel, 32 );
lv_obj_set_align( ui_SyspadVolumeHitLabel, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_SyspadVolumeHitLabel,"音量");
lv_obj_set_style_text_font(ui_SyspadVolumeHitLabel, &ui_font_SourceHanCrazyCube26, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadVolumeBar = lv_bar_create(ui_SyspadVolumePanel);
lv_bar_set_value(ui_SyspadVolumeBar,25,LV_ANIM_OFF);
lv_obj_set_width( ui_SyspadVolumeBar, 180);
lv_obj_set_height( ui_SyspadVolumeBar, 22);
lv_obj_set_x( ui_SyspadVolumeBar, 0 );
lv_obj_set_y( ui_SyspadVolumeBar, 33 );
lv_obj_set_align( ui_SyspadVolumeBar, LV_ALIGN_CENTER );

ui_SyspadBrightnessPanel = lv_obj_create(ui_SyspadFullPanel);
lv_obj_set_width( ui_SyspadBrightnessPanel, lv_pct(100));
lv_obj_set_height( ui_SyspadBrightnessPanel, lv_pct(100));
lv_obj_set_align( ui_SyspadBrightnessPanel, LV_ALIGN_TOP_MID );
lv_obj_add_flag( ui_SyspadBrightnessPanel, LV_OBJ_FLAG_HIDDEN );   /// Flags
lv_obj_clear_flag( ui_SyspadBrightnessPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_SyspadBrightnessPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_SyspadBrightnessPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_SyspadBrightnessPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_SyspadBrightnessPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_SyspadBrightnessPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_SyspadBrightnessPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_SyspadBrightnessPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadBrightnessHitImage2 = lv_img_create(ui_SyspadBrightnessPanel);
lv_img_set_src(ui_SyspadBrightnessHitImage2, &ui_img_anticlockwise_png);
lv_obj_set_width( ui_SyspadBrightnessHitImage2, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadBrightnessHitImage2, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadBrightnessHitImage2, -30 );
lv_obj_set_y( ui_SyspadBrightnessHitImage2, -8 );
lv_obj_set_align( ui_SyspadBrightnessHitImage2, LV_ALIGN_BOTTOM_MID );
lv_obj_add_flag( ui_SyspadBrightnessHitImage2, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_SyspadBrightnessHitImage2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_SyspadBrightnessLabel3 = lv_label_create(ui_SyspadBrightnessHitImage2);
lv_obj_set_width( ui_SyspadBrightnessLabel3, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadBrightnessLabel3, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadBrightnessLabel3, 0 );
lv_obj_set_y( ui_SyspadBrightnessLabel3, 1 );
lv_obj_set_align( ui_SyspadBrightnessLabel3, LV_ALIGN_CENTER );
lv_label_set_text(ui_SyspadBrightnessLabel3,"-");
lv_obj_set_style_text_font(ui_SyspadBrightnessLabel3, &ui_font_SourceHanCrazyCube30, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadBrightnessHitImage1 = lv_img_create(ui_SyspadBrightnessPanel);
lv_img_set_src(ui_SyspadBrightnessHitImage1, &ui_img_clockwise_png);
lv_obj_set_width( ui_SyspadBrightnessHitImage1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadBrightnessHitImage1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadBrightnessHitImage1, 30 );
lv_obj_set_y( ui_SyspadBrightnessHitImage1, -8 );
lv_obj_set_align( ui_SyspadBrightnessHitImage1, LV_ALIGN_BOTTOM_MID );
lv_obj_add_flag( ui_SyspadBrightnessHitImage1, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_SyspadBrightnessHitImage1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_SyspadBrightnessLabel4 = lv_label_create(ui_SyspadBrightnessHitImage1);
lv_obj_set_width( ui_SyspadBrightnessLabel4, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadBrightnessLabel4, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadBrightnessLabel4, 0 );
lv_obj_set_y( ui_SyspadBrightnessLabel4, 2 );
lv_obj_set_align( ui_SyspadBrightnessLabel4, LV_ALIGN_CENTER );
lv_label_set_text(ui_SyspadBrightnessLabel4,"+");
lv_obj_set_style_text_font(ui_SyspadBrightnessLabel4, &ui_font_SourceHanCrazyCube26, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadBrightnessImage = lv_img_create(ui_SyspadBrightnessPanel);
lv_img_set_src(ui_SyspadBrightnessImage, &ui_img_brightness_png);
lv_obj_set_width( ui_SyspadBrightnessImage, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadBrightnessImage, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadBrightnessImage, 20 );
lv_obj_set_y( ui_SyspadBrightnessImage, 24 );
lv_obj_add_flag( ui_SyspadBrightnessImage, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_SyspadBrightnessImage, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_SyspadBrightnessBar = lv_bar_create(ui_SyspadBrightnessPanel);
lv_bar_set_value(ui_SyspadBrightnessBar,25,LV_ANIM_OFF);
lv_obj_set_width( ui_SyspadBrightnessBar, 180);
lv_obj_set_height( ui_SyspadBrightnessBar, 22);
lv_obj_set_x( ui_SyspadBrightnessBar, 0 );
lv_obj_set_y( ui_SyspadBrightnessBar, 33 );
lv_obj_set_align( ui_SyspadBrightnessBar, LV_ALIGN_CENTER );

ui_SyspadBrightnessHitLabel = lv_label_create(ui_SyspadBrightnessPanel);
lv_obj_set_width( ui_SyspadBrightnessHitLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadBrightnessHitLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadBrightnessHitLabel, 0 );
lv_obj_set_y( ui_SyspadBrightnessHitLabel, 34 );
lv_obj_set_align( ui_SyspadBrightnessHitLabel, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_SyspadBrightnessHitLabel,"屏幕");
lv_obj_set_style_text_font(ui_SyspadBrightnessHitLabel, &ui_font_SourceHanCrazyCube26, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadManualPanel = lv_obj_create(ui_SyspadFullPanel);
lv_obj_set_width( ui_SyspadManualPanel, lv_pct(100));
lv_obj_set_height( ui_SyspadManualPanel, lv_pct(100));
lv_obj_set_align( ui_SyspadManualPanel, LV_ALIGN_TOP_MID );
lv_obj_add_flag( ui_SyspadManualPanel, LV_OBJ_FLAG_HIDDEN );   /// Flags
lv_obj_clear_flag( ui_SyspadManualPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_SyspadManualPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_SyspadManualPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_SyspadManualPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_SyspadManualPanel, 4, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_SyspadManualPanel, 4, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_SyspadManualPanel, 6, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_SyspadManualPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadManualTitleLabel = lv_label_create(ui_SyspadManualPanel);
lv_obj_set_width( ui_SyspadManualTitleLabel, lv_pct(100));
lv_obj_set_height( ui_SyspadManualTitleLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_SyspadManualTitleLabel, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_SyspadManualTitleLabel,"Title");
lv_obj_set_style_text_letter_space(ui_SyspadManualTitleLabel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_line_space(ui_SyspadManualTitleLabel, 2, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_align(ui_SyspadManualTitleLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_SyspadManualTitleLabel, &ui_font_SourceHanCrazyCube26, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadManualContentLabel = lv_label_create(ui_SyspadManualPanel);
lv_obj_set_width( ui_SyspadManualContentLabel, lv_pct(100));
lv_obj_set_height( ui_SyspadManualContentLabel, lv_pct(60));
lv_obj_set_x( ui_SyspadManualContentLabel, 0 );
lv_obj_set_y( ui_SyspadManualContentLabel, 34 );
lv_obj_set_align( ui_SyspadManualContentLabel, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_SyspadManualContentLabel,"Content");
lv_obj_set_style_text_letter_space(ui_SyspadManualContentLabel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_line_space(ui_SyspadManualContentLabel, 2, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_align(ui_SyspadManualContentLabel, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_SyspadManualContentLabel, &ui_font_SourceHanCrazyCube22, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadLEDPanel = lv_obj_create(ui_SyspadFullPanel);
lv_obj_set_width( ui_SyspadLEDPanel, lv_pct(100));
lv_obj_set_height( ui_SyspadLEDPanel, lv_pct(100));
lv_obj_set_align( ui_SyspadLEDPanel, LV_ALIGN_TOP_MID );
lv_obj_add_flag( ui_SyspadLEDPanel, LV_OBJ_FLAG_HIDDEN );   /// Flags
lv_obj_clear_flag( ui_SyspadLEDPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_SyspadLEDPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_SyspadLEDPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_SyspadLEDPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_SyspadLEDPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_SyspadLEDPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_SyspadLEDPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_SyspadLEDPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadLEDHitImage = lv_img_create(ui_SyspadLEDPanel);
lv_img_set_src(ui_SyspadLEDHitImage, &ui_img_anticlockwise_png);
lv_obj_set_width( ui_SyspadLEDHitImage, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadLEDHitImage, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadLEDHitImage, -30 );
lv_obj_set_y( ui_SyspadLEDHitImage, -8 );
lv_obj_set_align( ui_SyspadLEDHitImage, LV_ALIGN_BOTTOM_MID );
lv_obj_add_flag( ui_SyspadLEDHitImage, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_SyspadLEDHitImage, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_SyspadLEDLabel = lv_label_create(ui_SyspadLEDHitImage);
lv_obj_set_width( ui_SyspadLEDLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadLEDLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadLEDLabel, 0 );
lv_obj_set_y( ui_SyspadLEDLabel, 1 );
lv_obj_set_align( ui_SyspadLEDLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_SyspadLEDLabel,"-");
lv_obj_set_style_text_font(ui_SyspadLEDLabel, &ui_font_SourceHanCrazyCube30, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadLEDHitImage1 = lv_img_create(ui_SyspadLEDPanel);
lv_img_set_src(ui_SyspadLEDHitImage1, &ui_img_clockwise_png);
lv_obj_set_width( ui_SyspadLEDHitImage1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadLEDHitImage1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadLEDHitImage1, 30 );
lv_obj_set_y( ui_SyspadLEDHitImage1, -8 );
lv_obj_set_align( ui_SyspadLEDHitImage1, LV_ALIGN_BOTTOM_MID );
lv_obj_add_flag( ui_SyspadLEDHitImage1, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_SyspadLEDHitImage1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_SyspadLEDLabel5 = lv_label_create(ui_SyspadLEDHitImage1);
lv_obj_set_width( ui_SyspadLEDLabel5, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadLEDLabel5, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadLEDLabel5, 0 );
lv_obj_set_y( ui_SyspadLEDLabel5, 2 );
lv_obj_set_align( ui_SyspadLEDLabel5, LV_ALIGN_CENTER );
lv_label_set_text(ui_SyspadLEDLabel5,"+");
lv_obj_set_style_text_font(ui_SyspadLEDLabel5, &ui_font_SourceHanCrazyCube26, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadLEDImage1 = lv_img_create(ui_SyspadLEDPanel);
lv_img_set_src(ui_SyspadLEDImage1, &ui_img_led_png);
lv_obj_set_width( ui_SyspadLEDImage1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadLEDImage1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadLEDImage1, 16 );
lv_obj_set_y( ui_SyspadLEDImage1, 14 );
lv_obj_add_flag( ui_SyspadLEDImage1, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_SyspadLEDImage1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_SyspadLEDBar = lv_bar_create(ui_SyspadLEDPanel);
lv_bar_set_value(ui_SyspadLEDBar,25,LV_ANIM_OFF);
lv_obj_set_width( ui_SyspadLEDBar, 180);
lv_obj_set_height( ui_SyspadLEDBar, 22);
lv_obj_set_x( ui_SyspadLEDBar, 0 );
lv_obj_set_y( ui_SyspadLEDBar, 33 );
lv_obj_set_align( ui_SyspadLEDBar, LV_ALIGN_CENTER );

ui_SyspadLEDHitLabel = lv_label_create(ui_SyspadLEDPanel);
lv_obj_set_width( ui_SyspadLEDHitLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadLEDHitLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadLEDHitLabel, 0 );
lv_obj_set_y( ui_SyspadLEDHitLabel, 34 );
lv_obj_set_align( ui_SyspadLEDHitLabel, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_SyspadLEDHitLabel,"灯");
lv_obj_set_style_text_font(ui_SyspadLEDHitLabel, &ui_font_SourceHanCrazyCube26, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadLEDHitLabel1 = lv_label_create(ui_SyspadLEDPanel);
lv_obj_set_width( ui_SyspadLEDHitLabel1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadLEDHitLabel1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadLEDHitLabel1, 3 );
lv_obj_set_y( ui_SyspadLEDHitLabel1, -7 );
lv_obj_set_align( ui_SyspadLEDHitLabel1, LV_ALIGN_CENTER );
lv_label_set_text(ui_SyspadLEDHitLabel1,"手势向下切换开关");
lv_obj_set_style_text_font(ui_SyspadLEDHitLabel1, &ui_font_SourceHanCrazyCube26, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadAboutPanel = lv_obj_create(ui_SyspadFullPanel);
lv_obj_set_width( ui_SyspadAboutPanel, lv_pct(100));
lv_obj_set_height( ui_SyspadAboutPanel, lv_pct(100));
lv_obj_set_align( ui_SyspadAboutPanel, LV_ALIGN_TOP_MID );
lv_obj_add_flag( ui_SyspadAboutPanel, LV_OBJ_FLAG_HIDDEN );   /// Flags
lv_obj_clear_flag( ui_SyspadAboutPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_SyspadAboutPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_SyspadAboutPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_SyspadAboutPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_SyspadAboutPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_SyspadAboutPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_SyspadAboutPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_SyspadAboutPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadAboutHitRebootLabel = lv_label_create(ui_SyspadAboutPanel);
lv_obj_set_width( ui_SyspadAboutHitRebootLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadAboutHitRebootLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadAboutHitRebootLabel, 3 );
lv_obj_set_y( ui_SyspadAboutHitRebootLabel, -8 );
lv_obj_set_align( ui_SyspadAboutHitRebootLabel, LV_ALIGN_BOTTOM_MID );
lv_label_set_text(ui_SyspadAboutHitRebootLabel,"重启");
lv_obj_set_style_text_font(ui_SyspadAboutHitRebootLabel, &ui_font_SourceHanCrazyCube26, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadAboutLabel = lv_label_create(ui_SyspadAboutPanel);
lv_obj_set_width( ui_SyspadAboutLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadAboutLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadAboutLabel, 0 );
lv_obj_set_y( ui_SyspadAboutLabel, -15 );
lv_obj_set_align( ui_SyspadAboutLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_SyspadAboutLabel,"立方豆 CrazyCube\nv1.0\n作者 : 疯狂豆");
lv_obj_set_style_text_letter_space(ui_SyspadAboutLabel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_line_space(ui_SyspadAboutLabel, 2, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_align(ui_SyspadAboutLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_SyspadAboutLabel, &ui_font_SourceHanCrazyCube26, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadAboutHintRebootImage = lv_img_create(ui_SyspadAboutPanel);
lv_img_set_src(ui_SyspadAboutHintRebootImage, &ui_img_clockwise_png);
lv_obj_set_width( ui_SyspadAboutHintRebootImage, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadAboutHintRebootImage, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadAboutHintRebootImage, -42 );
lv_obj_set_y( ui_SyspadAboutHintRebootImage, -8 );
lv_obj_set_align( ui_SyspadAboutHintRebootImage, LV_ALIGN_BOTTOM_MID );
lv_obj_add_flag( ui_SyspadAboutHintRebootImage, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_SyspadAboutHintRebootImage, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_SyspadAboutDebugLabel = lv_label_create(ui_SyspadAboutPanel);
lv_obj_set_width( ui_SyspadAboutDebugLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadAboutDebugLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadAboutDebugLabel, 4 );
lv_obj_set_y( ui_SyspadAboutDebugLabel, -8 );
lv_obj_set_align( ui_SyspadAboutDebugLabel, LV_ALIGN_BOTTOM_LEFT );
lv_label_set_text(ui_SyspadAboutDebugLabel,"Dev");
lv_obj_set_style_text_color(ui_SyspadAboutDebugLabel, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_SyspadAboutDebugLabel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_SyspadAboutDebugLabel, &ui_font_SourceHanCrazyCube22, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadKeyboardPanel = lv_obj_create(ui_SyspadFullPanel);
lv_obj_set_width( ui_SyspadKeyboardPanel, lv_pct(100));
lv_obj_set_height( ui_SyspadKeyboardPanel, lv_pct(100));
lv_obj_set_x( ui_SyspadKeyboardPanel, 1 );
lv_obj_set_y( ui_SyspadKeyboardPanel, -1 );
lv_obj_set_align( ui_SyspadKeyboardPanel, LV_ALIGN_TOP_MID );
lv_obj_clear_flag( ui_SyspadKeyboardPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_SyspadKeyboardPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_SyspadKeyboardPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_SyspadKeyboardPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_SyspadKeyboardPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_SyspadKeyboardPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_SyspadKeyboardPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_SyspadKeyboardPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadKeyboardHitTitleLabel = lv_label_create(ui_SyspadKeyboardPanel);
lv_obj_set_width( ui_SyspadKeyboardHitTitleLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadKeyboardHitTitleLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadKeyboardHitTitleLabel, 22 );
lv_obj_set_y( ui_SyspadKeyboardHitTitleLabel, 33 );
lv_obj_set_align( ui_SyspadKeyboardHitTitleLabel, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_SyspadKeyboardHitTitleLabel,"手势蓝牙键盘");
lv_obj_set_style_text_font(ui_SyspadKeyboardHitTitleLabel, &ui_font_SourceHanCrazyCube26, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadKeyboardHitTitleLabel1 = lv_label_create(ui_SyspadKeyboardPanel);
lv_obj_set_width( ui_SyspadKeyboardHitTitleLabel1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadKeyboardHitTitleLabel1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadKeyboardHitTitleLabel1, 0 );
lv_obj_set_y( ui_SyspadKeyboardHitTitleLabel1, 77 );
lv_obj_set_align( ui_SyspadKeyboardHitTitleLabel1, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_SyspadKeyboardHitTitleLabel1,"状态: 未启用");
lv_obj_set_style_text_font(ui_SyspadKeyboardHitTitleLabel1, &ui_font_SourceHanCrazyCube26, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadKeyboardHintImage = lv_img_create(ui_SyspadKeyboardPanel);
lv_img_set_src(ui_SyspadKeyboardHintImage, &ui_img_keyboard_big_png);
lv_obj_set_width( ui_SyspadKeyboardHintImage, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadKeyboardHintImage, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadKeyboardHintImage, 20 );
lv_obj_set_y( ui_SyspadKeyboardHintImage, 26 );
lv_obj_add_flag( ui_SyspadKeyboardHintImage, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_SyspadKeyboardHintImage, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_SyspadKeyboardHintSwitchLabel = lv_label_create(ui_SyspadKeyboardPanel);
lv_obj_set_width( ui_SyspadKeyboardHintSwitchLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadKeyboardHintSwitchLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadKeyboardHintSwitchLabel, 22 );
lv_obj_set_y( ui_SyspadKeyboardHintSwitchLabel, -7 );
lv_obj_set_align( ui_SyspadKeyboardHintSwitchLabel, LV_ALIGN_BOTTOM_MID );
lv_label_set_text(ui_SyspadKeyboardHintSwitchLabel,"开关");
lv_obj_set_style_text_font(ui_SyspadKeyboardHintSwitchLabel, &ui_font_SourceHanCrazyCube26, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SyspadKeyboardSwitch = lv_switch_create(ui_SyspadKeyboardPanel);
lv_obj_set_width( ui_SyspadKeyboardSwitch, 50);
lv_obj_set_height( ui_SyspadKeyboardSwitch, 25);
lv_obj_set_x( ui_SyspadKeyboardSwitch, 0 );
lv_obj_set_y( ui_SyspadKeyboardSwitch, 30 );
lv_obj_set_align( ui_SyspadKeyboardSwitch, LV_ALIGN_CENTER );

ui_SyspadKeyboardHintActImage = lv_img_create(ui_SyspadKeyboardPanel);
lv_img_set_src(ui_SyspadKeyboardHintActImage, &ui_img_clockwise_png);
lv_obj_set_width( ui_SyspadKeyboardHintActImage, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SyspadKeyboardHintActImage, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SyspadKeyboardHintActImage, -26 );
lv_obj_set_y( ui_SyspadKeyboardHintActImage, -8 );
lv_obj_set_align( ui_SyspadKeyboardHintActImage, LV_ALIGN_BOTTOM_MID );
lv_obj_add_flag( ui_SyspadKeyboardHintActImage, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_SyspadKeyboardHintActImage, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

}

// void ui_init( void )
// {
// lv_disp_t *dispp = lv_disp_get_default();
// lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
// lv_disp_set_theme(dispp, theme);
// ui_SyspadFullScreen_screen_init();
// lv_disp_load_scr( ui_SyspadFullScreen);
// }
