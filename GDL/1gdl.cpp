#include "Wire.h"
#include "I2Cdev.h" 
#include "MPU6050.h" 
#include "Servo.h" 

MPU6050 mpu; 
int16_t ax, ay, az; 
int16_t gx, gy, gz; 
Servo servo1; 
Servo servo2;

int val1; 
int val2; 
int prevVal1; 
int prevVal2; 

void setup() 
{ 
  Wire.begin(); 
  Serial.begin(38400); 
  Serial.println("Initialize MPU"); 
  mpu.initialize(); 
  Serial.println(mpu.testConnection() ? "Connected" : "Connection failed"); 
  servo1.attach(9); 
  servo2.attach(10);
} 

void loop() 
{ 
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); 
  val1 = map(ax, -17000, 17000, 0, 179); 
  if (val1 != prevVal1) 
  { 
    servo1.write(val1); 
    prevVal1 = val1; 
  } 
  val2 = map(ay, -17000, 17000, 0, 179); 
  if (val2 != prevVal2) 
  { 
    servo2.write(val2); 
    prevVal2 = val2; 
  } 
  delay(50); 
}

//add o filtro complementar

/*

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Servo.h>

Servo servo;
Adafruit_MPU6050 srituhobby;

void setup(void) {
  Serial.begin(115200);
  servo.attach(3);
  Wire.begin();
  srituhobby.begin();
  servo.write(0);

  srituhobby.setAccelerometerRange(MPU6050_RANGE_8_G);//2_G,4_G,8_G,16_G
  srituhobby.setGyroRange(MPU6050_RANGE_500_DEG);//250,500,1000,2000
  srituhobby.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);
}

void loop() {

  // Get new sensor events with the readings
  sensors_event_t a, g, temp;
  srituhobby.getEvent(&a, &g, &temp);

  int value = a.acceleration.y;

  value = map(value,  -10, 10, 180, 0);
  servo.write(value);  
  Serial.println(value);
  //delay(10);

}

*/