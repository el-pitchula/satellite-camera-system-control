#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>
#include <utility/imumaths.h>
#include <math.h>
#include <Servo.h>

Servo pitchServo;
Servo rollServo;

float q0;
float q1;
float q2;
float q3;

float rollTarget=0;
float rollActual;
float rollError;
float rollServoVal=90;

float pitchTarget=0;
float pitchActual;
float pitchError;
float pitchServoVal=90;

#define MPU6050_SAMPLERATE_DELAY_MS (100)
Adafruit_MPU6050 mpu;

void setup() {
    Serial.begin(115200);
    mpu.begin();
    delay(1000);
    mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
    mpu.setGyroRange(MPU6050_RANGE_250_DEG);
    rollServo.attach(2);
    pitchServo.attach(3);

    rollServo.write(rollServoVal);
    delay(20);
    pitchServo.write(pitchServoVal);
    delay(20);
}

void loop() {
    sensors_event_t accel, gyro;
    mpu.getEvent(&accel, &gyro);
    
    imu::Quaternion quat = mpu.getQuaternion();

    q0 = quat.w();
    q1 = quat.x();
    q2 = quat.y();
    q3 = quat.z();

    rollActual = atan2(2 * (q0 * q1 + q2 * q3), 1 - 2 * (q1 * q1 + q2 * q2));
    pitchActual = asin(2 * (q0 * q2 - q3 * q1));

    rollActual = rollActual / (2 * 3.141592654) * 360;
    pitchActual = pitchActual / (2 * 3.141592654) * 360;

    rollError = rollTarget - rollActual;
    pitchError = pitchTarget - pitchActual;

    if (pitchError > 1.5) {
        pitchServoVal = pitchServoVal + 1;
        pitchServo.write(pitchServoVal);
        delay(20);
    }
    if (pitchError < -1.5) {
        pitchServoVal = pitchServoVal - 1;
        pitchServo.write(pitchServoVal);
        delay(20);
    }

    if (rollError > 1.5) {
        rollServoVal = rollServoVal + 1;
        rollServo.write(rollServoVal);
        delay(20);
    }
    if (rollError < -1.5) {
        rollServoVal = rollServoVal - 1;
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
    Serial.print(accel.acceleration);
    Serial.print(",");
    Serial.print(gyro.gyro);
    Serial.print(",");
    Serial.print(0); // mg not available in MPU6050
    Serial.print(",");
    Serial.println(0); // system not available in MPU6050

    delay(MPU6050_SAMPLERATE_DELAY_MS);
}