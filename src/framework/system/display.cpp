/**
 * @file display.cpp
 * @author CrazyLuke
 * @brief 参考 lvgl/example/arduino/LVGL_Arduino.ino
 * @version 1.0
 * @date 2022-06-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "display.h"
#include "tools/crazy_log.h"

#define DISP_BUF_SIZE (SCREEN_WIDTH*SCREEN_HEIGHT/1)

TFT_eSPI *g_tft;

bool _lv_ui_enable = true;  //允许 LVGL 刷新 UI

void my_print(const char *buf) {
  CrazyLog::d("lv","%s",buf);
}

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area,lv_color_t *color_p) {
  if(_lv_ui_enable){
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    g_tft->startWrite();
    g_tft->setAddrWindow(area->x1, area->y1, w, h);
    g_tft->pushColors((uint16_t *)&color_p->full, w * h, true);
    g_tft->endWrite();
  }

#if LV_USE_LOG
  if(!_lv_ui_enable) my_print("not allow my_disp_flush");
#endif

  lv_disp_flush_ready(disp);
}

void Display::set_lv_ui_enable(bool flag){
  _lv_ui_enable = flag;
  CrazyLog::d(kTag, "set_lv_ui_enable: %d",flag);
}

bool Display::lv_ui_enable() {
  return _lv_ui_enable;
}

void Display::InitLvgl()
{
  lv_init();
// #if LV_USE_LOG
//   lv_log_register_print_cb(my_print); /* register print function for debugging */
// #endif

  //display buffer
  static lv_disp_draw_buf_t disp_buf;
  lv_color_t* lv_buf = (lv_color_t*)ps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t));
  lv_disp_draw_buf_init(&disp_buf, lv_buf, NULL, DISP_BUF_SIZE);
  
  //Initialize the display
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = SCREEN_WIDTH;
  disp_drv.ver_res = SCREEN_HEIGHT;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &disp_buf;
  lv_disp_drv_register(&disp_drv);
}

void Display::Init(uint8_t brightness, uint8_t rotation, bool lvgl) {
  //tft
  g_tft = new TFT_eSPI(SCREEN_WIDTH, SCREEN_HEIGHT);
  // g_tft->initDMA();
  ledcSetup(LCD_BL_PWM_CHANNEL, 5000, 8);
  ledcAttachPin(LCD_BL_PIN, LCD_BL_PWM_CHANNEL);
  SetBrightness(0);
  g_tft->begin(); /* g_tft init */
  g_tft->setRotation(rotation);
  // g_tft->fillScreen(TFT_BLACK);
  if(lvgl) InitLvgl();
  SetBrightness(brightness);
}

void Display::Routine() { lv_timer_handler(); }

/**
 * @brief
 *
 * @param brightness  0 ~ 100
 */
void Display::SetBrightness(uint8_t brightness) {
  CrazyLog::d(kTag, "SetBrightness: %d", brightness);
  float duty = std::min((int)brightness, MAX_BRIGHTNESS) / 100.0;
  duty = constrain(duty, 0, 1);
  duty = 1 - duty;
  ledcWrite(LCD_BL_PWM_CHANNEL, (int)(duty * 255));
}

void Display::CreateTipsPannel() {
  if (tips_pannel_ == NULL) {
    tips_pannel_ = lv_obj_create(lv_scr_act());
    lv_obj_set_size(tips_pannel_, LV_PCT(100), LV_PCT(100));
    lv_obj_align(tips_pannel_, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_bg_color(tips_pannel_, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(tips_pannel_, LV_OPA_40, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_border_width(tips_pannel_, 0,
                                  LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(tips_pannel_, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(tips_pannel_, 0,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(tips_pannel_, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(tips_pannel_, 4,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  }
}

void Display::ShowTipsDisplay(String text, const lv_font_t *font) {
  CrazyLog::d(kTag, "ShowTipsDisplay: %s", text.c_str());
  if (tip_label_ == NULL) {
    CreateTipsPannel();
    tip_label_ = lv_label_create(tips_pannel_);
    lv_obj_set_size(tip_label_, LV_PCT(100), LV_PCT(100));
    lv_obj_align(tip_label_, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_bg_color(tip_label_, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(tip_label_, LV_OPA_TRANSP, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(tip_label_, text.c_str());
    lv_obj_set_style_text_font(tip_label_, font,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
  } else {
    lv_label_set_text(tip_label_, text.c_str());
  }
  lv_timer_handler();
}

void Display::ShowSubTipsDisplay(String text, const lv_font_t *font) {
  CrazyLog::d(kTag, "ShowSubTipsDisplay: %s", text.c_str());
  if (tip_sub_label_ == NULL) {
    CreateTipsPannel();
    tip_sub_label_ = lv_label_create(tips_pannel_);
    lv_obj_set_width(tip_sub_label_, LV_SIZE_CONTENT);
    lv_obj_set_height(tip_sub_label_, LV_SIZE_CONTENT);
    lv_obj_set_align(tip_sub_label_, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_style_bg_color(tip_sub_label_, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(tip_sub_label_, LV_OPA_TRANSP, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(tip_sub_label_, text.c_str());
    lv_obj_set_style_text_font(tip_sub_label_, font,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
  } else {
    lv_label_set_text(tip_sub_label_, text.c_str());
  }
  lv_timer_handler();
}

void Display::CleanTips() {
  if (tips_pannel_) {
    CrazyLog::d(kTag, "Clean sub_tip_label");
    lv_obj_del(tips_pannel_);
    tips_pannel_ = NULL;
    tip_sub_label_ = NULL;
    tip_label_ = NULL;
    lv_timer_handler();
  }
}

TFT_eSPI *Display::tft() { return g_tft; }


