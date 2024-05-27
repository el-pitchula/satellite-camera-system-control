#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Servo.h>

Servo servo;
Adafruit_MPU6050 mpu;

float setpoint = 0, errorSum = 0, lastError = 0, angleX = 0;
float Kp, Ki, Kd;
float Ku = 2.5, Tu = 0.5; // parâmetros Ziegler Nichols: Ganho crítico (Ku) e período oscilatório (Tu)

unsigned long lastTime = 0;
const float alpha = 0.98;

void setup(void) {
  Serial.begin(115200);
  servo.attach(3);
  Wire.begin();
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) delay(10);
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("MPU6050 ready!");
  delay(100);
  lastTime = millis();

  // Ziegler-Nichols PID Tuning
  Kp = 0.6 * Ku;
  Ki = 2 * Kp / Tu;
  Kd = Kp * Tu / 8;
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float xAccel = a.acceleration.x, yAccel = a.acceleration.y, zAccel = a.acceleration.z;
  float accelAngleX = atan2(yAccel, sqrt(xAccel * xAccel + zAccel * zAccel)) * 180 / PI;

  unsigned long currentTime = millis();
  float deltaTime = (currentTime - lastTime) / 1000.0;
  lastTime = currentTime;

  float gyroRateX = g.gyro.x;
  float gyroAngleX = gyroRateX * deltaTime;

  angleX = alpha * (angleX + gyroAngleX) + (1.0 - alpha) * accelAngleX;

  float error = setpoint - angleX;
  errorSum += error * deltaTime;
  float dError = (error - lastError) / deltaTime;
  lastError = error;

  float pidOutput = Kp * error + Ki * errorSum + Kd * dError;

  int servoValue = map(pidOutput, -10, 10, 0, 180);
  servoValue = constrain(servoValue, 0, 180);
  servo.write(servoValue);

  Serial.print("Accel Angulo X: "); Serial.println(accelAngleX);
  Serial.print("Angulo X filtrado: "); Serial.println(anhuloX);
  Serial.print("PID Output: "); Serial.println(pidOutput);
  Serial.print("Servo: "); Serial.println(servoValue);

  delay(10);
}