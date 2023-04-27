/**
 * @file tf_model_loader.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief  load model to psram from file
 * @version 1.0
 * @date 2022-09-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#define TF_MODEL_WAKEUP_FILE_PATH "/spiffs/model/tf.ccc"
#define TF_MODEL_WAKEUP_LEN 44128
#define TF_MODEL_WAKEUP_PSRAM 1

class TFModelLoader
{
private:
    const char * kTag = "TFModelLoader";
    unsigned char* GeadTFModelRAM(const char * modelFilePath,  unsigned int len, bool psram);

public:
    unsigned char * GetWakeupModel();
};

