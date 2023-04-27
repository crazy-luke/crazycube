/**
 * @file web_server.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief Setup CrazyCube via Browse
 * @version 1.0
 * @date 2022-08-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <WiFi.h>

#include "../app_contract.h"
#include "data/web_api.h"

class WebServer : public APP {

private:
  const char * kTag =  "WebServer";
  String ssid_;
  AsyncWebServer server_ = AsyncWebServer(80);
  const IPAddress kIP = IPAddress(192, 168, 0, 1);
  const IPAddress kNetmask = IPAddress(255, 255, 255, 0);
  WebApi webapi_;

 private:
  bool InitWifi();
  bool InitWebServer();
  void ShowManual();
  
  void DoGetFileList(AsyncWebServerRequest *request, WebFileType type);
  void DoDeleteFile(AsyncWebServerRequest *request, WebFileType type);

 public:
  ~WebServer();
  void OnLaunch() override;
  void OnExitApp() override;
  void OnAction(AppAction action) override;

private:
  void RegisterRouteSys();
  void RegisterRouteApp();
};
