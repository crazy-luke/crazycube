#include "app_contract.h"

#include "tools/crazy_log.h"

APP::~APP() { CrazyLog::d("APP", "released"); }

void APP::OnRoutine() {}

void APP::OnAction(AppAction action) {}

bool APP::OnButton(ButtonID id, ButtonState state) { return true;}

void APP::OnAssistantState(bool on){}

bool APP::OnSyspadState(bool on){  return true;}

const String AppShell::app_manul(){ return ""; }

const bool AppShell::asst_supress(){ return false; }

