/**
 * @file web_api.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief WebServer data process
 * @version 1.0
 * @date 2022-08-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>


#define RESERVE_FLASH_SIZE 1024 * 384  //保留一部分空间为其他APP服务

// 上传文件类型
enum class WebFileType {
  PHOTO,
};

//上传文件状态
enum class UploadFileResult{
  ERROR, //错误
  BUFFER, //继续上传
  SUCCESS, //上传文件成功完成
};

//上传文件地址
struct UploadFilePath{
  String file_path; //  文件地址
  String file_path_tmp; //临时文件地址
};


class WebApi {
 private:
  const char* kTag = "WebApi";
  UploadFilePath GetUploadFilePath(WebFileType type, const String &filename);  //获取上传文件路径
  String GetFileRootPath(WebFileType type); //文件根路径

 public:
  void GetCrazyFMInfo(JsonObject& obj);
  void GetKeyboardInfo(JsonObject& obj);
  void GetWifiInfo(JsonObject& obj);
  void GetDeviceInfo(JsonObject& obj);
  void GetDesktopInfo(JsonObject& obj);
  void GetGroupAppInfo(JsonObject& obj);
  void GetAssistantInfo(JsonObject& obj);
  // 获取文件 列表
  void GetFiles(JsonArray& json_files, JsonObject& meta, WebFileType type);
  // 获取文件 meta 信息： 容量
  void GetFilesMeta(JsonObject& meta, WebFileType type);
  // 删除文件
  bool DeleteFile(String name, WebFileType type);
  // 上传文件
  UploadFileResult HandleUploadFile(AsyncWebServerRequest* request, const String& filename,
                        const size_t& index, uint8_t* data,const size_t& len,const bool& final,
                        WebFileType type);                        
};