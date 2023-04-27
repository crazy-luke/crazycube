#pragma once

#include <freertos/FreeRTOS.h>
#include <lwip/apps/sntp.h>
#include <stdio.h>
#include <time.h>

#include "tools/crazy_log.h"

namespace TimerHelper {

static bool SyncTime(void) {
  const char* kTag = "sntp";
  CrazyLog::d(kTag, "sync_time");
  sntp_setoperatingmode(SNTP_OPMODE_POLL);
  sntp_setservername(0, "ntp1.aliyun.com");
  sntp_setservername(1, "time2.cloud.tencent.com");
  sntp_init();

  char strftime_buf[64];
  // wait for time to be set
  time_t now = 0;
  struct tm timeinfo = {0};
  int retry = 0;
  const int retry_count = 10;

  while (retry < retry_count && timeinfo.tm_year < (2020 - 1900)) {
#if CRAZY_LOG_YELL
    CrazyLog::d(kTag, "Waiting for system time to be set... (%d)", ++retry);
#endif
    vTaskDelay(500);
    time(&now);
    localtime_r(&now, &timeinfo);
  }

  setenv("TZ", "CST-8", 1);  // 东八区时间
  tzset();

  strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
  CrazyLog::d(kTag, "The current date/time in Shanghai is: %s", strftime_buf);
  sntp_stop();
  return timeinfo.tm_year > (2020 - 1900);
}

static unsigned long GetTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return (0);
  }
  time(&now);
  return now;
}

static tm* GetLocalTime() {
  time_t timep;
  time(&timep);
  // struct tm *pTM = gmtime(&timep);
  struct tm* pTM = localtime(&timep);
  return pTM;
}

static std::string getCurrentTime(const char* formater) {
  struct timeval tv;
  gettimeofday(&tv, NULL);

  static constexpr size_t MAX_BUFFER_SIZE = 128;
  char buff[MAX_BUFFER_SIZE + 1];
  time_t sec = static_cast<time_t>(tv.tv_sec);
  int ms = static_cast<int>(tv.tv_usec) / 1000;

  struct tm tm_time;
  localtime_r(&sec, &tm_time);
  // static const char *formater = "%4d-%02d-%02d %02d:%02d:%02d.%03d";
  int ret = snprintf(buff, MAX_BUFFER_SIZE, formater, tm_time.tm_year + 1900,
                     tm_time.tm_mon + 1, tm_time.tm_mday, tm_time.tm_hour,
                     tm_time.tm_min, tm_time.tm_sec, ms);
  if (ret < 0) {
    return std::string("");
  }

  return std::string(buff);
}

}  // namespace TimerHelper