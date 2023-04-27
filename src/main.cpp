#include <Arduino.h>

#include "keychain/kc_os_mode.h"
#include "os/app_os.h"
#include "outlander/codelab_os.h"

std::shared_ptr<OS> os;

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println("Hello CrazyCube~~");

  byte mode = OSModeKeyChain().os_mode();  // Normal
  // mode = OS_MODE_APPOS;                //Always APPOS
  // mode = OS_MODE_CODELAB;              //Always CODELAB

  if (mode == OS_MODE_CODELAB)
    os = std::make_shared<CodelabOS>();
  else
    os = std::make_shared<AppOS>();

  // revert to os
  if (mode != OS_MODE_APPOS) OSModeKeyChain().UpdateRunMode(OS_MODE_APPOS);

  os->Init();
}

void loop() { os->Routine(); }