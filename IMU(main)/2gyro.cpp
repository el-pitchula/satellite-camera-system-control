// pra accel e gyro juntos na vdd mas fds, esse é o código mais completo
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

float thetaG=0;
float phiG=0;
float dt; //altera no tempo pela ultima medida 
//(baseado na velocidade angular (ômega) do eixo em questão)
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
        //+ um vetor e add do segundo grau de liberdade 

  thetaM=-atan2(acc.x()/9.8,acc.z()/9.8)/2/3.141592654*360;
  phiM=atan2(acc.y()/9.8,acc.z()/9.8)/2/3.141592654*360;

  thetaFnew=.95*thetaFold+.05*thetaM;
  phiFnew=.95*phiFold+.05*phiM;

  dt=(millis()-millisOld); //variação tempo
  millisOld=millis();

  thetaG=thetaG+gyr.y()*dt; // thetaG + ômega (velocidade angular) * dt
  phiG=phiG+gyr.x()*dt;

  Serial.print(acc.x()/9.8);
  Serial.print(",");
  Serial.print(acc.y()/9.8);
  Serial.print(",");
  Serial.print(acc.z()/9.8);
  Serial.print(",");

  Serial.print(thetaG); //gyro após add variação do tempo
  Serial.print(",");
  Serial.print(phiG);
  Serial.print(",");


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
  Serial.print(thetaFnew);
  Serial.print(",");
  Serial.println(phiFnew);

  phiFold=phiFnew;
  thetaFold=thetaFnew;

  delay(BNO055_SAMPLERATE_DELAY_MS);
}