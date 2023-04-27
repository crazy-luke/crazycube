// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.0
// LVGL VERSION: 8.2.0
// PROJECT: CrazyCube_CubeManual

#include "ui.h"
#include "lv/ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t *ui_CubeManualScreen;
lv_obj_t *ui_CubeManualPanel;
lv_obj_t *ui_CubeManualSysbarPanel;
lv_obj_t *ui_CubeManualSysbarImage1;
lv_obj_t *ui_CubeManualScreen_Label1;
lv_obj_t *ui_CubeManualSysbarImage2;
lv_obj_t *ui_CubeManualScreen_Label3;
lv_obj_t *ui_CubeManualSysbarImage3;
lv_obj_t *ui_CubeManualScreen_Label4;
lv_obj_t *ui_CubeManualSysbarImage4;
lv_obj_t *ui_CubeManualScreen_Label5;
lv_obj_t *ui_CubeManualSysbarImage5;
lv_obj_t *ui_CubeManualScreen_Label6;
lv_obj_t *ui_CubeManualGesturePanel;
lv_obj_t *ui_CubeManualGestureLabel;
lv_obj_t *ui_CubeManualRSSIPanel;
lv_obj_t *ui_CubeManualRSSIBar;
lv_obj_t *ui_CubeManualRSSILabel;
lv_obj_t *ui_CubeManualTitleLabel;
lv_obj_t *ui_CubeManualHintLabel;
lv_obj_t *ui_CubeManualHintPanel;
lv_obj_t *ui_CubeManualHintImage;
lv_obj_t *ui_CubeManualHintLabel2;

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
void ui_CubeManualScreen_screen_init(void)
{
ui_CubeManualScreen = lv_obj_create(NULL);
lv_obj_clear_flag( ui_CubeManualScreen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_CubeManualScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_CubeManualScreen, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_CubeManualPanel = lv_obj_create(ui_CubeManualScreen);
lv_obj_set_width( ui_CubeManualPanel, lv_pct(100));
lv_obj_set_height( ui_CubeManualPanel, lv_pct(80));
lv_obj_set_align( ui_CubeManualPanel, LV_ALIGN_BOTTOM_MID );
lv_obj_clear_flag( ui_CubeManualPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_CubeManualPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_CubeManualPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_CubeManualPanel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_CubeManualPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_CubeManualPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_CubeManualPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_CubeManualPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_CubeManualPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_CubeManualSysbarPanel = lv_obj_create(ui_CubeManualPanel);
lv_obj_set_width( ui_CubeManualSysbarPanel, lv_pct(100));
lv_obj_set_height( ui_CubeManualSysbarPanel, lv_pct(100));
lv_obj_set_x( ui_CubeManualSysbarPanel, -1 );
lv_obj_set_y( ui_CubeManualSysbarPanel, 0 );
lv_obj_set_align( ui_CubeManualSysbarPanel, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_CubeManualSysbarPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_CubeManualSysbarPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_CubeManualSysbarPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_CubeManualSysbarPanel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_CubeManualSysbarPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_CubeManualSysbarPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_CubeManualSysbarPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_CubeManualSysbarPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_CubeManualSysbarPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_CubeManualSysbarImage1 = lv_img_create(ui_CubeManualSysbarPanel);
lv_img_set_src(ui_CubeManualSysbarImage1, &ui_img_wifi_off_png);
lv_obj_set_width( ui_CubeManualSysbarImage1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_CubeManualSysbarImage1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_CubeManualSysbarImage1, 20 );
lv_obj_set_y( ui_CubeManualSysbarImage1, 0 );
lv_obj_add_flag( ui_CubeManualSysbarImage1, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_CubeManualSysbarImage1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_CubeManualScreen_Label1 = lv_label_create(ui_CubeManualSysbarPanel);
lv_obj_set_width( ui_CubeManualScreen_Label1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_CubeManualScreen_Label1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_CubeManualScreen_Label1, 50 );
lv_obj_set_y( ui_CubeManualScreen_Label1, 0 );
lv_label_set_text(ui_CubeManualScreen_Label1,"WiFi 未连接");
lv_obj_set_style_text_font(ui_CubeManualScreen_Label1, &ui_font_SourceHanCrazyCube22, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_CubeManualSysbarImage2 = lv_img_create(ui_CubeManualSysbarPanel);
lv_img_set_src(ui_CubeManualSysbarImage2, &ui_img_wifi_on_png);
lv_obj_set_width( ui_CubeManualSysbarImage2, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_CubeManualSysbarImage2, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_CubeManualSysbarImage2, 20 );
lv_obj_set_y( ui_CubeManualSysbarImage2, 30 );
lv_obj_add_flag( ui_CubeManualSysbarImage2, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_CubeManualSysbarImage2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_CubeManualScreen_Label3 = lv_label_create(ui_CubeManualSysbarPanel);
lv_obj_set_width( ui_CubeManualScreen_Label3, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_CubeManualScreen_Label3, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_CubeManualScreen_Label3, 50 );
lv_obj_set_y( ui_CubeManualScreen_Label3, 30 );
lv_label_set_text(ui_CubeManualScreen_Label3,"WiFi 已连接");
lv_obj_set_style_text_font(ui_CubeManualScreen_Label3, &ui_font_SourceHanCrazyCube22, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_CubeManualSysbarImage3 = lv_img_create(ui_CubeManualSysbarPanel);
lv_img_set_src(ui_CubeManualSysbarImage3, &ui_img_lock_png);
lv_obj_set_width( ui_CubeManualSysbarImage3, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_CubeManualSysbarImage3, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_CubeManualSysbarImage3, 20 );
lv_obj_set_y( ui_CubeManualSysbarImage3, 60 );
lv_obj_add_flag( ui_CubeManualSysbarImage3, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_CubeManualSysbarImage3, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_CubeManualScreen_Label4 = lv_label_create(ui_CubeManualSysbarPanel);
lv_obj_set_width( ui_CubeManualScreen_Label4, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_CubeManualScreen_Label4, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_CubeManualScreen_Label4, 50 );
lv_obj_set_y( ui_CubeManualScreen_Label4, 60 );
lv_label_set_text(ui_CubeManualScreen_Label4,"屏幕已锁定");
lv_obj_set_style_text_font(ui_CubeManualScreen_Label4, &ui_font_SourceHanCrazyCube22, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_CubeManualSysbarImage4 = lv_img_create(ui_CubeManualSysbarPanel);
lv_img_set_src(ui_CubeManualSysbarImage4, &ui_img_keyboard_png);
lv_obj_set_width( ui_CubeManualSysbarImage4, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_CubeManualSysbarImage4, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_CubeManualSysbarImage4, 20 );
lv_obj_set_y( ui_CubeManualSysbarImage4, 90 );
lv_obj_add_flag( ui_CubeManualSysbarImage4, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_CubeManualSysbarImage4, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_CubeManualScreen_Label5 = lv_label_create(ui_CubeManualSysbarPanel);
lv_obj_set_width( ui_CubeManualScreen_Label5, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_CubeManualScreen_Label5, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_CubeManualScreen_Label5, 50 );
lv_obj_set_y( ui_CubeManualScreen_Label5, 90 );
lv_label_set_text(ui_CubeManualScreen_Label5,"蓝牙手势键盘");
lv_obj_set_style_text_font(ui_CubeManualScreen_Label5, &ui_font_SourceHanCrazyCube22, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_CubeManualSysbarImage5 = lv_img_create(ui_CubeManualSysbarPanel);
lv_img_set_src(ui_CubeManualSysbarImage5, &ui_img_assistant_on_png);
lv_obj_set_width( ui_CubeManualSysbarImage5, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_CubeManualSysbarImage5, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_CubeManualSysbarImage5, 20 );
lv_obj_set_y( ui_CubeManualSysbarImage5, 120 );
lv_obj_add_flag( ui_CubeManualSysbarImage5, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_CubeManualSysbarImage5, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_CubeManualScreen_Label6 = lv_label_create(ui_CubeManualSysbarPanel);
lv_obj_set_width( ui_CubeManualScreen_Label6, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_CubeManualScreen_Label6, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_CubeManualScreen_Label6, 50 );
lv_obj_set_y( ui_CubeManualScreen_Label6, 120 );
lv_label_set_text(ui_CubeManualScreen_Label6,"AI 助手可用");
lv_obj_set_style_text_font(ui_CubeManualScreen_Label6, &ui_font_SourceHanCrazyCube22, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_CubeManualGesturePanel = lv_obj_create(ui_CubeManualPanel);
lv_obj_set_width( ui_CubeManualGesturePanel, lv_pct(100));
lv_obj_set_height( ui_CubeManualGesturePanel, lv_pct(100));
lv_obj_set_align( ui_CubeManualGesturePanel, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_CubeManualGesturePanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_CubeManualGesturePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_CubeManualGesturePanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_CubeManualGesturePanel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_CubeManualGesturePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_CubeManualGesturePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_CubeManualGesturePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_CubeManualGesturePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_CubeManualGesturePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_CubeManualGestureLabel = lv_label_create(ui_CubeManualGesturePanel);
lv_obj_set_width( ui_CubeManualGestureLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_CubeManualGestureLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_CubeManualGestureLabel, 5 );
lv_obj_set_y( ui_CubeManualGestureLabel, 0 );
lv_label_set_text(ui_CubeManualGestureLabel,"上 下 左 右: 方向键\n向前: 锁屏或蓝牙键盘\n顺时针: 进APP或功能键\n逆时针: 退APP或功能键\n挥手: 切换状态栏");
lv_obj_set_style_text_font(ui_CubeManualGestureLabel, &ui_font_SourceHanCrazyCube22, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_CubeManualRSSIPanel = lv_obj_create(ui_CubeManualPanel);
lv_obj_set_width( ui_CubeManualRSSIPanel, lv_pct(100));
lv_obj_set_height( ui_CubeManualRSSIPanel, lv_pct(100));
lv_obj_set_align( ui_CubeManualRSSIPanel, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_CubeManualRSSIPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_CubeManualRSSIPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_CubeManualRSSIPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_CubeManualRSSIPanel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_CubeManualRSSIPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_CubeManualRSSIPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_CubeManualRSSIPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_CubeManualRSSIPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_CubeManualRSSIPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_CubeManualRSSIBar = lv_bar_create(ui_CubeManualRSSIPanel);
lv_bar_set_value(ui_CubeManualRSSIBar,55,LV_ANIM_OFF);
lv_obj_set_width( ui_CubeManualRSSIBar, 200);
lv_obj_set_height( ui_CubeManualRSSIBar, 20);
lv_obj_set_align( ui_CubeManualRSSIBar, LV_ALIGN_CENTER );

ui_CubeManualRSSILabel = lv_label_create(ui_CubeManualRSSIPanel);
lv_obj_set_width( ui_CubeManualRSSILabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_CubeManualRSSILabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_CubeManualRSSILabel, 0 );
lv_obj_set_y( ui_CubeManualRSSILabel, 40 );
lv_obj_set_align( ui_CubeManualRSSILabel, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_CubeManualRSSILabel,"55");
lv_obj_set_style_text_font(ui_CubeManualRSSILabel, &ui_font_SourceHanCrazyCube26, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_CubeManualTitleLabel = lv_label_create(ui_CubeManualScreen);
lv_obj_set_width( ui_CubeManualTitleLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_CubeManualTitleLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_CubeManualTitleLabel, 20 );
lv_obj_set_y( ui_CubeManualTitleLabel, 10 );
lv_label_set_text(ui_CubeManualTitleLabel,"状态栏图标");
lv_obj_set_style_text_font(ui_CubeManualTitleLabel, &ui_font_SourceHanCrazyCube26, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_CubeManualHintLabel = lv_label_create(ui_CubeManualScreen);
lv_obj_set_width( ui_CubeManualHintLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_CubeManualHintLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_CubeManualHintLabel, -10 );
lv_obj_set_y( ui_CubeManualHintLabel, -6 );
lv_obj_set_align( ui_CubeManualHintLabel, LV_ALIGN_BOTTOM_RIGHT );
lv_label_set_text(ui_CubeManualHintLabel,"1/3");
lv_obj_set_style_text_font(ui_CubeManualHintLabel, &ui_font_SourceHanCrazyCube22, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_CubeManualHintPanel = lv_obj_create(ui_CubeManualScreen);
lv_obj_set_width( ui_CubeManualHintPanel, 72);
lv_obj_set_height( ui_CubeManualHintPanel, 30);
lv_obj_set_x( ui_CubeManualHintPanel, 20 );
lv_obj_set_y( ui_CubeManualHintPanel, -6 );
lv_obj_set_align( ui_CubeManualHintPanel, LV_ALIGN_BOTTOM_MID );
lv_obj_clear_flag( ui_CubeManualHintPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_CubeManualHintPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_CubeManualHintPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_CubeManualHintPanel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_CubeManualHintPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_CubeManualHintPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_CubeManualHintPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_CubeManualHintPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_CubeManualHintPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_CubeManualHintImage = lv_img_create(ui_CubeManualHintPanel);
lv_img_set_src(ui_CubeManualHintImage, &ui_img_left_png);
lv_obj_set_width( ui_CubeManualHintImage, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_CubeManualHintImage, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_CubeManualHintImage, LV_ALIGN_LEFT_MID );
lv_obj_add_flag( ui_CubeManualHintImage, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_CubeManualHintImage, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_CubeManualHintLabel2 = lv_label_create(ui_CubeManualHintPanel);
lv_obj_set_width( ui_CubeManualHintLabel2, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_CubeManualHintLabel2, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_CubeManualHintLabel2, LV_ALIGN_RIGHT_MID );
lv_label_set_text(ui_CubeManualHintLabel2,"向左");
lv_obj_set_style_text_font(ui_CubeManualHintLabel2, &ui_font_SourceHanCrazyCube22, LV_PART_MAIN| LV_STATE_DEFAULT);

}

// void ui_init( void )
// {
// lv_disp_t *dispp = lv_disp_get_default();
// lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
// lv_disp_set_theme(dispp, theme);
// ui_CubeManualScreen_screen_init();
// lv_disp_load_scr( ui_CubeManualScreen);
// }
