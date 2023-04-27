/**
 * @file assistant.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief  Audio AssistantSpeech
 * @version 1.0
 * @date 2022-12-22
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "../app_contract.h"
#include "assistant_detect/assistant_detect.h"
#include "assistant_speech/assistant_specs.h"

class Assistant : public APP,
                  public AssistantSpecs {
 private:
  const char* kTag = "Assistant";
  AssistantDetect* assistant_detect_ptr_ =  nullptr;
  int8_t page_idx_ = 0;

  void UpdateHint(int8_t idx);
  void UpdateContext(int8_t idx);

 private:
  void TogglePage(bool next);

 public:
  ~Assistant();
  void OnLaunch();
  void OnExitApp();
  void OnAction(AppAction action);
  void OnAssistantState(bool on);

  private:
    friend void OnAssistantDetectListener(String text, void *param);

  public:
    bool OnAssistantSpecs(SpeechLanguage& language, uint16_t& speech_max_time, SessionType& type);
};
