#include "led.h"

#include "tools/crazy_log.h"
#include "sys.h"

Led::Led(){
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds_, NUM_LEDS);
}

void Led::Init(uint8_t brightness, uint8_t r, uint8_t g, uint8_t b){
  CrazyLog::d(kTag, "Init"); 
  brightness_ = brightness;
  FastLED.setBrightness(brightness);
  leds_[0] =  CRGB(r,g,b);
  color_cache_[0] =  CRGB(r,g,b);
  state_ = LedState::OFF;
}

/**
 * @brief  Set a led's color using r g b
 *
 * @param r 0~255
 * @param g 0~255
 * @param b 0~255
 */
void Led::SetRGB(uint8_t r, uint8_t g, uint8_t b) {
  CrazyLog::d(kTag, "SetRGB");
  leds_[0] =  CRGB(r,g,b);
  color_cache_[0] =  CRGB(r,g,b);
  FastLED.show();
}

/**
 * @brief  Adjust output brightness
 *
 * @param b  Brightness setting, 0=minimum (off), 255=brightest.
 */
void Led::SetBrightness(uint8_t b) {
  CrazyLog::d(kTag, "SetBrightness: %d", b);
  brightness_ = b;
  FastLED.setBrightness(b);
  FastLED.show();
}

void Led::TurnON() {
  CrazyLog::d(kTag, "TurnON");
  StopEffect();
  FastLED.setBrightness(brightness_);
  FastLED.show();
}

void Led::TurnOFF() {
  CrazyLog::d(kTag, "TurnOFF");
  StopEffect();
  FastLED.setBrightness(0);
  FastLED.show();
  off_count++;
}

void Led::SetState(LedState state){
  state_ = state;
  switch(state){
    case LedState::ON:
      TurnON();
      break;
    case LedState::OFF:
      TurnOFF();
      break;
    case LedState::EFFECT:
      StartBreathEffect();
      break;
  }
}

LedState Led::SwitchState(){
  CrazyLog::d(kTag,"SwitchState");
  LedState state;
  if(state_ == LedState::ON){
    state = LedState::OFF;
  }else if(state_ == LedState::EFFECT)
    state = LedState::OFF;
  else if(state_ == LedState::OFF) { //switch on and effect
    if(off_count % 2 == 1)
      state = LedState::EFFECT;
    else
      state = LedState::ON;
  }
   SetState(state);
   return state;
}

void LedEffectTask(void* param){
  Led* led = static_cast<Led*>(param);
  CrazyLog::d(led->kTag,"LedEffectTask");

  randomSeed(millis());
  bool rainbow = random(0,100) > 50;
  while (true)
  {
    led->BreathEffect(rainbow);
    delay(10);
  }  
}

void Led::StartBreathEffect(){
  CrazyLog::d(kTag, "StartBreathEffect");
  if(task_handle_!=nullptr)
  {
    CrazyLog::w(kTag,"StartBreathEffect alreay started!");
    return;
  }
  if(brightness_ == 0){
    CrazyLog::w(kTag, "fialed: brightness is 0");
    return;
  }
  rainbow_hue_ = 0;
  xTaskCreatePinnedToCore(LedEffectTask, "LedEffectTask", 1024*2, this,
                          TASK_PRIORITY_LED, &task_handle_, CORE_0);
}

LedState Led::state(){
  return state_;
}

void Led::StopEffect(){
  CrazyLog::d(kTag,"StopEffect");
  if (task_handle_) {
    vTaskDelete(task_handle_);
    task_handle_ = NULL;
    ResumeColor();
  }
}

void Led::ResumeColor(){
  leds_[0] =  color_cache_[0];  //resume color
  FastLED.show();
}

#define RAINBOW_DIVISOR 30
#define BREATH_MIN_BRIGHTNESS 20
// #define BREATH_MAX_BRIGHTNESS 64

 void Led::BreathEffect(bool rainbow){
  float breath = (exp(sin(millis()/5000.0*PI)) - 0.36787944)*108.0;
  breath = map(breath, 0, 255, BREATH_MIN_BRIGHTNESS, brightness_);
  FastLED.setBrightness(breath);
  if(rainbow){
    fill_rainbow(leds_, NUM_LEDS, (rainbow_hue_++/RAINBOW_DIVISOR));
    if(rainbow_hue_ == (255 * RAINBOW_DIVISOR))  rainbow_hue_ = 0;
  }
  FastLED.show();
 }