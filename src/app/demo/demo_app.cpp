#include "demo_app.h"

#include "tools/crazy_log.h"
#include "framework/framework.h"

void DemoApp::OnLaunch() {
  CrazyLog::d(kTag, "onLaunch");
  context()->frame().display().ShowTipsDisplay("Just a Demo");
  context()->frame().display().ShowSubTipsDisplay("逆时针 退出APP");
}

void DemoApp::OnExitApp() { 
  context()->frame().display().CleanTips();
  CrazyLog::d(kTag, "onExitApp");
}
