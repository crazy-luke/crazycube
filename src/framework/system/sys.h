/**
 * @file sys.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief  CrazyCube SysInfo
 * @version 1.0
 * @date 2022-08-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once


#define FIRMWARE_VERSION_CODE   1001
#define FIRMWARE_VERSION_NAME   String("1.3.0")

// Core 
#define CORE_0   0
#define CORE_1   1   

// Task Priority, 0 是最低优先级
#define TASK_PRIORITY_SPEAKER       20      // Speaker
#define TASK_PRIORITY_GIF           24      // Gif
#define TASK_PRIORITY_APP           8       // APP
#define TASK_PRIORITY_WIFI          2       // Wifi
#define TASK_PRIORITY_LED           1       // LED灯
#define TASK_PRIORITY_AUDIOMONITOR  2       // AudioMonitor
#define TASK_PRIORITY_SAMPLER       4       // Mic
#define TASK_PRIORITY_ASSISTANT     4       // ASSISTANT

// USED PSRAM 
// SPEAKER    300K
// MIC SAMPLE 35K       SAMPLE_PSRAM_BUF * SAMPLE_BUFFER_COUNT * sizeof(int16_t)
// LVGL       320K      LV_USE_PNG, needs lots of memory!, 32K -> 320K,  Should I optimize? 
// Tensorflow ARENA 25K 
// Tensorflow MODEL  44K

// SPEAKER  
#define SPEAKER_PSRAM_BUF 1024 * 300 
// MIC SAMPLE
#define SAMPLE_PSRAM_BUF 1600
#define SAMPLE_BUFFER_COUNT 11
//Tensorflow
#define TENSOR_PSRAM_ARENA_SIZE  25*1024
//其他 ps_malloc


// FILEPATH_ROOT   文件根目录
#define FILEPATH_ROOT_CACHE String("/cache")
#define FILEPATH_ROOT_AUDIO String("/audio")
#define FILEPATH_ROOT_MIAGE String("/image")
#define FILEPATH_ROOT_PHOTO String("/photo")
#define FILEPATH_ROOT_NES String("/nes")
#define FILEPATH_ROOT_GIF String("/gif")
#define SPIFF_LVGL_PREFIX String("S:")
#define FILEPATH_SPIFF_LVGL(filepath) (SPIFF_LVGL_PREFIX + filepath).c_str()