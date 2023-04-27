/**
 * @file chunked_uploader.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief chunked 分段上传
 * @version 1.0
 * @date 2022-09-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <HTTPClient.h>
#include <WString.h>

// https://ai.baidu.com/ai-doc/SPEECH/mk4o0bijn
struct BaiduASRResult {
  bool success;
  String err_no;
  String err_msg;
  String corpus_no;
  String sn;
  String result_text;
};

// https://cloud.baidu.com/doc/SPEECH/s/ek38lxj1u
#define DEV_PID_SPEECH_MANDARIN String("1537")  // 普通话(纯中文识别)
#define DEV_PID_SPEECH_ENGLISH String("1737")   // 英语模型

class ChunkedUploader {
 private:
  const char *kTag = "ChunkedUploader";

  WiFiClient wifi_client_;

 public:
  ChunkedUploader();
  ~ChunkedUploader();

  // retry_times, 连接失败重试次数，defalut: 0
  bool ConnectHost(String token, String dev_pid, uint8_t retry_times = 0);
  bool connected();
  void StartChunk(int size_in_bytes);
  size_t SendChunkData(const uint8_t *data, int size_in_bytes);
  void FinishChunk();
  BaiduASRResult GetResults();
  void uploadfile(String token);
};
