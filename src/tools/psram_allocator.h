/**
 * @file psram_allocator.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief ArduinoJson + PSRAM 
 * @version 1.0
 * @date 2022-08-17
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include <memory>

#include "tools/crazy_log.h"

struct PSRamAllocator {
  void* allocate(size_t size) {
#if CRAZY_LOG_YELL
    CrazyLog::d("PSRamAllocator", "allocate size:%d",size);
#endif
    return heap_caps_malloc(size, MALLOC_CAP_SPIRAM);
  }

  void deallocate(void* pointer) {
#if CRAZY_LOG_YELL    
    CrazyLog::d("PSRamAllocator", "deallocate");
#endif    
    heap_caps_free(pointer);
  }

  void* reallocate(void* ptr, size_t new_size) {
#if CRAZY_LOG_YELL
    CrazyLog::d("PSRamAllocator", "reallocate size:%d",new_size);
#endif    
   return heap_caps_realloc(ptr, new_size, MALLOC_CAP_SPIRAM);
  }
};

using PSRamJsonDocument = BasicJsonDocument<PSRamAllocator>;
