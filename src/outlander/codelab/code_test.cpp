#include "code_test.h"

#include "app/assistant/assistant_speech/nlp/intent_processor.h"
#include "app/assistant/assistant_speech/nlp/intent_session.h"
#include "keychain/kc_assistant.h"

void CodeTest::Test_Audio() {
  CrazyLog::d(kTag, "Test_Audio");

  frame.speaker().SetVolume(12);
  frame.speaker().PlayFile("/audio/message.mp3");
}

void CodeTest::Test_MPU() {
  CrazyLog::d(kTag, "Test_MPU");
  frame.imu().Reset();
  EularAngle angle;
  for (int i = 0; i < 10; i++) {
    frame.imu().Update(100, &angle, true);
    String tips = " yaw:" + String(angle.yaw);
    tips += "\n pitch: " + String(angle.pitch);
    tips += "\n roll: " + String(angle.roll);
    CrazyLog::d(kTag, tips.c_str());
    delay(300);
  }
  CrazyLog::d(kTag, "TestInitMPU Done");
}

bool CodeTest::Test_Connect_Wifi(String ssid,String passwd){
  CrazyLog::d(kTag, "Test_Connect_Wifi");
   bool result = frame.network().Connect(ssid, passwd, 5000);
  if(!result)   CrazyLog::e(kTag, "connect wifi failed!!!!!!!");
   return result;
}

void CodeTest::Test_OpenAI_CreateChatMessagesForGPT35(){

}