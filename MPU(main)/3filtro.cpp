#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>
#include <utility/imumaths.h>
#include <math.h>

#define MPU6050_SAMPLERATE_DELAY_MS (100)
Adafruit_MPU6050 mpu;

float thetaM;
float phiM;
float thetaFold=0;
float thetaFnew;
float phiFold=0;
float phiFnew;

// p/o filtro complementar (Gy e Ac juntos)
float theta; // p/def theta e phi geral 
float phi;

float thetaG=0;
float phiG=0;
float dt;
unsigned long millisOld;

void setup() {
  Serial.begin(115200);
  mpu.begin();
  delay(1000);
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  millisOld=millis();
}

void loop() {
  sensors_event_t accel, gyro;
  mpu.getEvent(&accel, &gyro);
  
  imu::Vector<3> acc = accel.acceleration;
  imu::Vector<3> gyr = gyro.gyro;

  thetaM=-atan2(acc.x,acc.z)/2/3.141592654*360;
  phiM=-atan2(acc.y,acc.z)/2/3.141592654*360;

  thetaFnew=.95*thetaFold+.05*thetaM;
  phiFnew=.95*phiFold+.05*phiM;

  dt=(millis()-millisOld)/1000.;
  millisOld=millis();

  thetaG=thetaG+gyr.y*dt;
  phiG=phiG-gyr.x*dt;

    // filtro:
  theta=(theta+gyr.y*dt)*.95+thetaM*.05;
  phi=(phi-gyr.x*dt)*.95+phiM*.05;

  Serial.print(acc.x/9.8);
  Serial.print(",");
  Serial.print(acc.y/9.8);
  Serial.print(",");
  Serial.print(acc.z/9.8);
  Serial.print(",");

  Serial.print(",");
  Serial.print(thetaG);
  Serial.print(",");
  Serial.print(phiG);


  Serial.print(accel.acceleration);
  Serial.print(",");
  Serial.print(gyro.gyro);
  Serial.print(",");
  Serial.print(system);
  Serial.print(",");


  Serial.print(thetaM);
  Serial.print(",");
  Serial.print(phiM);
  Serial.print(",");
  Serial.print(thetaFnew);
  Serial.print(",");
  Serial.print(phiFnew);


  Serial.print(theta);
  Serial.print(",");
  Serial.println(phi);

  phiFold=phiFnew;
  thetaFold=thetaFnew;


  delay(MPU6050_SAMPLERATE_DELAY_MS);
}