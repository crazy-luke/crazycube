#include "app_os.h"

#include <esp_task_wdt.h>

#include "tools/file_manager.h"
#include "tools/crazy_log.h"
#include "framework/framework.h"
#include "keychain/kc_device.h"
#include "keychain/kc_os_mode.h"
#include "keychain/kc_state.h"
#include "lv/lv_helper.h"
#include "tools/mutex_helper.h"
#include "app/assistant/assistant_speech/assistant_specs.h"
#include "volume/volume_bar.h"

 //Do some thing background after OS inited
void OSInitedTask(void* param){  
  //clear cache file
  FileManager().DeleteFolderFiles(FILEPATH_ROOT_CACHE);
  vTaskDelete(NULL); 
}

 void AppOS::ReloadAppList(std::vector<AppShell*> apps, String position_app_id, bool is_group_app){
    CrazyLog::d(kTag, "ReloadAppList");
    if(apps.size()<=0)  {
      CrazyLog::e(kTag, "apps is empty");
      return;
    }
    //init data
    active_app_idx_ =0;
    //clean app_sheels_ before reload
    AppList().Clean(app_sheels_); 
    for (auto app : apps) {
      app_sheels_.push_back(app);
    }

    active_app_idx_ = FindAppIndex(app_sheels_, position_app_id);
    CrazyLog::d(kTag,"app_sheels total:%d, active_app_idx:%d",app_sheels_.size(), active_app_idx_);
    launchpad_.ReloadActiveAPP(app_sheels_[active_app_idx_]->app_img(),
                               app_sheels_[active_app_idx_]->app_name());
    launchpad_.SetSubMode(is_group_app);
    running_app_ptr_.reset();
 }

void AppOS::Init() {
  CrazyLog::d(kTag, "Init");
  // don't get killed for long running tasks
  esp_task_wdt_init(15, false); 

  auto state = StateKeyChain().Read();
  frame().display().Init(state.brightness);
  frame().speaker().SetVolume(state.volume);
  frame().mic().Init();
  frame().gesture().Init(700);

  // Init Button
  InitButton();

  if (!SPIFFS.begin()) 
    CrazyLog::e(kTag, "SPIFFS initialisation failed!"); 
  lv_png_init();

  // Init luanchpad apps
  launchpad_.Init();
  ReloadAppList(AppList().RootAPP(true), OSModeKeyChain().app_id(), false);

  //init syspad
  syspad_.Init();
  syspad_.set_context(shared_from_this());
  NetworkMonitor(true);

  //init led
  auto device = DeviceKeyChain().Read();
  allow_lock_gesture_ = device.lock_gesutre;
  frame().led().Init(state.ledlight,device.color_r, device.color_g, device.color_b);
  frame().ResotreLedStateWithStore();

  //play ready audio
  frame().speaker().PlayFile(AUDIO_RES_MESSAGE);
  CrazyLog::d(kTag, "AppOS Ready");
  
  //assistant
  asst_speech_.set_context(shared_from_this());

  //controller_ex
  if(CONTROLLER_EX_DEBUG) {
    controller_ex_ptr_ = new ControllerEx();
    controller_ex_ptr_->set_context(shared_from_this());
  }
  
  //launch a background task
  xTaskCreatePinnedToCore(OSInitedTask, "OSInitedTask", 1024 * 4, NULL,
                          TASK_PRIORITY_APP, NULL, CORE_0);
}

void AppOS::Routine() {
#if CRAZY_LOG_YELL
  CrazyLog::v(kTag, "Routine");
#endif
  MutexUI::instance().Lock();
  frame().display().Routine();
  MutexUI::instance().Unlock();

  // Gesture
  if (frame().gesture().IsDataReady()) {
#ifdef AUTO_SCROLL
    if (millis() - show_ts_ > 2000) {
      OnAction(GestureAction::LEFT);
      show_ts_ = millis();
    }
#endif
    auto action = frame().gesture().GetAction();
  //  if (running_app_ptr_ == nullptr && !gesture_helper_.ActionFilter(action))
    if (gesture_helper_.ActionFilter(action)) OnAction(action);
    else CrazyLog::d(kTag, "gesture_gard!");
  }

  //Button 
  frame().btn().Routine();

  //APP
  if (running_app_ptr_ != nullptr) {
    running_app_ptr_->OnRoutine();
  }

  if(controller_ex_ptr_) controller_ex_ptr_->Routine();
}

void AppOS::LaunchAPP(uint8_t idx) {
  if (idx < 0 || idx >= app_sheels_.size()) {
    CrazyLog::w(kTag, "LaunchAPP idx error");
    return;
  }
  CrazyLog::d(kTag, "LaunchAPP idx:%d", idx);
  auto app_shell = app_sheels_[idx];
  APP *app = app_shell->CreateApp();
  running_app_ptr_.reset(app);
  app->set_context(shared_from_this());

  //保存最近一次运行的 APP.  save state
  if(!launchpad_.is_sub_mode()) 
    OSModeKeyChain().UpdateAppId(app_shell->app_id());
  CrazyLog::ram(app_shell->app_name());
  app->OnLaunch(); 
}

uint8_t AppOS::FindAppIndex(std::vector<AppShell*> & apps, String app_id) {
  if(app_id.isEmpty()) return 0;
  uint8_t idx = 0;
  for (uint8_t i = 0; i < apps.size(); i++) {
    if (apps[i]->app_id() == app_id) {
      CrazyLog::d(kTag, "FindAppIndex app_id: %s, idx:%d", app_id.c_str(), i);
      idx = i;
      break;
    }
  }
  return idx;
}

void AppOS::SwitchAPP(bool forward) {
  uint8_t size = app_sheels_.size();
  if (size <= 0) {
    CrazyLog::w(kTag, "NO APP!");
    return;
  }
  uint8_t idx = active_app_idx_;

  if (forward) {
    if (idx >= size - 1) {
      idx = 0;
    } else {
      idx++;
    }
  } else {
    if (idx == 0) {
      idx = size - 1;
      ;
    } else {
      idx--;
    }
  }

  AppShell *app_shell = app_sheels_[idx];
  CrazyLog::d(kTag, "SwitchAPP idx:%d, isForward:%d, AppName: %s", idx, forward,
              app_shell->app_name());

  frame().speaker().PlayFile(AUDIO_RES_SWITCH);
  launchpad_.SwitchAPP(forward, app_shell->app_img(), app_shell->app_name());
  active_app_idx_ = idx;
}

void AppOS::OnAction(GestureAction action) {
  if (action == GestureAction::NONE) return;
  CrazyLog::w("Gesture", "action %d", action);

  // close assistant
  if (asst_speech_.IsForegroundWorking()) {
    CrazyLog::d(kTag, "Setp: assistant IsForegroundWorking");
    if (action == GestureAction::DOWN || action == GestureAction::ANTICLOCKWISE) {
       CrazyLog::d(kTag, "Close Assistant by gesture:%d",action);
      asst_speech_.OnExit();
    }else if(action == GestureAction::CLOCKWISE) {
      asst_speech_.DoSpeechResultByAction();
    }
    return;
  }

  // lock screen && keyboard
  if (action == GestureAction::FORWARD) {
    CrazyLog::d(kTag, "Setp: LockScreen");
    syspad_.is_locked() ? UnLockScreen() : LockScreen();
    return;
  }

  if (syspad_.is_locked()) {
    if (keyboard_ptr_ != nullptr && keyboard_ptr_->isConnected()) {
      CrazyLog::d(kTag, "Setp: Send Keyboard");
      syspad_.KeyboardHint();
      keyboard_ptr_->OnAction(action);
    } else {
      CrazyLog::d(kTag, "Setp: Sorry, Screen is locked");
      syspad_.LockHint();
    }
    return;
  }

  // syspad
  // close or open syspad with GestureAction::WAVE
  if (syspad_.full_syspad()) {
    CrazyLog::d(kTag, "Setp: syspad");
    if (action == GestureAction::WAVE || action == GestureAction::UP) {
      CloseFullSyspad();
      return;
    }
    auto result = gesture_helper_.ConvertSysbarAction(action);
    if (result.success) {
      syspad_.OnAction(result.action);
    }
    return;
  }

  if (action == GestureAction::WAVE) {
    CrazyLog::d(kTag, "Setp: syspad");
    OpenFullSyspad();
    return;
  }

  // APP is running
  if (running_app_ptr_ != nullptr) {
    auto result = gesture_helper_.ConvertAppAction(action);
    if (result.success) {
      CrazyLog::d(kTag, "Setp: APP OnAction");
      running_app_ptr_->OnAction(result.action);
      return;
    }
  }

  // Exit App
  if (action == GestureAction::ANTICLOCKWISE ) {
    if(running_app_ptr_ != nullptr) {
       CloseAPP();
       return;
    }else  if(launchpad_.is_sub_mode()) {
      ReloadAppList(AppList().RootAPP(true), OSModeKeyChain().app_id(), false);
      return;
    }
  }

  // During anim 动画过程中不响应
  if (lv_anim_count_running() && (!asst_speech_.IsForegroundWorking())) {
    CrazyLog::d(kTag, "Setp: No need to rush!");
    return;
  }

  // launchpad
  if (action == GestureAction::LEFT) {
    CrazyLog::d(kTag, "Setp: switch APP left");
    SwitchAPP(true);
  } else if (action == GestureAction::RIGHT) {
    CrazyLog::d(kTag, "Setp: switch APP right");
    SwitchAPP(false);
  } else if (action == GestureAction::CLOCKWISE) {
    CrazyLog::d(kTag, "Setp: Launch APP");
    LaunchAPP(active_app_idx_);
  }
}

void AppOS::OpenFullSyspad() {
  CrazyLog::d(kTag, "OpenFullSyspad");

  syspad_.OnLaunchFullSyspad();
  if (running_app_ptr_ != nullptr) {
    syspad_.SetManual(app_sheels_[active_app_idx_]->app_name(),
                      app_sheels_[active_app_idx_]->app_manul().c_str());
  } else {
    String title = "手势操作说明";
    String content = "向左、右 : 切换APP\n";
    content += "顺、逆时针 : 进出APP\n";
    content += "向前 : 锁屏或解锁\n";
    content += "挥手 : 开关状态栏";
    syspad_.SetManual(title.c_str(), content.c_str());
  }

  if (running_app_ptr_ != nullptr) {
    if (!running_app_ptr_->OnSyspadState(true)) {
      CloseFullSyspad();  // app not compatible
    }
  }
}

void AppOS::CloseFullSyspad() {
  CrazyLog::d(kTag, "CloseFullSyspad");
  syspad_.OnExitFullSyspad();
  if (running_app_ptr_ != nullptr) {
    running_app_ptr_->OnSyspadState(false);
  }
}

void AppOS::CloseAPP(){
  CrazyLog::d(kTag, "Exit App");
  if(running_app_ptr_ != nullptr){
    running_app_ptr_->OnExitApp();
    running_app_ptr_.reset();
  }
  
  UpdateUIAssistantState();
  
  CrazyLog::ram("closeapp");
}

//------------------ ContextAPP ------------------

lv_obj_t *AppOS::home_screen() { return launchpad_.launchpad_screen(); }


void AppOS::NetworkMonitor(bool enable) {
  if (enable)
    syspad_.StartNetworkMonitor();
  else
    syspad_.StopNetworkMonitor();
}

bool AppOS::CallAssistant() {
  CrazyLog::d(kTag, "CallAssistant");
  
  SpeechLanguage speech_language = SpeechLanguage::MANDARIN;
  uint16_t speech_max_time = SpeechTimeShort;
  SessionType session_type = SessionType::UNKNOWN;
  if (running_app_ptr_ != nullptr){
     if(auto p = std::dynamic_pointer_cast<AssistantSpecs>(running_app_ptr_)) {
        CrazyLog::d(kTag,"OnAssistantSpecs");
        SpeechLanguage speech_language_app;
        uint16_t speech_max_time_app;
        SessionType session_type_app;
        if(p->OnAssistantSpecs(speech_language_app, speech_max_time_app, session_type_app)){
          speech_language = speech_language_app;
          speech_max_time = speech_max_time_app;
          session_type = session_type_app;
        }
     }
  }
  auto result = asst_speech_.OnLaunch(speech_language, speech_max_time, session_type);
  if(result == AsstLaunchResult::SUCCESS){
    return true;
  }

  if(result == AsstLaunchResult::STOPPED || result == AsstLaunchResult::TOKEN_EXPIRED){
    asst_speech_.Start();
  }

  return false;
}

Frame& AppOS::frame() {
  return Frame::instance();
}

void AppOS::OnGroup(String group_id) {
  ReloadAppList(AppList().GroupAPP(group_id), OSModeKeyChain().app_id(),true);
}

bool AppOS::LockScreen() {
  CrazyLog::d(kTag, "LockScreen");

  if(!allow_lock_gesture_ && !syspad_.full_syspad()){
    CrazyLog::d(kTag, "not allow LockScreen, lock_gesture disable");
    return false;
  }

  if(!frame().display().lv_ui_enable()) { 
    //lock screen may cause confused
    CrazyLog::d(kTag, "not allow LockScreen, lv_ui_enable is false");
    return false;
  }

  if (syspad_.keyboard_allowed()) {
    if (keyboard_ptr_ == nullptr) {
      keyboard_ptr_.reset(new Keyboard());
    }
    keyboard_ptr_->Begin();
  } else if (keyboard_ptr_ != nullptr) {
    keyboard_ptr_.reset();
  }

  if (syspad_.full_syspad()) syspad_.OnExitFullSyspad();
  
  syspad_.LockScreen(true);
  return true;
}

bool AppOS::UnLockScreen() {
  CrazyLog::d(kTag, "UnLockScreen");
  syspad_.LockScreen(false);
  if (keyboard_ptr_ != nullptr) {
    keyboard_ptr_->End();
  }
  return true;
}

//------------------ ContextSyspad ------------------
void AppOS::OnNetworkStateChanged(bool on) {
  CrazyLog::d(kTag, "OnNetworkStateChanged: %d", on);
  if(on) asst_speech_.Start();
  UpdateUIAssistantState();
}

//------------------ ContextAssistant ------------------

void AppOS::OnAssistantState(bool on){
   CrazyLog::d(kTag, "OnAssistantState: %d", on);
   if (running_app_ptr_ != nullptr) running_app_ptr_->OnAssistantState(on);
}

void AppOS::OnAssistantReady(bool ready) {
  UpdateUIAssistantState();
}

void AppOS::UpdateUIAssistantState() {
  CrazyLog::d(kTag, "OnAssistantReady");
  bool on = false;

  //1. assistant ready
  if(asst_speech_.IsReady()) {
    if(running_app_ptr_== nullptr)
      on = true;
    else if(!app_sheels_[active_app_idx_]->asst_supress())
      on = true;
  }
  //2. network
  if(!frame().network().IsConnected())
    on = false;

  syspad_.ShowAssistant(on);
}


//------------------ ContextAssistant ------------------
void AppOS::OnActionEx(GestureAction action){
  CrazyLog::d(kTag, "OnActionEx");
  OnAction(action);
}

void AppOS::OnButtonListenerEx(ButtonID id, ButtonState state){
  CrazyLog::d(kTag, "OnButtonListenerEx");
  OnButtonListener(id,state);
}

//------------------ Button Action ------------------
void AppOS::OnButtonListener(ButtonID id, ButtonState state){
  CrazyLog::d(kTag,"OnButtonListener");

  //1. pre action: Unlock screen
  if(syspad_.is_locked()){    
    UnLockScreen(); 
  }
  //2. pre action: s1 exit assistant and syspad
  if(id == ButtonID::S1){ //S1 trigger
    if(asst_speech_.IsForegroundWorking()){   
      //1. exit assistant
      asst_speech_.OnExit();
      return;
    }else if(syspad_.full_syspad()){
      //2. exit syspad
      CloseFullSyspad();  
      return;
    }
  }

  //3. do app action
  if (running_app_ptr_ != nullptr) {
    bool do_default_action = running_app_ptr_->OnButton(id, state);
    if(!do_default_action)  return;
  }

  //4. do syspad action 
  if(syspad_.full_syspad()){
    OnButtonSyspad(id,state);
    return;
  }

  //5. do defalut action
  OnButtonDefault(id,state);
}

void AppOS::OnButtonSyspad(ButtonID& id, ButtonState& state){

    auto l1_action= [&](ButtonState state) -> void { 
      if(state == ButtonState::Click)    
        OnAction(GestureAction::LEFT);  
      else if(state == ButtonState::DoubuleClick)
        OnAction(GestureAction::LEFT);
      else if(state == ButtonState::LongPress)
        OnAction(GestureAction::ANTICLOCKWISE);  //Close Syspad action
    };

    auto r1_action= [&](ButtonState state) -> void { 
      if(state == ButtonState::Click)    
        OnAction(GestureAction::RIGHT);  
      else if(state == ButtonState::DoubuleClick)
        OnAction(GestureAction::RIGHT);  
      else if(state == ButtonState::LongPress)
        OnAction(GestureAction::CLOCKWISE);
    };

    if(id==ButtonID::L1) l1_action(state);
    else if(id == ButtonID::R1) r1_action(state);     
}

void AppOS::OnButtonDefault(ButtonID& id, ButtonState& state){

  auto s1_action = [&](ButtonState state) -> void { 
    if(state == ButtonState::Click){    
      //3. click switch led
      frame().SwitchLedStateWithStore();
    }else if(state == ButtonState::DoubuleClick){   
      //4. double-click call syspad
      OpenFullSyspad();
    }else if(state == ButtonState::LongPress){  
      //5. long press  call assistant
      CallAssistant();
    }
  };

  auto l1_action = [&](ButtonState state) -> void { 
    if(state == ButtonState::Click)    
      OnAction(GestureAction::LEFT);  
    else if(state == ButtonState::DoubuleClick){
      auto  volume = frame().TurnVolumeWithStore(false,2);
      VolumeBar().ShowVolumeBar(volume);
   }else if(state == ButtonState::LongPress)
      OnAction(GestureAction::ANTICLOCKWISE);
  };

  auto r1_action = [&](ButtonState state) -> void { 
    if(state == ButtonState::Click)    
      OnAction(GestureAction::RIGHT);  
    else if(state == ButtonState::DoubuleClick){
      auto  volume = frame().TurnVolumeWithStore(true,2);
      VolumeBar().ShowVolumeBar(volume);
   }else if(state == ButtonState::LongPress)
      OnAction(GestureAction::CLOCKWISE);
  };

  if(id == ButtonID::S1)  s1_action(state);
  else if(id==ButtonID::L1) l1_action(state);
  else if(id == ButtonID::R1) r1_action(state);
}

void AppOSOnButtonListener(ButtonID id, ButtonState state,void * param){
  AppOS *os = static_cast<AppOS*>(param);
  os->OnButtonListener(id, state);
}

void AppOS::InitButton(){
  //Support click、doubleclick、longpress
  frame().btn().SetListener(AppOSOnButtonListener, this);
  frame().btn().AttachClickListener(ButtonID::S1);
  frame().btn().AttachDoubleClickListener(ButtonID::S1);
  frame().btn().AttachLongPressListener(ButtonID::S1);
  frame().btn().AttachClickListener(ButtonID::L1);
  frame().btn().AttachDoubleClickListener(ButtonID::L1);
  frame().btn().AttachLongPressListener(ButtonID::L1);
  frame().btn().AttachClickListener(ButtonID::R1);
  frame().btn().AttachDoubleClickListener(ButtonID::R1);
  frame().btn().AttachLongPressListener(ButtonID::R1);
}
