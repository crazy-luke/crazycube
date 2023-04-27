/**
 * @file network.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief 网络
 * @version 1.0
 * @date 2022-07-27
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>

#include "tools/psram_allocator.h"

// CrazyAdam:  Warning! !!
// 警告，开启此功能可能导致死锁，开启后不要暂停或杀死网络访问线程，此功能将并发任务改为串行任务以节约内存峰值开销。
// NETWORK_WITH_LOCK may cause deadlock,  never stop or pause thread which use
// Network with NETWORK_WITH_LOCK  each request will wait until pre-request finished. 
// Do not open this unless RAM is too small 

#define NETWORK_WITH_LOCK
#ifdef NETWORK_WITH_LOCK
#include <mutex>
#endif

//RAM 低于伐值预警
#define NETWORK_MEM_WARNNING 68000
// #define NETWORK_MEM_WARNNING 120000

#define NETWORK_CONNECT_TIMEOUT 6000
#define NETWORK_READ_TIMEOUT 10000

#define NETWORK_RETRY_TIME_MAX_LIMIT 3

struct HttpStringResult {
  bool success;
  int code;
  String data;
};

struct HttpJsonResult {
  bool success;
  int code;
  PSRamJsonDocument data;
};

class Network {
 private:
  const char* kTag = "Network";
  const IPAddress kIP = IPAddress(192, 168, 0, 1);
  const IPAddress kNetmask = IPAddress(255, 255, 255, 0);

#ifdef NETWORK_WITH_LOCK
  std::mutex lock_task_;
#endif


 public:
  bool Connect(String ssid, String password, uint16_t timeout);
  bool WifiAP();

  bool IsConnected();
  HttpStringResult HttpGetRequest(String url, uint8_t retry_times);
  HttpStringResult HttpGetRequest(String url);
  HttpJsonResult HttpGetRequestJson(String url);
  HttpStringResult HttpPostRequest(String url, String json_body,String auth, uint16_t timeout, uint8_t retry_times);
  HttpStringResult HttpPostRequest(String url, String json_body,String auth, uint16_t timeout = NETWORK_READ_TIMEOUT);
  bool DownloadAndSaveFile(String filePath, String url);
  int8_t SignalStrength();
};