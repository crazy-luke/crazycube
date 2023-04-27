/**
 * @file file_manager.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief Manager File, make sure SPIFFS.begin() before us it
 * @version 1.0
 * @date 2022-08-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <WString.h>
#include <vector>

struct FileInfo {
  String name;
  size_t size;
  String size_rd;  // for human read
  String path;
};

class FileManager {
 private:
  const char* kTag = "FileManager";

 public:
  std::vector<FileInfo> GetFileList(String root_path, std::vector<String> suffix_list);
  std::vector<FileInfo> GetFileList(String root_path, String suffix = "");
  bool DeleteFile(String file_path);
  size_t GetFolderSize(String folder_path);
  String ReadableSize(const size_t bytes);
  //sort by name
  void SortFiles(std::vector<FileInfo> & files);
  //剩余空间
  size_t GetRemainSize(); 
  //删除文件夹中所有文件
  bool DeleteFolderFiles(String folder_path);
};