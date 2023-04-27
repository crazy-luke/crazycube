#include "token_store.h"

#include "tools/crazy_log.h"
#include "framework/framework.h"
#include "tools/timer_helper.h"
#include "keychain/kc_assistant.h"

bool TokenStore::CheckExpired(){
  if(baidu_token_.isEmpty()){
    CrazyLog::d(kTag,"Token is empty");
    return true;
  }

  if(millis() - last_reflash_time_ > kTokenExpiresTime){
    CrazyLog::d(kTag,"Token is expired");
    baidu_token_ = "";  //过期
    return true;
  }
  return false;
}

String TokenStore::baidu_token() {
  return baidu_token_;
}

String TokenStore::GetBaiduToken(bool auto_reflash)
{
  if(CheckExpired() && auto_reflash)
    ReflashBaiduToken();
  return baidu_token();
}

bool TokenStore::ReflashBaiduToken() {
  CrazyLog::d(kTag, "ReflashBaiduToken");
  auto info = AssistantChain().Read();
  String client_id = info.asst_id;
  String client_secret = info.asst_secret;
  if(client_id.isEmpty() || client_secret.isEmpty()){
    CrazyLog::w(kTag, "assistant info is empty");
    return false;
  }

  // String client_id = "Lpk5tcaijoQXoLuf6WeAROip";
  // String client_secret = "bV6CTDZL9ZQYKkQYyy0hHYqYG3NZMqTf";
  // String url =
  // "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=Lpk5tcaijoQXoLuf6WeAROip&client_secret=bV6CTDZL9ZQYKkQYyy0hHYqYG3NZMqTf";
  String url =  "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=" + client_id + "&client_secret=" + client_secret;
  auto result = network().HttpGetRequestJson(url);
  if (result.success) {
    const char * access_token = result.data["access_token"];
    const unsigned long expires_in = result.data["expires_in"];

    baidu_token_ = (access_token ? String(access_token) : "");
  //  baidu_expires_in_ = expires_in;
    last_reflash_time_ = millis();

  #if CRAZY_LOG_YELL  // save memory
    CrazyLog::d(kTag, "ReflashToken BaiduToken : %s, expires_in: %ld",
                baidu_token_.c_str(), baidu_expires_in_);
  #endif


    return true;
  }
  return false;
}
