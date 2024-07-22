#include <Wire.h>
#include <MPU6050.h>
#include <math.h>

#define MPU6050_SAMPLERATE_DELAY_MS (100) // Taxa de amostragem e atraso de 100 ms
MPU6050 mpu;

float thetaM; // Medido
float phiM;
float thetaFold = 0; // Primeiro
float thetaFnew;
float phiFold = 0;
float phiFnew;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();
  delay(1000);
}

void loop() {
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  thetaM = -atan2((float)ax / 16384.0, (float)az / 16384.0) / 2 / 3.141592654 * 360;
  phiM = atan2((float)ay / 16384.0, (float)az / 16384.0) / 2 / 3.141592654 * 360;

  thetaFnew = 0.9 * thetaFold + 0.1 * thetaM;
  phiFnew = 0.9 * phiFold + 0.1 * phiM;

  Serial.print((float)ax / 16384.0);
  Serial.print(",");
  Serial.print((float)ay / 16384.0);
  Serial.print(",");
  Serial.print((float)az / 16384.0);
  Serial.print(",");
  
  Serial.print(thetaM);
  Serial.print(",");
  Serial.print(phiM);
  
  Serial.print(thetaFnew);
  Serial.print(",");
  Serial.println(phiFnew);

  phiFold = phiFnew;
  thetaFold = thetaFnew;

  delay(MPU6050_SAMPLERATE_DELAY_MS);
}