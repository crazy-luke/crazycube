#include "codelab_os.h"

#include "tools/crazy_log.h"

CodelabOS::CodelabOS(/* args */)
{
  CrazyLog::d(kTag, "constructor!"); 
}

CodelabOS::~CodelabOS()
{
   CrazyLog::d(kTag, "~release");
}

void CodelabOS::Init() {
  CrazyLog::d(kTag,"DoCodeLabInit");
  lab_.Init();
}

void CodelabOS::Routine() { 
  lab_.Routine(); 
}