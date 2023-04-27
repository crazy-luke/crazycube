/**
 * @file crazy_log.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief Code is cheap , show me the log
 * @version 1.0
 * @date 2022-08-17
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <Arduino.h>

#define CRAZY_LOG_YELL 0  // set 0 to save memory while relese model
#define CRAZY_LOG_ENABLE 1

enum class LogLevel { VERBOSE = 0, DEBUG, INFO, WARN, ERROR };

class CrazyLog {
  
 public:
  static void set_level(LogLevel level);
  static LogLevel level();
  static void ram(const char *tag);  // show memory
  static void ts(const char *tag);   // show time cost

 public:
  static void v(const char *tag, const char *fmt, ...);
  static void d(const char *tag, const char *fmt, ...);
  static void i(const char *tag, const char *fmt, ...);
  static void w(const char *tag, const char *fmt, ...);
  static void e(const char *tag, const char *fmt, ...);
};
