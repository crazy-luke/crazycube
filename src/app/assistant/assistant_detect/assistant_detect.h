
#pragma once

#include "framework/system/mic/mic.h"
#include "audio_detect/detect_word.h"

using DetectListener = void (*)(String text, void *);

class AssistantDetect
{
private:
  const char *kTag = "AssistantDetect";
   Mic &mic_;
   TaskHandle_t task_handle_ = nullptr;
   DetectWord * detect_word_;
   uint16_t init_task_delay_ = 0;

   DetectListener listener_;
   void *listener_param_ = NULL;

private:
  void OnDetectResult(String text);

public:
    AssistantDetect(Mic &mic);
    ~AssistantDetect();
    void SetListener(DetectListener listener, void *param);

public:
   void Start(uint16_t delay = 0);
   void Stop();

private:
  friend void AssistantDetectTask(void *param);   
  void DoAssistantDetectTask();
};

