/**
 * @file  led.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @date 2022/6/20
 * @brief FastLED 控制 WS2812灯
 */

#pragma once

// #include <Adafruit_NeoPixel.h>

//重要，跳过 FastLED 引脚禁用限制 具体见 fastpin_esp32.h （PIN 20 被禁用了)

#define FASTLED_UNUSABLE_PIN_MASK (0ULL)

#include <FastLED.h>
#include <esp32-hal-timer.h>

#define MAX_LED_LIGHT 250
#define MIN_LED_LIGHT 25

#define DATA_PIN 20

#define NUM_LEDS 1

enum class  LedState {
  ON = 0,   //开灯
  OFF,  //关灯
  EFFECT,  //效果
};

class Led {
 private:
  const char * kTag = "Led";
  uint8_t brightness_ = 100;
  CRGB color_cache_[1];
  CRGB leds_[1];

private:
  friend void LedEffectTask(void* param);
  void BreathEffect(bool rainbow);
  TaskHandle_t task_handle_ = NULL;
  int rainbow_hue_;

  LedState state_;
  uint8_t off_count = 0;
  void ResumeColor(); //set color with color_cache_
  void TurnON();
  void TurnOFF();
  void StartBreathEffect();
  void StopEffect();

 public:
  Led();
  void Init(uint8_t brightness, uint8_t r, uint8_t g, uint8_t b);
  void SetBrightness(uint8_t b);
  void SetRGB(uint8_t r, uint8_t g, uint8_t b);
  LedState SwitchState();
  LedState state();
  void SetState(LedState state);
};