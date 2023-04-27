#include "imu.h"

#include "tools/crazy_log.h"
#include "sys.h"

bool IMU::Init() {
  CrazyLog::d(kTag, "Init");
  Wire.begin(IMU_I2C_SDA, IMU_I2C_SCL);
  Wire.setClock(400000);  // 400kHz I2C clock

  mpu_.initialize();
   
  uint16_t timeout = 4000;
  uint8_t retryTimes = 0;
  while (!mpu_.testConnection()) {
    delay(500);
    retryTimes++;
    if (retryTimes * 500 >= timeout) {
      CrazyLog::w(kTag, "MPU init failed!");
      ready_ = false;
      return false;
    }
    Serial.print(".");
  }
  // load and configure the DMP

  uint8_t devStatus = mpu_.dmpInitialize();

  // upply your own gyro offsets here, scaled for min sensitivity
  //  mpu_.setXGyroOffset(220);
  //  mpu_.setYGyroOffset(76);
  //  mpu_.setZGyroOffset(-85);
  //  mpu_.setZAccelOffset(1788); // 1688 factory default for my test chip
  // make sure it worked (returns 0 if so)
  if (devStatus == 0) {
    mpu_.CalibrateAccel(7);
    mpu_.CalibrateGyro(7);
    mpu_.PrintActiveOffsets();
    mpu_.setDMPEnabled(true);
    ready_ = true;
  }

  if (ready_)
    CrazyLog::d(kTag, "MPU init success");
  else
    CrazyLog::e(kTag, "MPU init failed %d", devStatus);

   return ready_;
}

bool IMU::Update(EularAngle* angle){
  Quaternion q;         // [w, x, y, z]         quaternion container
  VectorFloat gravity;  // [x, y, z]            gravity vector
   // mpu_.dmpPacketSize
  float ypr[3];  // [yaw, pitch, roll]   yaw/pitch/roll 
  // read a packet from FIFO
  bool fifo_success = mpu_.dmpGetCurrentFIFOPacket(fifo_buffer_);
  if (fifo_success && angle) 
  {  // Get the Latest packet
    // display Euler angles in degrees
    mpu_.dmpGetQuaternion(&q, fifo_buffer_);
    mpu_.dmpGetGravity(&gravity, &q);
    mpu_.dmpGetYawPitchRoll(ypr, &q, &gravity);
    angle->yaw = ypr[0] * 180 / M_PI;
    angle->pitch = ypr[1] * 180 / M_PI;
    angle->roll = ypr[2] * 180 / M_PI;
#if CRAZY_LOG_YELL    
    CrazyLog::d(kTag, "yaw: %f, pitch: %f, roll: %f", angle->yaw, angle->pitch, angle->roll);
#endif
  }
  return fifo_success;
}

bool IMU::Update(int interval, EularAngle* angle, bool sent_to_processing)
{
  if (!ready_){
#if CRAZY_LOG_YELL    
    CrazyLog::e(kTag, "MPU Not Ready~!");
#endif 
    return false;
  }
  if (millis() - last_update_time_ < interval) {
#if CRAZY_LOG_YELL 
     CrazyLog::d(kTag, "time threshold");
#endif     
     return false;
  }
  
  if(Update(angle) && sent_to_processing){
    SentToProcessing(fifo_buffer_);
  }

  last_update_time_ = millis();
  return true;
}

void IMU::Stop() {
  CrazyLog::d(kTag, "MPU Stop!");
  mpu_.reset();
  mpu_.setSleepEnabled(true);
  ready_ = false;
}

void IMU::SentToProcessing(uint8_t* fifo_buffer){
  // display quaternion values in InvenSense Teapot demo format:
  // w: 0 1
  // x: 4 5
  // y: 8 9
  // z: 12 13
  teapotPacket[2] = fifo_buffer[0];  
  teapotPacket[3] = fifo_buffer[1];
  teapotPacket[4] = fifo_buffer[4];
  teapotPacket[5] = fifo_buffer[5];
  teapotPacket[6] = fifo_buffer[8];
  teapotPacket[7] = fifo_buffer[9];
  teapotPacket[8] = fifo_buffer[12];
  teapotPacket[9] = fifo_buffer[13];
  Serial.write(teapotPacket, 14);
  teapotPacket[11]++; // packetCount, loops at 0xFF on purpose
}

void IMU::Reset(){
  CrazyLog::d(kTag, "MPU Reset");
  ready_ = false;
  mpu_.reset();
  Init();
}
