/**
 * @file bilibili_api.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief bilibili Api
 * @version 1.0
 * @date 2022-09-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include <WString.h>
#include "framework/context/network_context.h"

#define FANS_API "https://api.bilibili.com/x/relation/stat?vmid="

class BilibiliApiN: public NetworkContext<BilibiliApiN>
{
private:
  const char * kTag = "BilibiliApiN";
  
public:
  int32_t GetFansData(String vmid);
};

