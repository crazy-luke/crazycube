#include "bilibili_api_n.h"

#include "tools/crazy_log.h"

int32_t BilibiliApiN::GetFansData(String vmid) {
  CrazyLog::d(kTag, "GetFansData");

  String url = FANS_API + vmid;
  auto result = network().HttpGetRequest(url);

  PSRamJsonDocument doc(result.data.length() * 2);
  if(!result.success || deserializeJson(doc, result.data)){ 
    //http or deserializeJson failed
    CrazyLog::e(kTag, "GetFansData failed, code:%d", result.code);
    return -1;
  }
  int32_t fans = doc["data"]["follower"];
  CrazyLog::d(kTag, "fans: %d", fans);
  return fans;
}