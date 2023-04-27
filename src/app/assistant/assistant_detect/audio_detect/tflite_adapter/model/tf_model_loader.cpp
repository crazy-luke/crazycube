#include "tf_model_loader.h"

#include <Arduino.h>
#include <SPIFFS.h>

#include <fstream>
#include <iostream>
#include <vector>

#include "tools/crazy_log.h"

unsigned char* TFModelLoader::GeadTFModelRAM(const char* modelFilePath,
                                             unsigned int len, bool psram) {
  CrazyLog::d(kTag, "GeadTFModelRAM");
  //读取数据文件
  std::ifstream in(modelFilePath, std::ios::in);
  if (!in.is_open()) {
    CrazyLog::e(kTag, "open file error");
    return NULL;
  } 
  //将数据文件数据存入数组
  unsigned char* model =
      psram ? (unsigned char*)ps_malloc(len) : (unsigned char*)malloc(len);
  in.read((char*)model, len);
  std::cout << in.gcount() << "characters read\n";
  in.close();
  return model;
}

unsigned char* TFModelLoader::GetWakeupModel() {
  CrazyLog::d(kTag, "GetWakeupModel");
  unsigned char* model = GeadTFModelRAM(
      TF_MODEL_WAKEUP_FILE_PATH, TF_MODEL_WAKEUP_LEN, TF_MODEL_WAKEUP_PSRAM);
  if (model) {
    CrazyLog::i(kTag, "load model success");
  } else {
    CrazyLog::e(kTag, "load model failed");
  }
  return model;
}