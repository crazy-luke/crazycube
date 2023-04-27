说明

本目录文件为第三方 lib 定制修改内容，需要覆盖到 .ipo/lib_deps 对应目录下

如：
   "conf_libdeps/lvgl/lv_conf.h" 复制到 ".pio/libdeps/pico32/lvgl/lv_conf.h"


//--------------------------------------------------------------------
// ********** 以下内容仅做部分说明，可以不看 **********
// ********** 配置修改注释以此开头👉  //crazycube: 
//--------------------------------------------------------------------

一、LVGL 配置： 
   1. 基础配置
      lv_conf_template.h 改名 lv_conf.h
      #if 1
      #define LV_TICK_CUSTOM 1

   2. 启用 PSRAM
    #define LV_MEM_SIZE (320U * 1024U)  
    #define LV_MEM_POOL_INCLUDE <esp32-hal-psram.h> 
    #define LV_MEM_POOL_ALLOC   ps_malloc 

   3. 启用 png 文件(注意 需要大量内存, LV_MEM_SIZE 提高到320)
      /*PNG decoder library*/
      #define LV_USE_PNG 1

      #define LV_USE_FS_STDIO 1
      #if LV_USE_FS_STDIO
         #define LV_FS_STDIO_LETTER 'S'     /*Set an upper cased letter on which the drive will accessible (e.g. 'A')*/
         #define LV_FS_STDIO_PATH "/spiffs"         /*Set the working directory. File/directory paths will be appended to it.*/
         #define LV_FS_STDIO_CACHE_SIZE  0   /*>0 to cache this number of bytes in lv_fs_read()*/
      #endif

   4. 启用 SJPG
      #define LV_USE_SJPG 1

   5. 启用图片缓存   //默认为0， 如果不启用，Bilibili 头像区域 UI更新时会很慢（比如唤起状态栏 sysbar ）
      #define LV_IMG_CACHE_DEF_SIZE   2   

二、TFT_eSPI 配置：

User_Setup_Select.h
启用配置
	//#include <User_Setup.h>	注释这行
	#include <User_Setups/Setup24_ST7789.h>	//打开行

Setup24_ST7789.h
屏幕大小
   #define TFT_WIDTH  240
   #define TFT_HEIGHT 240

引脚配置
   #define TFT_MISO -1
   #define TFT_MOSI 7
   #define TFT_SCLK 8
   #define TFT_CS    -1
   #define TFT_DC    2
   #define TFT_RST   4

 屏幕时钟
   #define SPI_FREQUENCY  40000000

ST7789_Rotation.h
   屏幕镜像适配


三、ESP32-audioI2S Audio 修改
原始 512-10 太短，导致 播放 TTS URL可能失败

Audio.h //Line 419
    char            chbuf[1024 + 128];               // must be greater than m_lastHost #254
    char            m_lastHost[1024];                // Store the last URL to a webstream
    char*           m_playlistBuff = NULL;          // stores playlistdata
    const uint16_t  m_plsBuffEntryLen = 512;        // length of each entry in playlistBuff


Audio.cpp //Line 432
   if(strlen(host) >= 1024 - 10) {
      if(audio_info) audio_info("Hostaddress is too long");
      return false;
   }


Audio.cpp //Line 179 改小一些节约大量DMA缓存（播放时会增加一些CPU负担，可以提高播放任务优先级 ）
    m_i2s_config.dma_buf_count        = 4;      // 8->4 max buffers
    m_i2s_config.dma_buf_len          = 512;   // 1024 -> 512 max value
   


malloc -> ps_malloc
   auido.h  357行
   audio.cpp 437、511、515、758、800、944、2645


四、FastLED（无需操作）
立方豆需要LED PIN20 被FastLED禁用
修改 fastpin_esp32.h 85行
