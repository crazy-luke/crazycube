// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.0
// LVGL VERSION: 8.2.0
// PROJECT: Luanchpad

#include "ui.h"
#include "lv/ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t *ui_AppScreen;
lv_obj_t *ui_AppPanel1;
lv_obj_t *ui_LogoImage1;
lv_obj_t *ui_NameLabel1;
lv_obj_t *ui_AppPanel2;
lv_obj_t *ui_LogoImage2;
lv_obj_t *ui_NameLabel2;
lv_obj_t *ui_AppHintPanel;
lv_obj_t *ui_AppHintImage;
lv_obj_t *ui_AppHintLabel;

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
void ui_AppScreen_screen_init(void)
{
ui_AppScreen = lv_obj_create(NULL);
lv_obj_clear_flag( ui_AppScreen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_AppScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_AppScreen, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_AppPanel1 = lv_obj_create(ui_AppScreen);
lv_obj_set_width( ui_AppPanel1, lv_pct(100));
lv_obj_set_height( ui_AppPanel1, lv_pct(100));
lv_obj_set_align( ui_AppPanel1, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_AppPanel1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_AppPanel1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_AppPanel1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_AppPanel1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_AppPanel1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_LogoImage1 = lv_img_create(ui_AppPanel1);
lv_obj_set_width( ui_LogoImage1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_LogoImage1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_LogoImage1, 0 );
lv_obj_set_y( ui_LogoImage1, -15 );
lv_obj_set_align( ui_LogoImage1, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_LogoImage1, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_LogoImage1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_NameLabel1 = lv_label_create(ui_AppPanel1);
lv_obj_set_width( ui_NameLabel1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_NameLabel1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_NameLabel1, -1 );
lv_obj_set_y( ui_NameLabel1, 81 );
lv_obj_set_align( ui_NameLabel1, LV_ALIGN_CENTER );
lv_label_set_text(ui_NameLabel1,"Crazycube");
lv_obj_set_style_text_font(ui_NameLabel1, &ui_font_SourceHanCrazyCube26, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_AppPanel2 = lv_obj_create(ui_AppScreen);
lv_obj_set_width( ui_AppPanel2, lv_pct(100));
lv_obj_set_height( ui_AppPanel2, lv_pct(100));
lv_obj_set_align( ui_AppPanel2, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_AppPanel2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_AppPanel2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_AppPanel2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_AppPanel2, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_AppPanel2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_LogoImage2 = lv_img_create(ui_AppPanel2);
lv_obj_set_width( ui_LogoImage2, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_LogoImage2, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_LogoImage2, 0 );
lv_obj_set_y( ui_LogoImage2, -15 );
lv_obj_set_align( ui_LogoImage2, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_LogoImage2, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_LogoImage2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_NameLabel2 = lv_label_create(ui_AppPanel2);
lv_obj_set_width( ui_NameLabel2, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_NameLabel2, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_NameLabel2, -1 );
lv_obj_set_y( ui_NameLabel2, 81 );
lv_obj_set_align( ui_NameLabel2, LV_ALIGN_CENTER );
lv_label_set_text(ui_NameLabel2,"Crazycube");
lv_obj_set_style_text_font(ui_NameLabel2, &ui_font_SourceHanCrazyCube26, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_AppHintPanel = lv_obj_create(ui_AppScreen);
lv_obj_set_height( ui_AppHintPanel, 60);
lv_obj_set_width( ui_AppHintPanel, LV_SIZE_CONTENT);  /// 41
lv_obj_set_x( ui_AppHintPanel, 10 );
lv_obj_set_y( ui_AppHintPanel, 35 );
lv_obj_clear_flag( ui_AppHintPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_AppHintPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_AppHintPanel, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_AppHintPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_AppHintPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_AppHintPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_AppHintPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_AppHintPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_AppHintPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_AppHintImage = lv_img_create(ui_AppHintPanel);
lv_img_set_src(ui_AppHintImage, &ui_img_anticlockwise_png);
lv_obj_set_width( ui_AppHintImage, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_AppHintImage, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_AppHintImage, LV_ALIGN_BOTTOM_MID );
lv_obj_add_flag( ui_AppHintImage, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_AppHintImage, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_AppHintLabel = lv_label_create(ui_AppHintPanel);
lv_obj_set_width( ui_AppHintLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_AppHintLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_AppHintLabel, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_AppHintLabel,"返回");
lv_obj_set_style_text_font(ui_AppHintLabel, &ui_font_SourceHanCrazyCube22, LV_PART_MAIN| LV_STATE_DEFAULT);

}

void ui_init( void )
{
lv_disp_t *dispp = lv_disp_get_default();
lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
lv_disp_set_theme(dispp, theme);
ui_AppScreen_screen_init();
lv_disp_load_scr( ui_AppScreen);
}
