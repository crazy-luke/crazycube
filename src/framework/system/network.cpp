#include "network.h"

#include <FS.h>
#include <SPIFFS.h>

#include "tools/crazy_log.h"
#include "tools/psram_allocator.h"

#define USER_AGENT                                                      \
  "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 " \
  "(KHTML, like Gecko) Chrome/102.0.0.0 Safari/537.36"



bool Network::Connect(String ssid, String password, uint16_t timeout) {
  WiFi.mode(WIFI_STA);
  // WiFi.enableSTA(true);
  WiFi.begin(ssid.c_str(), password.c_str());
  CrazyLog::d(kTag, "Start Connect Wifi");
  uint8_t retryTimes = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    retryTimes++;
    if (retryTimes * 500 >= timeout) {
      WiFi.disconnect();
      CrazyLog::w(kTag, "WiFi connect failed!");
      return false;
    }
    Serial.print(".");
  }
  WiFi.setAutoConnect(true);
  CrazyLog::i(kTag, "WiFi connected");
  Serial.println(WiFi.localIP());
  return true;
}

bool Network::WifiAP() {
  if (WiFi.isConnected()) {
    WiFi.setAutoConnect(false);
    WiFi.disconnect();
  }

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(kIP, kIP, kNetmask);
  String ssid = "CrazyCube - " + WiFi.macAddress();
  bool result = WiFi.softAP(ssid.c_str(), "", 1, 0, 4);
  if (!result) {
    CrazyLog::w(kTag, "WiFi failed");
  }
  return result;
}

bool Network::IsConnected() { return WiFi.isConnected(); }

//CrazyAdam: 此封装会增加一次 JsonDocument Copy 行为， 大数据建议直接使用 HttpGetRequest
HttpJsonResult Network::HttpGetRequestJson(String url) {
  CrazyLog::d(kTag, "HttpGetRequestJson");
  auto result = HttpGetRequest(url);
  if(result.success) {
    PSRamJsonDocument doc(result.data.length() * 2);
    DeserializationError error = deserializeJson(doc, result.data);
    if (!error) {
      CrazyLog::d(kTag, "deserializeJson success");
      return {true, result.code, doc};
    }
    CrazyLog::e(kTag, "deserializeJson error");
  }
  PSRamJsonDocument doc(0);
  return {false, result.code, doc};
}

HttpStringResult Network::HttpGetRequest(String url, uint8_t retry_times) {

  if(retry_times > NETWORK_RETRY_TIME_MAX_LIMIT) {
    CrazyLog::w(kTag, "oops~ max retry time is %d", NETWORK_RETRY_TIME_MAX_LIMIT);
    retry_times = NETWORK_RETRY_TIME_MAX_LIMIT;
  }

  uint8_t try_time = 0;
  bool success = false;
  HttpStringResult result;
  
  while(!success && try_time ++ <= (retry_times+1)){
      result = HttpGetRequest(url);
      success = result.success;
      //retry
      if(!success && result.code == HTTPC_ERROR_CONNECTION_REFUSED)
        continue;
      else 
        break;
   }

 return result;
}

HttpStringResult Network::HttpGetRequest(String url) {
  
#if CRAZY_LOG_YELL  // save memory
  CrazyLog::d(kTag, "HttpGetRequest url= %s", url.c_str());
#else
  CrazyLog::d(kTag, "HttpGetRequest");
#endif

  if (!WiFi.isConnected()) {
    CrazyLog::w(kTag, "wifi is not connected");
    return HttpStringResult{false,-1, "{}"};
  }

if(ESP.getFreeHeap()< NETWORK_MEM_WARNNING) CrazyLog::ram(kTag);

#ifdef NETWORK_WITH_LOCK
  CrazyLog::d(kTag, "lock HttpGetRequest");
  std::lock_guard<std::mutex> l(lock_task_); 
#endif

  HTTPClient http;
  http.setUserAgent(USER_AGENT);
  http.setConnectTimeout(NETWORK_CONNECT_TIMEOUT);
  http.setTimeout(NETWORK_READ_TIMEOUT);
  http.begin(url);


  // Send HTTP Get request
  int code = 0;
  try {
    code = http.GET();
  } catch (const std::exception& e) {
    CrazyLog::e(kTag, "http.GET error: %s", e.what());
  }
  String payload = code > 0 ? http.getString() : "{}";

#if CRAZY_LOG_YELL  // save memory
  CrazyLog::d(kTag, "httpCode: %d, payload:%s", code, payload.c_str());
#endif

  bool success = (code == HTTP_CODE_OK || code == HTTP_CODE_MOVED_PERMANENTLY) ? true : false;
  if (!success) CrazyLog::e(kTag, "HttpGetRequest error!  httpCode=%d", code);
  http.end();

#ifdef NETWORK_WITH_LOCK
  CrazyLog::d(kTag, "unlock HttpGetRequest");
#endif
  return HttpStringResult{success, code, payload};
}

HttpStringResult Network::HttpPostRequest(String url, String json_body, String auth, uint16_t timeout, uint8_t retry_times) {

  if(retry_times > NETWORK_RETRY_TIME_MAX_LIMIT) {
    CrazyLog::w(kTag, "oops~ max retry time is %d", NETWORK_RETRY_TIME_MAX_LIMIT);
    retry_times = NETWORK_RETRY_TIME_MAX_LIMIT;
  }

  uint8_t try_time = 0;
  bool success = false;
  HttpStringResult result;
  
  while(!success && try_time ++ <= (retry_times+1)){
      result = HttpPostRequest(url, json_body, auth, timeout);
      success = result.success;
      //retry
      if(!success && result.code == HTTPC_ERROR_CONNECTION_REFUSED)
        continue;
      else 
        break;
   }

 return result;
}

HttpStringResult Network::HttpPostRequest(String url, String json_body, String auth, uint16_t timeout) {
#if CRAZY_LOG_YELL
  CrazyLog::d(kTag, "HttpPostRequest url= %s", url.c_str());
#else
  CrazyLog::d(kTag, "HttpPostRequest");
#endif

  if (!WiFi.isConnected()) {
    return HttpStringResult{false,-1, "{}"};
  }

  if(ESP.getFreeHeap()< NETWORK_MEM_WARNNING) CrazyLog::ram(kTag);
#ifdef NETWORK_WITH_LOCK
  CrazyLog::d(kTag, "lock HttpPostRequest");
  std::lock_guard<std::mutex> l(lock_task_); 
#endif
  HTTPClient http;
  http.setUserAgent(USER_AGENT);
  http.setConnectTimeout(NETWORK_CONNECT_TIMEOUT);
  http.setTimeout(timeout);
  http.begin(url);

  http.addHeader("Content-Type", "application/json");
  if(!auth.isEmpty()){
    http.addHeader("Authorization", "Bearer " + auth);
  }


  // Send HTTP POST request
  int code = 0;

  try {
    CrazyLog::d(kTag, "http.Post");
    code = http.POST(json_body);
  } catch (const std::exception& e) {
    CrazyLog::e(kTag, "http.Posterror: %s", e.what());
  }
  String payload = code > 0 ? http.getString() : "{}";

#if CRAZY_LOG_YELL  // save memory
  CrazyLog::d(kTag, "httpCode: %d, payload:%s", code, payload.c_str());
#endif

  bool success = (code == HTTP_CODE_OK || code == HTTP_CODE_MOVED_PERMANENTLY) ? true : false;
  if (!success) CrazyLog::e(kTag, "HttpPostRequest error!  httpCode=%d", code);
  http.end();

#ifdef NETWORK_WITH_LOCK
  CrazyLog::d(kTag, "unlock HttpPostRequest");
#endif  

  return HttpStringResult{success, code, payload};
}

bool Network::DownloadAndSaveFile(String filePath, String url) {
#if CRAZY_LOG_YELL  // save memory
  CrazyLog::d(kTag, "DownloadAndSaveFile filePath=%s, url=%s", filePath.c_str(),
              url.c_str());
#endif

#ifdef NETWORK_WITH_LOCK
  CrazyLog::d(kTag, "lock DownloadAndSaveFile");
  std::lock_guard<std::mutex> l(lock_task_); 
#endif

  bool success = false;
  HTTPClient http;
  http.setConnectTimeout(NETWORK_CONNECT_TIMEOUT);
  http.setTimeout(NETWORK_READ_TIMEOUT);
  http.begin(url);
  int httpCode = http.GET();
  CrazyLog::d(kTag, "httpCode: %d", httpCode);
  if (httpCode > 0) {
    //    int code = http.GET();
    File file = SPIFFS.open(filePath.c_str(), FILE_WRITE);
    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      // get lenght of document (is -1 when Server sends no Content-Length
      // header)
      int len = http.getSize();
      CrazyLog::d(kTag, "http.getSize(): %d", len);
      // create buffer for read
      const uint8_t buff_len = 128;
      uint8_t* buff = (uint8_t*)ps_calloc(buff_len, sizeof(uint8_t));
      // get tcp stream
      WiFiClient* stream = http.getStreamPtr();
      // read all data from server
      while (http.connected() && (len > 0 || len == -1)) {
        // get available data size
        size_t size = stream->available();
        if (size) {
          // size_t car_len = (size > buff_len) ? buff_len : size;
          // CrazyLog::d("download","size:%d, car_len:%d",size,car_len);
          // read up to buff_len byte
          int c = stream->readBytes(buff, (size > buff_len) ? buff_len : size);
          file.write(buff, c);
          if (len > 0) {
            len -= c;
          }
        }

        delay(1);
      }
      CrazyLog::d(kTag, "download file finish");
      file.close();
      free(buff);
      success = true;
    }
  }
  http.end();

#ifdef NETWORK_WITH_LOCK
  CrazyLog::d(kTag, "unlock DownloadAndSaveFile");
#endif    
  return success;
}

int8_t Network::SignalStrength(){
  return WiFi.RSSI();
}
