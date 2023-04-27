#include "button.h"

#include "tools/crazy_log.h"

Button::~Button() {
  if (s1_) delete (s1_);
  if (l1_) delete (l1_);
  if (r1_) delete (r1_);
}

void Button::Init(ButtonID id) {
  if (id == ButtonID::S1 && s1_ == nullptr) {
    s1_ = new OneButton(PIN_BUTTON_S1, true, true);
    s1_->setDebounceTicks(BUTTON_DEBOUNCE_TS);
    s1_->setClickTicks(click_ticks_);
    s1_->setPressTicks(BUTTON_PRESS_TS);
  } else if (id == ButtonID::L1 && l1_ == nullptr) {
    l1_ = new OneButton(PIN_BUTTON_L1, true, true);
    l1_->setDebounceTicks(BUTTON_DEBOUNCE_TS);
    l1_->setClickTicks(click_ticks_);
    l1_->setPressTicks(BUTTON_PRESS_TS);
  } else if (id == ButtonID::R1 && r1_ == nullptr) {
    r1_ = new OneButton(PIN_BUTTON_R1, true, true);
    r1_->setDebounceTicks(BUTTON_DEBOUNCE_TS);
    r1_->setClickTicks(click_ticks_);
    r1_->setPressTicks(BUTTON_PRESS_TS);
  }
}

void Button::SetListener(ButtonListener listener, void *param) {
  listener_ = listener;
  listener_param_ = param;
}

void Button::Routine() {
  if (s1_) s1_->tick();
  if (l1_) l1_->tick();
  if (r1_) r1_->tick();
}

void S1Clicked(void *param) {
  Button *btn = static_cast<Button *>(param);
  CrazyLog::d(btn->kTag, "S1Clicked");
  if (btn->listener_)
    btn->listener_(ButtonID::S1, ButtonState::Click, btn->listener_param_);
}

void S1DoubleClicked(void *param) {
  Button *btn = static_cast<Button *>(param);
  CrazyLog::d(btn->kTag, "S1DoubleClicked");
  if (btn->listener_)
    btn->listener_(ButtonID::S1, ButtonState::DoubuleClick,
                   btn->listener_param_);
}

void S1LongPress(void *param) {
  Button *btn = static_cast<Button *>(param);
  CrazyLog::d(btn->kTag, "S1LongPress");
  if (btn->listener_)
    btn->listener_(ButtonID::S1, ButtonState::LongPress, btn->listener_param_);
}

void L1Clicked(void *param) {
  Button *btn = static_cast<Button *>(param);
  CrazyLog::d(btn->kTag, "L1Clicked");
  if (btn->listener_)
    btn->listener_(ButtonID::L1, ButtonState::Click, btn->listener_param_);
}

void L1DoubleClicked(void *param) {
  Button *btn = static_cast<Button *>(param);
  CrazyLog::d(btn->kTag, "L1DoubleClicked");
  if (btn->listener_)
    btn->listener_(ButtonID::L1, ButtonState::DoubuleClick,
                   btn->listener_param_);
}

void L1LongPress(void *param) {
  Button *btn = static_cast<Button *>(param);
  CrazyLog::d(btn->kTag, "L1LongPress");
  if (btn->listener_)
    btn->listener_(ButtonID::L1, ButtonState::LongPress, btn->listener_param_);
}

void R1Clicked(void *param) {
  Button *btn = static_cast<Button *>(param);
  CrazyLog::d(btn->kTag, "R1Clicked");
  if (btn->listener_)
    btn->listener_(ButtonID::R1, ButtonState::Click, btn->listener_param_);
}

void R1DoubleClicked(void *param) {
  Button *btn = static_cast<Button *>(param);
  CrazyLog::d(btn->kTag, "R1DoubleClicked");
  if (btn->listener_)
    btn->listener_(ButtonID::R1, ButtonState::DoubuleClick,
                   btn->listener_param_);
}

void R1LongPress(void *param) {
  Button *btn = static_cast<Button *>(param);
  CrazyLog::d(btn->kTag, "R1LongPress");
  if (btn->listener_)
    btn->listener_(ButtonID::R1, ButtonState::LongPress, btn->listener_param_);
}

void Button::AttachClickListener(ButtonID id) {
  if (id == ButtonID::S1) {
    Init(ButtonID::S1);
    s1_->attachClick(S1Clicked, this);
  } else if (id == ButtonID::L1) {
    Init(ButtonID::L1);
    l1_->attachClick(L1Clicked, this);
  } else if (id == ButtonID::R1) {
    Init(ButtonID::R1);
    r1_->attachClick(R1Clicked, this);
  }
}

void Button::AttachDoubleClickListener(ButtonID id) {
  if (id == ButtonID::S1) {
    Init(ButtonID::S1);
    s1_->attachDoubleClick(S1DoubleClicked, this);
  } else if (id == ButtonID::L1) {
    Init(ButtonID::L1);
    l1_->attachDoubleClick(L1DoubleClicked, this);
  } else if (id == ButtonID::R1) {
    Init(ButtonID::R1);
    r1_->attachDoubleClick(R1DoubleClicked, this);
  }
}

void Button::AttachLongPressListener(ButtonID id) {
  if (id == ButtonID::S1) {
    Init(ButtonID::S1);
    s1_->attachLongPressStart(S1LongPress, this);
  } else if (id == ButtonID::L1) {
    Init(ButtonID::L1);
    l1_->attachLongPressStart(L1LongPress, this);
  } else if (id == ButtonID::R1) {
    Init(ButtonID::R1);
    r1_->attachLongPressStart(R1LongPress, this);
  }
}

void Button::Release(ButtonID id) {
  if (id == ButtonID::S1){
    if (s1_){
      delete (s1_);
      s1_ = nullptr;
    }
  }
  else if (id == ButtonID::L1){
    if (l1_){
      delete (l1_);
      l1_ = nullptr;
    }
  }
  else if (id == ButtonID::R1){
    if (r1_) {
      delete (r1_);
      r1_ = nullptr;
    }
  }
}

void Button::SetClickTicks(int ticks){
  click_ticks_ = ticks;
  if (s1_) s1_->setClickTicks(click_ticks_);
  if (l1_) l1_->setClickTicks(click_ticks_);
  if (r1_) r1_->setClickTicks(click_ticks_);
}