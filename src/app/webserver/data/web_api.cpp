#include "web_api.h"

#include <SPIFFS.h>

#include "keychain/keychain.h"
#include "tools/crazy_log.h"
#include "tools/file_manager.h"
#include "framework/system/sys.h"
#include "app/app_list.h"
#include "keychain/kc_group.h"


void WebApi::GetCrazyFMInfo(JsonObject& obj){
    auto info = CrazyFMInfoKeyChain().Read();
    obj["title_1"] = info.channel1.title;
    obj["url_1"] = info.channel1.url;
    obj["title_2"] = info.channel2.title;
    obj["url_2"] = info.channel2.url;
    obj["title_3"] = info.channel3.title;
    obj["url_3"] = info.channel3.url;
}

void WebApi::GetKeyboardInfo(JsonObject& obj){
    auto info = KeyboardKeyChain().Read();
    obj["kb_name"] = info.name;
    obj["kb_up"] = info.up;
    obj["kb_down"] = info.down;
    obj["kb_left"] = info.left;
    obj["kb_right"] = info.right;
    obj["kb_cw"] = info.clockwise;
    obj["kb_anticw"] = info.anticlockwise;
}

void WebApi::GetWifiInfo(JsonObject& obj){
    auto info = WifiInfoKeyChain().ReadSecurity();
    obj["ssid"] = info.ssid;
    obj["password"] = info.password;
}

 void WebApi::GetDeviceInfo(JsonObject& obj){
    auto info = DeviceKeyChain().Read();
    obj["color_r"] = info.color_r;
    obj["color_g"] = info.color_g;
    obj["color_b"] = info.color_b;
    obj["lock_gesutre"] = info.lock_gesutre;
 }

  void WebApi::GetDesktopInfo(JsonObject& obj){
    auto info = DesktopKeyChain().Read();
    obj["desk_sign"] = info.sign;
    obj["desk_screensaver"] = info.auto_screensaver;
 }

void WebApi::GetGroupAppInfo(JsonObject& obj){

     auto add_apps = [](JsonArray array,std::vector<AppShell*> apps) -> void { 
       for (auto& app : apps) {
            auto obj = array.createNestedObject();
            obj["id"] = app->app_id();
            obj["name"] = app->app_name();
        }
        AppList().Clean(apps);
     };

    add_apps(obj.createNestedArray("g0"), AppList().RootAPP(false));
    add_apps(obj.createNestedArray("g1"), AppList().GroupAPP(GROUP_APP_G1));

    // auto group =  obj.createNestedArray("g0");
    // auto apps = applist.RootAPP(false);
    // for (auto& app : apps) {
    //     auto obj = group.createNestedObject();
    //     obj["id"] = app->app_name();
    //     obj["name"] = app->app_name();
    // }
    // applist.Clean(apps);

    // // add g1 with GROUP_APP_G1
    // group =  obj.createNestedArray("g1");
    // apps = applist.GroupAPP(GROUP_APP_G1);

    // for (auto& app : apps) {
    //     auto obj = group.createNestedObject();
    //     obj["id"] = app->app_name();
    //     obj["name"] = app->app_name();
    // }
    // applist.Clean(apps);

 }

 void WebApi::GetAssistantInfo(JsonObject& obj){
    auto info = AssistantChain().Read();
    obj["asst_id"] = info.asst_id;
    obj["asst_secret"] = info.asst_secret;
    obj["asst_tts_voice"] = info.asst_tts_voice;
    obj["asst_nlp"] = info.asst_nlp;
    obj["asst_openai_key"] = info.asst_openai_key;
 }


String WebApi::GetFileRootPath(WebFileType type){
    switch (type)
    {
    case WebFileType::PHOTO:
        return FILEPATH_ROOT_PHOTO;
    }
}

void WebApi::GetFiles(JsonArray& json_files, JsonObject& meta, WebFileType type){
    FileManager fm;
    std::vector<FileInfo> files  = fm.GetFileList(GetFileRootPath(type));
    fm.SortFiles(files);

    size_t total_size =0;
    for(auto file: files){
        auto obj = json_files.createNestedObject();
        obj["name"] = file.name;
        obj["size"] = file.size;
        obj["size_rd"] = file.size_rd;
        // obj["path"] = file.path; //no need
        total_size += file.size;
    }
    auto total = fm.ReadableSize(total_size);
    meta["file_total"] = total;
    size_t remain_size = fm.GetRemainSize();
    auto remain = fm.ReadableSize(remain_size);
    meta["file_remain"] = remain;
    CrazyLog::d(kTag,"file_total:%s, file_remain:%s",total.c_str(), remain.c_str());
}

void WebApi::GetFilesMeta(JsonObject& meta, WebFileType type){
    FileManager  fm;
    size_t total_size = fm.GetFolderSize(GetFileRootPath(type));
    auto total = fm.ReadableSize(total_size);
    meta["file_total"] = total;
    size_t remain_size = fm.GetRemainSize();
    auto remain = fm.ReadableSize(remain_size);
    meta["file_remain"] = remain;
    CrazyLog::d(kTag,"file_total:%s, file_remain:%s",total.c_str(), remain.c_str());
}

 bool WebApi::DeleteFile(String name, WebFileType type){
    String file_path = GetFileRootPath(type) + "/" + name;    
    return FileManager().DeleteFile(file_path);
 }

// 文件先保存到 临时文件 
UploadFileResult WebApi::HandleUploadFile(AsyncWebServerRequest* request, const String& filename,
                        const size_t& index, uint8_t* data, const size_t& len, const bool& final,
                        WebFileType type){

 // CrazyLog::d(kTag, "HandleUploadFile");

  if (!index) {
    auto path = GetUploadFilePath(type, filename);

    CrazyLog::d(kTag, "url:%s", request->url().c_str());
    if (SPIFFS.exists(path.file_path)) {
      CrazyLog::w(kTag, "file already exist! cancel request");
      return UploadFileResult::ERROR;
    }
    
    if (SPIFFS.exists(path.file_path_tmp)) SPIFFS.remove(path.file_path_tmp);
    
    auto remain_size = FileManager().GetRemainSize();
    size_t request_file_size = request->contentLength();

    CrazyLog::d(kTag, "file_size:%d, remain_size:%d",request_file_size,remain_size);
    if((request_file_size + RESERVE_FLASH_SIZE) > remain_size ){
      CrazyLog::w(kTag, "file too large failed!");
      return UploadFileResult::ERROR;
    }

    CrazyLog::d(kTag, "Start upload file %s to path %s ",filename.c_str(), path.file_path_tmp.c_str());

    // open the file on first call and store the file handle in the
    // request
    
    request->_tempFile = SPIFFS.open(path.file_path_tmp, "w");
  }

  if (len) {
    // stream the incoming chunk to the opened file
    // CrazyLog::d(kTag, "Writing file:%s, index= %d, len=%d ", filename.c_str(),
    //             index, len);
    request->_tempFile.write(data, len);
  }

  if (final) {
    auto path = GetUploadFilePath(type, filename);

    
    CrazyLog::d(kTag, "rename %s to %s ", path.file_path_tmp.c_str(), path.file_path.c_str());
    bool rename_success =  SPIFFS.rename(path.file_path_tmp, path.file_path);
    // close the file handle as the upload is now done
    request->_tempFile.close();
    
    if(rename_success){
        CrazyLog::d(kTag, "Upload Complete::%s, size=%d ", filename.c_str(), index + len);
        return UploadFileResult::SUCCESS;   //文件上传成功
    }else {
        SPIFFS.remove(path.file_path_tmp);
        CrazyLog::d(kTag, "rename tmp file %s failed , delete tmp file", path.file_path_tmp.c_str());
        return UploadFileResult::ERROR; //文件上传错误
    }
  }

  return UploadFileResult::BUFFER;  //文件上传中
}

UploadFilePath WebApi::GetUploadFilePath(WebFileType type, const String &filename){

    String tmp_file = FILEPATH_ROOT_CACHE + "/web_tmp_.tmp";   //单一临时文件，避免垃圾文件产生

    if(type == WebFileType::PHOTO) {
        return UploadFilePath{
            FILEPATH_ROOT_PHOTO + "/" +filename,
            tmp_file,
        };
    }


}