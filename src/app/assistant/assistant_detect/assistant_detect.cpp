#include "assistant_detect.h"

#include "audio_detect/tflite_adapter/model/tf_model_loader.h"

#define NOTIFY_ID_ASST_START 12

void AssistantDetectTask(void *param) {
  AssistantDetect *assistant = static_cast<AssistantDetect *>(param);
  if(assistant->init_task_delay_>0) {
    vTaskDelay(assistant->init_task_delay_);
    assistant->init_task_delay_ = 0;
  }
  assistant->DoAssistantDetectTask();
  assistant->task_handle_ = NULL;
  vTaskDelete(NULL);
}

AssistantDetect::AssistantDetect(Mic &mic) : mic_(mic) {}

AssistantDetect::~AssistantDetect() { 
  CrazyLog::d(kTag, "~release");
  Stop(); 
}

void AssistantDetect::Start(uint16_t delay) {
  CrazyLog::d(kTag, "StartTask");

  if (task_handle_ != nullptr) {
    xTaskNotify(task_handle_, NOTIFY_ID_ASST_START, eSetBits);
    return;
  }
  init_task_delay_ = delay;
  // 初始化任务
  xTaskCreatePinnedToCore(AssistantDetectTask, "AssistantDetectTask", 1024 * 6, this,
                          TASK_PRIORITY_ASSISTANT, &task_handle_, CORE_0);
  xTaskNotify(task_handle_, NOTIFY_ID_ASST_START, eSetBits);
}

void AssistantDetect::Stop() {
  CrazyLog::d(kTag, "Stop");
  mic_.Stop();

  if (task_handle_ != nullptr) {
    vTaskDelete(task_handle_);
    task_handle_ = nullptr;
  }

  if (detect_word_ != nullptr) {
    delete (detect_word_);
  }
}

void AssistantDetect::OnDetectResult(String text) {
  CrazyLog::d(kTag, "OnDetectResult");
   mic_.Suspend(task_handle_);
   if(listener_ != nullptr) listener_("marvin", listener_param_);
}

void AssistantDetect::SetListener(DetectListener listener, void *param) {
  listener_ = listener;
  listener_param_ = param;
}

void AssistantDetect::DoAssistantDetectTask() {
  CrazyLog::d(kTag, "DoAssistantDetectTask");
  auto model = TFModelLoader().GetWakeupModel();  //will be free DetectWord release
  detect_word_ = new DetectWord(mic_.sampler(), model);

  uint32_t ulNotificationValue;
  
  while (true) {
    CrazyLog::d(kTag, "DetectProcess1: waiting for start signal");
    ulNotificationValue = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    
    if (ulNotificationValue != NOTIFY_ID_ASST_START) {
      CrazyLog::d(kTag, "DetectProcess1: ignore signal %d",ulNotificationValue);
      continue;
    }

    CrazyLog::d(kTag, "DetectProcess1: do Detect Process");

    detect_word_->Enter();
    mic_.Start(task_handle_);
    String msg;
    while (true) {
      //1. waiting audio sampler signal
      ulNotificationValue = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

      //2. receive not sampler signal
      if(ulNotificationValue != NOTIFY_ID_STATE_I2S_SAMPLER) {
        CrazyLog::d(kTag, "DetectProcess2: ignore signal %d",ulNotificationValue);
        continue;
      }

      //3. receive sampler signal
      if (detect_word_->Run(msg)) {
        detect_word_->Exit();
        OnDetectResult(msg);
        break;
      }
      delay(10); //breath
    }
  }
}