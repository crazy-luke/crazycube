/**
 * @file button.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief OneButton
 * @version 0.1
 * @date 2023-01-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <OneButton.h>

#include <memory>

#define PIN_BUTTON_S1 GPIO_NUM_19
#define PIN_BUTTON_L1 GPIO_NUM_21
#define PIN_BUTTON_R1 GPIO_NUM_22

#define BUTTON_DEBOUNCE_TS 60  // 按钮去抖动
#define BUTTON_CLICK_TS 400    // 单击时间判定
#define BUTTON_PRESS_TS 800   // 长按时间判定

enum class ButtonID { S1, L1, R1 };

enum class ButtonState { Click, DoubuleClick, LongPress };

// CrazyAdam: better using c++ style instand of c style
using ButtonListener = void (*)(ButtonID, ButtonState, void *);
// typedef void (*ButtonListener)(ButtonID, ButtonState,void *);

class Button {
 private:
  const char *kTag = "Button";

  OneButton *s1_ = nullptr;
  OneButton *l1_ = nullptr;
  OneButton *r1_ = nullptr;

 private:
  int click_ticks_ = BUTTON_CLICK_TS;
  ButtonListener listener_;
  void *listener_param_ = NULL;

  friend void S1Clicked(void *param);
  friend void S1DoubleClicked(void *param);
  friend void S1LongPress(void *param);
  friend void L1Clicked(void *param);
  friend void L1DoubleClicked(void *param);
  friend void L1LongPress(void *param);
  friend void R1Clicked(void *param);
  friend void R1DoubleClicked(void *param);
  friend void R1LongPress(void *param);

  void Init(ButtonID id);

 public:
  ~Button();
  void SetListener(ButtonListener listener, void *param);
  void Routine();

  void AttachClickListener(ButtonID id);
  void AttachDoubleClickListener(ButtonID id);
  void AttachLongPressListener(ButtonID id);
  void Release(ButtonID id);
  void SetClickTicks(int ticks);
};