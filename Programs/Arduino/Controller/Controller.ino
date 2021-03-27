#include <ros.h>

#include <Wire.h>

#include <ros.h>
#include <std_msgs/String.h>

#define TCAADDR 0x70

//ros::NodeHandle  nh;

//std_msgs::String str_msg;
//ros::Publisher chatter("chatter", &str_msg);
char hello[13] = "hello world!";

int x = 0;
void tcaselect(uint8_t i)
{
 if (i > 7) return;
 Wire.beginTransmission(TCAADDR);
 Wire.write(1 << i);
 Wire.endTransmission();  
}

const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

void setup()
{
 Serial.begin(57600);
 Wire.begin();

 tcaselect(0);
 Wire.beginTransmission(MPU_addr);
 Wire.write(0x6B);  // PWR_MGMT_1 register
 Wire.write(0);     // set to zero (wakes up the MPU-6050)
 Wire.endTransmission(true);
 Serial.println ("Done 0");
 tcaselect(1);
 Wire.beginTransmission(MPU_addr);
 Wire.write(0x6B);  // PWR_MGMT_1 register
 Wire.write(0);     // set to zero (wakes up the MPU-6050)
 Wire.endTransmission(true);
 Serial.println ("Done 1");
 
 tcaselect(2);
 Wire.beginTransmission(MPU_addr);
 Wire.write(0x6B);  // PWR_MGMT_1 register
 Wire.write(0);     // set to zero (wakes up the MPU-6050)
 Wire.endTransmission(true);
 Serial.println ("Done 1");
 
 tcaselect(3);
 Wire.beginTransmission(MPU_addr);
 Wire.write(0x6B);  // PWR_MGMT_1 register
 Wire.write(0);     // set to zero (wakes up the MPU-6050)
 Wire.endTransmission(true);
 Serial.println ("Done 3");
// ----------------------FOR ROS node--------start--------
// nh.initNode();
// nh.advertise(chatter);
//--------------------FOR ROS node -------- end --------
}

void loop(){

for(int x=0; x<4; x++){
 tcaselect(x);
 Wire.beginTransmission(MPU_addr);
 Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
 Wire.endTransmission(false);
 Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
 AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
 AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
 AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
 Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
 GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
 GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
 GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
Serial.print("PORT: (");Serial.print(x); Serial.print(")\t");
Serial.print(AcX); Serial.print("\t");
Serial.print(AcY); Serial.print("\t");
Serial.print(AcZ); Serial.print("\t");
Serial.print(Tmp/340.00+36.53); Serial.print("\t"); //equation for temperature in degrees C from datasheet 
Serial.print(GyX); Serial.print("\t");
Serial.print(GyY); Serial.print("\t");
Serial.println(GyZ); 
delay(10);

// ----------------------FOR ROS node--------start--------
//  str_msg.data = hello;
 // chatter.publish( &str_msg );
 // nh.spinOnce();
  //--------------------FOR ROS node -------- end --------
}

}
