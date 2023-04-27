/**
 * @file  imu.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @date 2022/6/20
 * @brief MPU6050
 */

#pragma once

#include <I2Cdev.h>
#include <MPU6050_6Axis_MotionApps20.h>

#define IMU_I2C_SDA 32
#define IMU_I2C_SCL 33

#define IMU_DEFALUT_VALUE_UP -12
#define IMU_DEFALUT_VALUE_DOWN 8
#define IMU_DEFALUT_VALUE_LEFT -12
#define IMU_DEFALUT_VALUE_RIGHT 12

struct EularAngle {
  float yaw;    // 偏航角
  float pitch;  // 俯仰角
  float roll;   // 翻滚角
};

class IMU {
 private:
  const char* kTag = "IMU";
  long last_update_time_;
  bool ready_ = false;
  MPU6050 mpu_;
  uint8_t fifo_buffer_[48];
  // packet structure for "/test/mpu.pde"
  uint8_t teapotPacket[14] = {'$', 0x02, 0, 0,    0,    0,    0,
                              0,   0,    0, 0x00, 0x00, '\r', '\n'};
  void SentToProcessing(uint8_t* fifo_buffer);

 public:
  bool Init();
  bool Update(int interval, EularAngle* angle, bool sent_to_processing = false);
  bool Update(EularAngle* angle);
  void Stop();
  void Reset();
  bool ready() { return ready_; }
};
