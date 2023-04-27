
#include "lab.h"

void LabOnButtonListener(ButtonID id, ButtonState state, void *param) {
  Lab *os = static_cast<Lab *>(param);
  CrazyLog::ram(os->kTag);
  os->OnButtonListener(id, state);
}

void Lab::Init() {
  CrazyLog::d(kTag, "Init");

  if (!SPIFFS.begin()) CrazyLog::e(kTag, "SPIFFS initialisation failed!");

  frame().btn().SetListener(LabOnButtonListener, this);
  frame().btn().AttachClickListener(ButtonID::L1);
  frame().btn().AttachDoubleClickListener(ButtonID::L1);

  frame().btn().AttachLongPressListener(ButtonID::L1);
  frame().btn().AttachClickListener(ButtonID::R1);
  frame().btn().AttachDoubleClickListener(ButtonID::R1);
  frame().btn().AttachLongPressListener(ButtonID::R1);

  test_ = std::make_unique<CodeTest>(frame());
}

void Lab::Routine() {
  frame().btn().Routine();
  delay(10);
}

void Lab::OnButtonListener(ButtonID id, ButtonState state) {
  CrazyLog::d(kTag, "OnButtonListener");

  // click l1
  if (id == ButtonID::L1 && state == ButtonState::Click) {
    //Test dependy on network
    ConnectWifi(); 
    test_->Test_OpenAI_CreateChatMessagesForGPT35();
  }
  // double l1
  else if (id == ButtonID::L1 && state == ButtonState::DoubuleClick) {
    
  }
  // longpress l1
  else if (id == ButtonID::L1 && state == ButtonState::LongPress) {

  }
  // click l2
  else if (id == ButtonID::R1 && state == ButtonState::Click) {
    // Test Hardware
    // test_->Test_Audio();
    test_->Test_MPU();
  }
  // double l2
  else if (id == ButtonID::R1 && state == ButtonState::DoubuleClick) {
  }
  // longpress l2
  else if (id == ButtonID::R1 && state == ButtonState::LongPress) {
    CrazyLog::d(kTag, "ESP.restart()");
    ESP.restart();
  }
}

Frame &Lab::frame() { return Frame::instance(); }


bool Lab::ConnectWifi(){
    String ssid = "";
    String passwd = "";
    ssid = "";
    passwd = "";
    return test_->Test_Connect_Wifi(ssid, passwd);
}