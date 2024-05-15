#include <Wire.h>
#include <MPU6050.h>
#include <math.h>
#include <Servo.h>

#define MPU6050_SAMPLERATE_DELAY_MS (100)
MPU6050 mpu;

float thetaM;
float phiM;
float thetaFold = 0;
float thetaFnew;
float phiFold = 0;
float phiFnew;

float thetaG = 0;
float phiG = 0;
float dt;
unsigned long millisOld;

Servo pitchServo;
Servo rollServo;

float rollTarget = 0;
float rollActual;
float rollError;
float rollServoVal = 90;

float pitchTarget = 0;
float pitchActual;
float pitchError;
float pitchServoVal = 90;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();
  delay(1000);
  millisOld = millis();

  pitchServo.attach(2);
  rollServo.attach(3);

  pitchServo.write(pitchServoVal);
  delay(20);
  rollServo.write(rollServoVal);
  delay(20);
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
  dt = (millis() - millisOld) / 1000.0;
  millisOld = millis();

  thetaG += ((float)gy / 16384.0) * dt; // thetaG + omega (angular velocity) * dt
  phiG += ((float)gx / 16384.0) * dt;

  // filtro
  float theta = (thetaG + thetaM) * 0.95 + thetaFnew * 0.05;
  float phi = (phiG + phiM) * 0.95 + phiFnew * 0.05;

  rollActual = theta;
  pitchActual = phi;

  rollError = rollTarget - rollActual;
  pitchError = pitchTarget - pitchActual;

  if (abs(pitchError) > 1.5) {
    pitchServoVal += pitchError / 2;
    pitchServo.write(pitchServoVal);
    delay(20);
  }

  if (abs(rollError) > 1.5) {
    rollServoVal += rollError / 2;
    rollServo.write(rollServoVal);
    delay(20);
  }

  Serial.print(rollTarget);
  Serial.print(",");
  Serial.print(rollActual);
  Serial.print(",");
  Serial.print(pitchTarget);
  Serial.print(",");
  Serial.print(pitchActual);
  Serial.print(",");
  Serial.print(thetaG);
  Serial.print(",");
  Serial.print(phiG);
  Serial.print(",");
  Serial.print(theta);
  Serial.print(",");
  Serial.println(phi);

  phiFold = phiFnew;
  thetaFold = thetaFnew;

  delay(MPU6050_SAMPLERATE_DELAY_MS);
}
