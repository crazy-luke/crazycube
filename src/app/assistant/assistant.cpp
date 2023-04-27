#include "assistant.h"

#include "gui/gui.h"
#include "tools/crazy_log.h"

#define AssistantMaxPageIdx 2

Assistant::~Assistant() {
  CrazyLog::d(kTag, "~release");
  if (assistant_detect_ptr_) {
    assistant_detect_ptr_->Stop();
    delete (assistant_detect_ptr_);
  }
}

void OnAssistantDetectListener(String text, void* param) {
  Assistant* app = static_cast<Assistant*>(param);
  CrazyLog::d(app->kTag, "OnAssistantDetectListener");
  app->context()->CallAssistant();
}

void Assistant::OnLaunch() {
  CrazyLog::d(kTag, "OnLaunch");
  // CrazyLog::set_level(LogLevel::INFO);

  lv_obj_t* ui_screen = ui_init_crazy_asst();
  UpdateContext(0);
  UpdateHint(0);
  lv_scr_load_anim(ui_screen, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 300, 0, false);

  assistant_detect_ptr_ = new AssistantDetect(context()->frame().mic());
  assistant_detect_ptr_->SetListener(OnAssistantDetectListener, this);
  assistant_detect_ptr_->Start(400);

  
}

void Assistant::OnExitApp() {
  // CrazyLog::set_level(LogLevel::DEBUG);
  CrazyLog::d(kTag, "OnExitApp");
  lv_scr_load_anim(context()->home_screen(), LV_SCR_LOAD_ANIM_MOVE_TOP, 300, 0,
                   true);
}

void Assistant::OnAction(AppAction action) {
  if (action == AppAction::ACT) {
    CrazyLog::d(kTag, "ACT");
    context()->CallAssistant();
  } else if (action == AppAction::LEFT)
    TogglePage(false);
  else if (action == AppAction::RIGHT)
    TogglePage(true);
}

void Assistant::OnAssistantState(bool on) {
  CrazyLog::d(kTag, "OnAssistantState");
  if (!on && assistant_detect_ptr_) assistant_detect_ptr_->Start();
}

void Assistant::TogglePage(bool next) {
  CrazyLog::d(kTag, "TogglePage: next:%d", next);

  // idx
  int8_t page_idx = next ? page_idx_ + 1 : page_idx_ - 1;
  if (page_idx > AssistantMaxPageIdx) page_idx = 0;
  if (page_idx < 0) page_idx = AssistantMaxPageIdx;

  UpdateContext(page_idx);
  UpdateHint(page_idx);
  page_idx_ = page_idx;
}

bool Assistant::OnAssistantSpecs(SpeechLanguage& language,
                              uint16_t& speech_max_time,
                              SessionType& type) {
  if (page_idx_ == 0) {
    language = SpeechLanguage::MANDARIN;
    speech_max_time = SpeechTimeShort;
    type = SessionType::UNKNOWN;
    return true;
  }

  if (page_idx_ == 1) {
    language = SpeechLanguage::MANDARIN;
    speech_max_time = SpeechTimeLong;
    type = SessionType::SERISE_OPENAI;
    return true;
  }

  if (page_idx_ == 2) {
    language = SpeechLanguage::ENGLISH;
    speech_max_time = SpeechTimeLong;
    type = SessionType::SERISE_OPENAI;
    return true;
  }

  return false;
}

void Assistant::UpdateHint(int8_t idx) {
  String hint = String(idx + 1) + "/" + String(AssistantMaxPageIdx + 1) + " >>";
  ui_update_hint_crazy_asst(hint.c_str());
}

void Assistant::UpdateContext(int8_t idx) {
  // update ui
  String title = "";
  String desc = "";

  if (idx == 0) {
    title = "单句对话";
    desc = "1.长按背后系统按钮\n";
    desc += "2.顺时针手势\n";
    desc += "3.语音 Marvin\n";
    desc += "\n注: 方法2、3 仅在当前 APP 有效";
  } else if (idx == 1) {
    title = "持续对话";
    desc = "1.单句语音时长 " + String(SpeechTimeLong / 1000) + " 秒\n";
    desc += "2.录音时 顺时针 手势提前结束录音\n";
    desc += "\n当前为中文会话模式";
  } else if (idx == 2) {
    title = "Conversation";
    desc = "1.单句语音时长 " + String(SpeechTimeLong / 1000) + " 秒\n";
    desc += "2.录音时 顺时针 手势提前结束录音\n";
    desc += "\n当前为英语会话模式";
  }
  ui_update_content_crazy_asst(title.c_str(), desc.c_str());
}