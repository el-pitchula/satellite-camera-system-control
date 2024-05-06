#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <math.h>

#define BNO055_SAMPLERATE_DELAY_MS (100)
Adafruit_BNO055 myIMU = Adafruit_BNO055();

float thetaM;
float phiM;
float thetaFold=0;
float thetaFnew;
float phiFold=0;
float phiFnew;

float theta; 
float phi;

float thetaG=0;
float phiG=0;

// p/o magnetrômetro
float Xm;
float Ym;
float psi;
//
float thetaRad;
float phiRad;

float dt;
unsigned long millisOld;

void setup() {
  Serial.begin(115200);
  myIMU.begin();
  delay(1000);
  int8_t temp=myIMU.getTemp();
  myIMU.setExtCrystalUse(true);
  millisOld=millis();
}

void loop() {
  uint8_t system, gyro, accel, mg = 0;
  myIMU.getCalibration(&system, &gyro, &accel, &mg);

  imu::Vector<3> acc = myIMU.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  imu::Vector<3> gyr = myIMU.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  imu::Vector<3> mag = myIMU.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);

  thetaM=-atan2(acc.x()/9.8,acc.z()/9.8)/2/3.141592654*360;
  phiM=-atan2(acc.y()/9.8,acc.z()/9.8)/2/3.141592654*360;

  thetaFnew=.95*thetaFold+.05*thetaM;
  phiFnew=.95*phiFold+.05*phiM;

  dt=(millis()-millisOld)/1000.;
  millisOld=millis();

  thetaG=thetaG+gyr.y()*dt;
  phiG=phiG-gyr.x()*dt;

  theta=(theta+gyr.y()*dt)*.95+thetaM*.05;
  phi=(phi-gyr.x()*dt)*.95+phiM*.05;

  //
  phiRad=phi/360*(2*3.14);
  thetaRad=theta/360*(2*3.14);

  //mag
  Xm=mag.x()*cos(thetaRad)-mag.y()*sin(phiRad)*sin(thetaRad)+mag.z()*cos(phiRad)*sin(thetaRad); //n tenho certeza ainda
  Ym=mag.y()*cos(phiRad)+mag.z()*sin(phiRad);
  psi=atan2(Ym,Xm)/(2*3.14)*360;

  Serial.print(acc.x()/9.8);
  Serial.print(",");
  Serial.print(acc.y()/9.8);
  Serial.print(",");
  Serial.print(acc.z()/9.8);
  Serial.print(",");

  Serial.print(",");
  Serial.print(thetaG);
  Serial.print(",");
  Serial.print(phiG);


  Serial.print(accel);
  Serial.print(",");
  Serial.print(gyro);
  Serial.print(",");
  Serial.print(mg);
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
  Serial.print(phi);

  Serial.print(",");
  Serial.println(psi);

  phiFold=phiFnew;
  thetaFold=thetaFnew;

 
  delay(BNO055_SAMPLERATE_DELAY_MS);
}