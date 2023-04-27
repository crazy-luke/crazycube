#include "group_app.h"

#include "tools/crazy_log.h"

void GroupAPP::OnLaunch() {
  CrazyLog::d(kTag, "OnExitOnLaunchApp");
  if(group_id_.isEmpty()){
   String tips = "\n放入收纳盒方法\n\n";
   tips +="1.打开 系统设置\n";
   tips +="2.Web 高级设置";
   context()->frame().display().ShowTipsDisplay(tips);
  }else{
    context()->OnGroup(group_id_);
  }
}

void GroupAPP::OnExitApp() { 
  context()->frame().display().CleanTips();
  CrazyLog::d(kTag, "onExitApp");
}