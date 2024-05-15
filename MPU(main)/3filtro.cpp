#include <Wire.h>
#include <MPU6050.h>
#include <math.h>

#define MPU6050_SAMPLERATE_DELAY_MS (100) // Sample rate and delay of 100 ms
MPU6050 mpu;

float thetaM; // Measured
float phiM;
float thetaFold = 0; // First
float thetaFnew;
float phiFold = 0;
float phiFnew;

float thetaG = 0; // Gyro
float phiG = 0;
float dt; // Time variation
unsigned long millisOld;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();
  delay(1000);
  millisOld = millis();
}

void loop() {
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  thetaM = -atan2((float)ax / 16384.0, (float)az / 16384.0) / 2 / 3.141592654 * 360;
  phiM = atan2((float)ay / 16384.0, (float)az / 16384.0) / 2 / 3.141592654 * 360;

  thetaFnew = 0.95 * thetaFold + 0.05 * thetaM;
  phiFnew = 0.95 * phiFold + 0.05 * phiM;

  int16_t gx, gy, gz;
  mpu.getRotation(&gx, &gy, &gz);
  dt = (millis() - millisOld) / 1000.0; // Time variation in seconds
  millisOld = millis();

  thetaG += ((float)gy / 16384.0) * dt; // thetaG + omega (angular velocity) * dt
  phiG += ((float)gx / 16384.0) * dt;

  // Complementary filter
  float theta = (thetaG + thetaM) * 0.95 + thetaFnew * 0.05;
  float phi = (phiG + phiM) * 0.95 + phiFnew * 0.05;

  Serial.print((float)ax / 16384.0);
  Serial.print(",");
  Serial.print((float)ay / 16384.0);
  Serial.print(",");
  Serial.print((float)az / 16384.0);
  Serial.print(",");

  Serial.print(thetaG); // Gyro after adding time variation
  Serial.print(",");
  Serial.print(phiG);
  Serial.print(",");
/*
  Serial.print(thetaM);
  Serial.print(",");
  Serial.print(phiM);
  Serial.print(",");
  Serial.print(thetaFnew);
  Serial.print(",");
  Serial.print(phiFnew);
*/
  Serial.print(theta);
  Serial.print(",");
  Serial.println(phi);

  phiFold = phiFnew;
  thetaFold = thetaFnew;

  delay(MPU6050_SAMPLERATE_DELAY_MS);
}