#include "controller_ex.h"

#if CONTROLLER_EX_DEBUG
#include "outlander/simulator_os.h"
#endif

ControllerEx::ControllerEx(/* args */) { 
  CrazyLog::d(kTag, "constructor!"); 

  #if CONTROLLER_EX_DEBUG
    SimulatorOS::SimulatorBluepadInit();
  #endif
}

ControllerEx::~ControllerEx() { CrazyLog::d(kTag, "~release"); }


void ControllerEx::Routine() {
#if CONTROLLER_EX_DEBUG
  SimulatorOS::SimulatorBluepadRoutine();
  switch (SimulatorOS::SimulatorBluepadClick()) {
    case 0:
      break;
    case 1:
      context()->OnActionEx(GestureAction::UP);
      break;
    case 2:
      context()->OnActionEx(GestureAction::DOWN);
      break;
    case 3:
      context()->OnActionEx(GestureAction::LEFT);
      break;
    case 4:
      context()->OnActionEx(GestureAction::RIGHT);
      break;
    case 5:
      context()->OnActionEx(GestureAction::CLOCKWISE);
      break;  // INPUT_A
    case 6:
      context()->OnActionEx(GestureAction::ANTICLOCKWISE);
      break;  // INPUT_B
    case 7:
      context()->OnButtonListenerEx(ButtonID::S1, ButtonState::Click);
      break;  // INPUT_X
    case 8:
      context()->OnButtonListenerEx(ButtonID::L1, ButtonState::DoubuleClick);
      break;  // INPUT_Y
    case 9:
      context()->OnActionEx(GestureAction::WAVE);
      break;  // INPUT_START
    case 10:
      context()->OnActionEx(GestureAction::FORWARD);
      break;  // INPUT_SELECT
    case 11:
      context()->OnButtonListenerEx(ButtonID::S1, ButtonState::LongPress);  // INPUT_SYSTEM
  }
#endif
}
