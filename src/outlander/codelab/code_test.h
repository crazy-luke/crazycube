

#pragma once

#include "framework/framework.h"

class CodeTest
{
private:
  const char* kTag = "CodeTest";
  Frame& frame;

public:
   CodeTest(Frame& f): frame(f){}

  bool Test_Connect_Wifi(String ssid,String passwd);
  void Test_Audio();
  void Test_MPU();

  void Test_OpenAI_CreateChatMessagesForGPT35();

 
};
