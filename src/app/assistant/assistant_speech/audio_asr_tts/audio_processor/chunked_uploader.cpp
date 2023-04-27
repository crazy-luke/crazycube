#include "chunked_uploader.h"

#include <ArduinoJson.h>

#include "tools/psram_allocator.h"
#include "tools/crazy_log.h"


ChunkedUploader::ChunkedUploader()
{  
  CrazyLog::d(kTag, "constructor!"); 
}


ChunkedUploader::~ChunkedUploader()
{
    CrazyLog::d(kTag,"~release");
    // wifi_client_.stop();    //wifi_client_ 析构时内部会处理关闭
}


bool ChunkedUploader::ConnectHost(String token,String dev_pid, uint8_t retry_times) {
    CrazyLog::d(kTag, "Init"); 
    uint8_t try_time = 0;
    bool success = false;
    while(try_time ++ <= (retry_times+1) && !success){
        CrazyLog::w(kTag,"connectting host...");
        success = wifi_client_.connect("vop.baidu.com", 80,5000);
    }
    if(!success){
        CrazyLog::w(kTag,"connect host failed!");
        return false;
    }

    CrazyLog::d(kTag,"connect host success");
    // wifi_client_.connect("vop.baidu.com", 80);
    char authorization_header[100];
    snprintf(authorization_header, 100, "authorization: Bearer %s", token);
    String cuid = WiFi.macAddress();
    String  post = "POST /server_api?dev_pid="+dev_pid+"&cuid="+cuid+"&token="+token + " HTTP/1.1";
    wifi_client_.println(post.c_str());
    wifi_client_.println("host: vop.baidu.com");
    wifi_client_.println(authorization_header);
    wifi_client_.println("content-type: audio/pcm; rate=16000;");
    wifi_client_.println("transfer-encoding: chunked");
    wifi_client_.println();
    return success;
}

bool ChunkedUploader::connected()
{
   return wifi_client_.connected();
}

void ChunkedUploader::StartChunk(int size_in_bytes)
{
    wifi_client_.printf("%X\r\n", size_in_bytes);
}


size_t ChunkedUploader::SendChunkData(const uint8_t *data, int size_in_bytes)
{
   return wifi_client_.write(data, size_in_bytes);
}

void ChunkedUploader::FinishChunk()
{
    wifi_client_.print("\r\n");
}


BaiduASRResult ChunkedUploader::GetResults()
{
    BaiduASRResult asr;
    // finish the chunked request by sending a zero length chunk
    wifi_client_.print("0\r\n");
    wifi_client_.print("\r\n");
    // get the headers and the content length
    int status = -1;
    int content_length = 0;
    while (wifi_client_.connected())
    {
        char buffer[255];
        int read = wifi_client_.readBytesUntil('\n', buffer, 255);
        if (read > 0)
        {
            buffer[read] = '\0';
            // blank line indicates the end of the headers
            if (buffer[0] == '\r')
            {
                break;
            }
            if (strncmp("HTTP", buffer, 4) == 0)
            {
                sscanf(buffer, "HTTP/1.1 %d", &status);
            }
            else if (strncmp("Content-Length:", buffer, 15) == 0)
            {
                sscanf(buffer, "Content-Length: %d", &content_length);
            }
        }
    }
    CrazyLog::d(kTag, "Http status is %d with content length of %d\n", status, content_length);
    
    if (status == HTTP_CODE_OK)
    {
        String textResult = wifi_client_.readString();
       #if CRAZY_LOG_YELL    // save memory
        CrazyLog::d(kTag,"asr result : %s",textResult.c_str());
       #endif

       PSRamJsonDocument doc(content_length*2);
       DeserializationError error = deserializeJson(doc, textResult);
        if (error) {
            CrazyLog::e(kTag, "result deserializeJson failed: %s", error.c_str());
            return asr;
        }
        const char *err_no = doc["err_no"];
        const char *err_msg = doc["err_msg"];
        const char *corpus_no = doc["corpus_no"];
        const char *sn = doc["sn"];
        const char *result = doc["result"][0];

        asr.err_no = (err_no ? String(err_no) : "");
        asr.err_msg = (err_msg ? String(err_msg) : "");
        asr.corpus_no = (corpus_no ? String(corpus_no) : "");
        asr.sn = (sn ? String(sn) : "");
        asr.result_text = (result ? String(result) : "");
        if(asr.err_no.length()==0 || asr.result_text.length()>0){
            asr.success = true;
        }

        #if CRAZY_LOG_YELL    // save memory
        CrazyLog::d(kTag,"err_no:%s, err_msg:%s, sn: %s, corpus_no:%s, result:%s",asr.err_no.c_str(), asr.err_msg.c_str(), asr.corpus_no.c_str(), asr.sn,asr.result_text.c_str());
        #endif
    }
    return asr;
}

