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

float thetaG=0;
float phiG=0;
float dt; //altera no tempo pela ultima medida 
//(baseado na velocidade angular (ômega) do eixo em questão)
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
        //+ um vetor e add do segundo grau de liberdade 

  thetaM=-atan2(acc.x,acc.z)/2/3.141592654*360;
  phiM=atan2(acc.y,acc.z)/2/3.141592654*360;

  thetaFnew=.95*thetaFold+.05*thetaM;
  phiFnew=.95*phiFold+.05*phiM;

  dt=(millis()-millisOld); //variação tempo
  millisOld=millis();

  thetaG=thetaG+gyr.y*dt; // thetaG + ômega (velocidade angular) * dt
  phiG=phiG+gyr.x*dt;

  Serial.print(acc.x/9.8);
  Serial.print(",");
  Serial.print(acc.y/9.8);
  Serial.print(",");
  Serial.print(acc.z/9.8);
  Serial.print(",");

  Serial.print(thetaG); //gyro após add variação do tempo
  Serial.print(",");
  Serial.print(phiG);
  Serial.print(",");


  Serial.print(accel.acceleration);
  Serial.print(",");
  Serial.print(gyro.gyro);
  Serial.print(",");
  Serial.print(system);
  Serial.print(",");


  Serial.print(thetaM);
  Serial.print(",");
  Serial.print(phiM);
  Serial.print(thetaFnew);
  Serial.print(",");
  Serial.println(phiFnew);

  phiFold=phiFnew;
  thetaFold=thetaFnew;

  delay(MPU6050_SAMPLERATE_DELAY_MS);
}