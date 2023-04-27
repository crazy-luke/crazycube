#include "web_server.h"

#include <ArduinoJson.h>
#include <AsyncJson.h>

#include <cmath>

#include "framework/framework.h"
#include "keychain/keychain.h"
#include "tools/crazy_log.h"


String GetFilterParam(AsyncWebServerRequest *request, String name) {
  String value = request->arg(name);
  if (value.compareTo("undefined") == 0) value = "";
  value.trim();
  return value;
}


WebServer::~WebServer() { CrazyLog::d(kTag, "~release"); }

void WebServer::OnAction(AppAction action) { CrazyLog::d(kTag, "onAction"); }

void WebServer::OnLaunch() {
  CrazyLog::d(kTag, "onLaunch");
  context()->NetworkMonitor(false);
  InitWifi();
  InitWebServer();
  ShowManual();
}

void WebServer::OnExitApp() {
  CrazyLog::d(kTag, "onExitApp");
  context()->frame().RestartOS();
}

bool WebServer::InitWifi() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(kIP, kIP, kNetmask);
  ssid_ = "CrazyCube-" + WiFi.macAddress();
  bool result = WiFi.softAP(ssid_.c_str(), "", 1, 0, 4);
  if (!result) {
    CrazyLog::w(kTag, "WiFi failed");
  }
  return result;
}

bool WebServer::InitWebServer() {
  if (!SPIFFS.begin()) {
    CrazyLog::w(kTag, "initWebServer failed: SPIFFS!!!!");
    return false;
  }
  // home page
  server_.on("/", HTTP_GET, [&](AsyncWebServerRequest *request) {
    CrazyLog::i(kTag, "send html");
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server_.serveStatic("/crazycube.css", SPIFFS, "/crazycube.css");
  server_.serveStatic("/jquery.min.js", SPIFFS, "/jquery.min.js");
  server_.serveStatic("/crazycube.js", SPIFFS, "/crazycube.js");
  server_.serveStatic("/simpleUpload.min.js", SPIFFS, "/simpleUpload.min.js");
  server_.serveStatic("/loading.gif", SPIFFS, "/loading.gif");
  server_.serveStatic("/favicon.ico", SPIFFS, "/favicon.ico");

  RegisterRouteSys();
  RegisterRouteApp();
  server_.begin();
  return true;
}

void WebServer::ShowManual() {
  String manual = "";
  manual += "1.电脑或手机连接以下 Wifi:\n";
  manual += ssid_ + "\n\n";
  manual += "2.浏览器访问\n";
  manual += "http://" + kIP.toString();
  context()->frame().display().ShowTipsDisplay(manual);
}

void WebServer::RegisterRouteSys() {

  // 获取基础信息
  server_.on("/sys/infos", HTTP_GET, [&](AsyncWebServerRequest *request) {
    CrazyLog::d(kTag, "all info read");
    AsyncJsonResponse *response = new AsyncJsonResponse(false, 1024 * 4);
    JsonVariant &root = response->getRoot();

    auto wifi = root.createNestedObject("wifi");
    webapi_.GetWifiInfo(wifi);

    auto device = root.createNestedObject("device");
    webapi_.GetDeviceInfo(device);

    auto group_app = root.createNestedObject("group");
    webapi_.GetGroupAppInfo(group_app);

    auto assistant = root.createNestedObject("assistant");
    webapi_.GetAssistantInfo(assistant);

    auto desktop = root.createNestedObject("desktop");
    webapi_.GetDesktopInfo(desktop);

    auto keyboard = root.createNestedObject("keyboard");
    webapi_.GetKeyboardInfo(keyboard);

    auto crazyfm = root.createNestedObject("crazyfm");
    webapi_.GetCrazyFMInfo(crazyfm);

    response->setLength();
    request->send(response);
    CrazyLog::d(kTag, "all read done");
  });

  // reboot
  server_.on("/sys/reboot", HTTP_POST, [&](AsyncWebServerRequest *request) {
    CrazyLog::d(kTag, "reboot");
    context()->frame().RestartOS();
  });

  // wifi
  server_.on("/sys/wifi", HTTP_POST, [&](AsyncWebServerRequest *request) {
    CrazyLog::d(kTag, "wifi save");
    WifiInfo info = {.ssid = GetFilterParam(request, "ssid"),
                     .password = GetFilterParam(request, "password")};
    CrazyLog::i(kTag, "wifi save,info: %s", info.ssid);
    WifiInfoKeyChain().Save(info);
    request->send(200);
  });

  // Device
  server_.on("/sys/device", HTTP_POST, [&](AsyncWebServerRequest *request) {
    CrazyLog::d(kTag, "device save");
    String color_r = GetFilterParam(request, "color_r");
    String color_g = GetFilterParam(request, "color_g");
    String color_b = GetFilterParam(request, "color_b");
    int r = atoi(color_r.c_str());
    int g = atoi(color_g.c_str());  
    int b = atoi(color_b.c_str());
    r = min(max(0, r), 255);
    g = min(max(0, g), 255);
    b = min(max(0, b), 255);

    String lock_gesutre_str = GetFilterParam(request, "lock_gesutre");
    bool lock_gesutre = lock_gesutre_str.compareTo("true") == 0 ? true : false;

#if CRAZY_LOG_YELL
    CrazyLog::d(kTag, "Update color r:%d g:%d b:%d", r,
                g, b);
#endif
    auto info = DeviceInfo{r, g, b,lock_gesutre};
    DeviceKeyChain().save(info);
    request->send(200);
  });

  // Group APP
  server_.on("/sys/group", HTTP_POST, [&](AsyncWebServerRequest *request) {
    CrazyLog::d(kTag, "group app save");

      String body = request->getParam("body", true)->value();
      CrazyLog::d(kTag, "body:%s",body.c_str());

      PSRamJsonDocument doc(body.length() * 4);
      DeserializationError error = deserializeJson(doc, body);
      if (error) {
        CrazyLog::e(kTag, "deserializeJson failed:%s",error.c_str());
        request->send(500);
        return;
      }
      CrazyLog::d(kTag, "deserializeJson success");
      JsonArray array = doc["g1"];
      std::vector<String> app_ids;
      for (int i = 0; i < array.size(); i++) {
        //const char* id = array[i]["id"];
        const char* id = array[i];
        if(id) app_ids.push_back(String(id));
      }
      GroupKeyChain().Save(GROUP_APP_G1,app_ids);
      request->send(200);
  });

  // Assistant
  server_.on("/sys/asst", HTTP_POST, [&](AsyncWebServerRequest *request) {
    CrazyLog::d(kTag, "Assistant save");
    String asst_id = GetFilterParam(request, "asst_id");
    String asst_secret = GetFilterParam(request, "asst_secret");
    String asst_tts_voice_str = GetFilterParam(request, "asst_tts_voice");
    int16_t asst_tts_voice = atoi(asst_tts_voice_str.c_str());

    String asst_nlp_str = GetFilterParam(request, "asst_nlp");
    int16_t asst_nlp = atoi(asst_nlp_str.c_str());
    String asst_openai_key = GetFilterParam(request, "asst_openai_key");

#if CRAZY_LOG_YELL
    CrazyLog::d(kTag, "save asst_id: %s, asst_secret_length:%d, asst_tts_voice:%d",
                asst_id.c_str(), asst_secret.length(), asst_tts_voice);
#endif

    AssistantChain().Save(AssistantInfo{asst_id, asst_secret, asst_tts_voice,asst_nlp, asst_openai_key});
    request->send(200);
  });

  // Keyboard
  server_.on("/sys/keyboard", HTTP_POST, [&](AsyncWebServerRequest *request) {
    CrazyLog::d(kTag, "keyboard save");
    String kb_name = GetFilterParam(request, "kb_name");
    String kb_up = GetFilterParam(request, "kb_up");
    String kb_down = GetFilterParam(request, "kb_down");
    String kb_left = GetFilterParam(request, "kb_left");
    String kb_right = GetFilterParam(request, "kb_right");
    String kb_cw = GetFilterParam(request, "kb_cw");
    String kb_anticw = GetFilterParam(request, "kb_anticw");
#if CRAZY_LOG_YELL
    CrazyLog::d(kTag,
                "Update keyboard: "
                "kb_name:%s,kb_up:%s,kb_down:%s,kb_left:%s,kb_right:%s,kb_"
                "cw:%s,kb_anticw:%s",
                kb_name.c_str(), kb_up.c_str(), kb_down.c_str(),
                kb_left.c_str(), kb_right.c_str(), kb_cw.c_str(),
                kb_anticw.c_str());
#endif
    KeyboardKeyChain().Save(KeyboardInfo{kb_name, kb_up, kb_down, kb_left,
                                         kb_right, kb_cw, kb_anticw});
    request->send(200);
  });
}

void WebServer::RegisterRouteApp() {
 
  // Desktop
  server_.on("/app/desktop", HTTP_POST, [&](AsyncWebServerRequest *request) {
    CrazyLog::d(kTag, "desktop save");
    String desk_sign = GetFilterParam(request, "desk_sign");
    String desk_screensaver_str = GetFilterParam(request, "desk_screensaver");
    bool desk_screensaver = desk_screensaver_str.compareTo("true") == 0 ? true : false;
    DesktopKeyChain().Save(DesktopInfo{desk_sign,desk_screensaver});
    request->send(200);
  });

  // CrazyFM
  server_.on("/app/crazyfm", HTTP_POST, [&](AsyncWebServerRequest *request) {
    CrazyLog::d(kTag, "crazyfm save");

    CrazyFMInfo info = {
        .channel1 = {.title = GetFilterParam(request, "title_1"),
                     .url = GetFilterParam(request, "url_1")},
        .channel2 = {.title = GetFilterParam(request, "title_2"),
                     .url = GetFilterParam(request, "url_2")},
        .channel3 = {.title = GetFilterParam(request, "title_3"),
                     .url = GetFilterParam(request, "url_3")}};
#if CRAZY_LOG_YELL
    CrazyLog::d(kTag,
                "info save: title_1: %s, url_1:%s, title_2: %s, "
                "url_2:%s,title_3: %s, url_3:%s,",
                info.channel1.title, info.channel1.url, info.channel2.title,
                info.channel2.url, info.channel3.title, info.channel3.url);
#endif
    CrazyFMInfoKeyChain().Save(info);
    request->send(200);
  });


  // 获取 Photo 文件 列表
  server_.on("/app/photo", HTTP_GET, [&](AsyncWebServerRequest *request) {
    CrazyLog::d(kTag, "request get files: photo");
    DoGetFileList(request, WebFileType::PHOTO);
  });

  // 删除 Photo 文件,并返回 容量信息
  server_.on("/app/photo", HTTP_DELETE, [&](AsyncWebServerRequest *request) {
    CrazyLog::d(kTag, "request delete file: photo");
    DoDeleteFile(request, WebFileType::PHOTO);
  });

  // 上传 Photo 文件
  server_.on("/app/photo/upload", HTTP_POST, [](AsyncWebServerRequest *request) { 
    //request->send(200,"text","success");  //上传成功返回 success
     request->send(200);
  },
  [&](AsyncWebServerRequest *request, String filename, size_t index,uint8_t *data, size_t len, bool final) {
      auto result = webapi_.HandleUploadFile(request, filename,index, data,len,final, WebFileType::PHOTO);
      if(result == UploadFileResult::ERROR){
        CrazyLog::e(kTag, "upload file failed");
        request->send(500);//上传文件失败，终止
        request->client()->close(true);
      }
  });
}


void WebServer::DoGetFileList(AsyncWebServerRequest *request, WebFileType type){
    CrazyLog::d(kTag, "DoGetFileList");
    AsyncJsonResponse *response = new AsyncJsonResponse(false);
    JsonVariant &root = response->getRoot();

    auto files = root.createNestedArray("files");
    auto meta = root.createNestedObject("meta");
    webapi_.GetFiles(files, meta, type);

    CrazyLog::d(kTag, "file nums:%d", files.size());

    response->setLength();
    request->send(response);
    CrazyLog::d(kTag, "DoGetFileList done");
}

void WebServer::DoDeleteFile(AsyncWebServerRequest *request, WebFileType type) {
    CrazyLog::d(kTag, "DoDeleteFile");
    auto file_name = GetFilterParam(request, "file_name");
    CrazyLog::i(kTag, "request delete file name: %s", file_name.c_str());
    auto success = webapi_.DeleteFile(file_name, type);
    if (!success) {
      request->send(500);
      return;
    }
    // 删除成功后返回容量信息
    AsyncJsonResponse *response = new AsyncJsonResponse(false);
    JsonVariant &root = response->getRoot();
    auto meta = root.createNestedObject("meta");
    webapi_.GetFilesMeta(meta, type);
    response->setLength();
    request->send(response);
    CrazyLog::d(kTag, "DoDeleteFile done");
}