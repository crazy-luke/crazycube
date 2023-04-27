#include "file_manager.h"

#include <SPIFFS.h>
#include <wctype.h>

#include "tools/crazy_log.h"

std::vector<FileInfo> FileManager::GetFileList(String root_path, String suffix) {
   std::vector<String> suffix_list;
   if(!suffix.isEmpty()) suffix_list.push_back(suffix);
  return GetFileList(root_path, suffix_list);
}

std::vector<FileInfo> FileManager::GetFileList(String root_path, std::vector<String> suffix_list){
  std::vector<FileInfo> files;
  File root = SPIFFS.open(root_path);
  File file = root.openNextFile();
  while (file) {
    //fliter
    bool legal = true;
    if(suffix_list.size()>0){
      legal = false;
      for(auto suffix: suffix_list){
        suffix.toLowerCase();
        String name = String(file.name());
        name.toLowerCase();
        if(name.endsWith(suffix)) {
          legal = true;
          break;
        }
      }
    }

    // push file
    if(legal){
      String name = String(file.name());
      size_t size = file.size();
      String path = String(file.path());
      FileInfo info = FileInfo{name, size, ReadableSize(size), path};
      files.push_back(info);
    }else{
      CrazyLog::d(kTag, "file %s is not match suffix", file.name());
    }
    
    //close
    file.close();
    file = root.openNextFile();
  }
  root.close();

  for(auto file : files){
    CrazyLog::d(kTag, "get file:%s", file.name.c_str());
  }

  return files;
}

String FileManager::ReadableSize(const size_t bytes) {
  if (bytes < 1024)
    return String(bytes) + " B";
  else if (bytes < (1024 * 1024))
    return String(bytes / 1024) + " KB";
  else if (bytes < (1024 * 1024 * 1024))
    return String(bytes / 1024.0 / 1024.0) + " MB";
  else
    return String(bytes / 1024.0 / 1024.0 / 1024.0) + " GB";
}

bool FileManager::DeleteFile(String file_path) {
  bool success = false;
  if (SPIFFS.exists(file_path)) {
    CrazyLog::d(kTag,"delete file %s",file_path.c_str());
    success = SPIFFS.remove(file_path);
  }else{
    CrazyLog::w(kTag,"no file: %s",file_path.c_str());
  }
  return success;
}

void FileManager::SortFiles(std::vector<FileInfo> & files) {
 
  std::sort(files.begin(),files.end(),[](FileInfo file1, FileInfo file2)-> bool{  
      String name1 = file1.name;
      String name2 = file2.name;
      std::transform(name1.begin(),name1.end(), name1.begin(),::towlower);
      std::transform(name2.begin(),name2.end(), name2.begin(),::towlower);
      return name2 > name1;
  });

  // for(auto file : files){
  //     CrazyLog::d(kTag, "before sort, filename:%s", file.name.c_str());
  // }  
}

size_t FileManager::GetFolderSize(String folder_path) {
    std::vector<FileInfo> files  = GetFileList(folder_path);
    size_t total_size =0;
    for(auto file: files){
        total_size += file.size;
    }
    return total_size;
}

size_t FileManager::GetRemainSize() {
  return SPIFFS.totalBytes()  - SPIFFS.usedBytes();
}

bool FileManager::DeleteFolderFiles(String folder_path){
  CrazyLog::d(kTag,"DeleteFolderFiles: %s", folder_path.c_str());
  if(folder_path.isEmpty()) return false;

  std::vector<String> files;
  File root = SPIFFS.open(folder_path);
  File file = root.openNextFile();
  while (file) {
    files.push_back(file.path());
    file.close();
    file = root.openNextFile();
  }
  root.close();

  for(auto file : files){
    CrazyLog::i(kTag, "remove file:%s", file.c_str());
    SPIFFS.remove(file);
  }

  return true;
}