#include "crazy_log.h"

#include <stdio.h>
#include <time.h>
#include <iostream>
#include <vector>

LogLevel log_level_ = LogLevel::DEBUG;

static void logger(const char *tag, LogLevel level, const char *fmt,
                   va_list args) {
#if CRAZY_LOG_ENABLE
  time_t timep;
  time(&timep);
  struct tm *pTM = localtime(&timep);
  printf("[%4d-%02d-%02d %02d:%02d:%02d] ", pTM->tm_year + 1900,
         pTM->tm_mon + 1, pTM->tm_mday, pTM->tm_hour, pTM->tm_min, pTM->tm_sec);

  printf("[LogLevel:%d] [TAG:%s]", level, (tag ? tag : "unkonwTag"));
  vprintf(fmt, args);
  printf("\n");
#endif
}

void CrazyLog::set_level(LogLevel level){
  log_level_ = level;
}

LogLevel CrazyLog::level(){
  return log_level_;
}

void CrazyLog::v(const char *tag, const char *fmt, ...) {
#if CRAZY_LOG_ENABLE
  if (log_level_ > LogLevel::VERBOSE) return;
  va_list args;  // 定义一个va_list类型的变量，用来储存单个参数
  va_start(args, fmt);  // 使args指向可变参数的第一个参数
  logger(tag, LogLevel::VERBOSE, fmt, args);  // 打印日志
  va_end(args);                               // 结束可变参数的获取
#endif
}

void CrazyLog::d(const char *tag, const char *fmt, ...) {
#if CRAZY_LOG_ENABLE
  if (log_level_ > LogLevel::DEBUG) return;
  va_list args;
  va_start(args, fmt);
  logger(tag, LogLevel::DEBUG, fmt, args);
  va_end(args);
#endif
}

void CrazyLog::i(const char *tag, const char *fmt, ...) {
#if CRAZY_LOG_ENABLE
  if (log_level_ > LogLevel::INFO) return;
  va_list args;
  va_start(args, fmt);
  logger(tag, LogLevel::INFO, fmt, args);
  va_end(args);
#endif
}

void CrazyLog::w(const char *tag, const char *fmt, ...) {
#if CRAZY_LOG_ENABLE
  if (log_level_ > LogLevel::WARN) return;
  va_list args;
  va_start(args, fmt);
  logger(tag, LogLevel::WARN, fmt, args);
  va_end(args);
#endif
}

void CrazyLog::e(const char *tag, const char *fmt, ...) {
#if CRAZY_LOG_ENABLE
  if (log_level_ > LogLevel::ERROR) return;
  va_list args;
  va_start(args, fmt);
  logger(tag, LogLevel::ERROR, fmt, args);
  va_end(args);
#endif
}

void CrazyLog::ram(const char *tag) {
#if CRAZY_LOG_ENABLE
  printf("vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv-S %s \n", tag);
  // printf("PSRAM  size: %u \n", ESP.getPsramSize());
  printf("PSRAM  free: %u \n", ESP.getMaxAllocPsram());
  printf("RAM  size: %u \n", ESP.getHeapSize());
  printf("RAM  free: %u \n", ESP.getFreeHeap());
  printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^-E\n");
#endif
}

unsigned ts_ = 0;
void CrazyLog::ts(const char *tag){
  printf("ts %s: %u \n",tag, millis()- ts_);
  ts_ = millis();
}