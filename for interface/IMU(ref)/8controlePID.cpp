#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <math.h>
#include <Servo.h>

Servo pitchServo;
Servo rollServo;

float q0;
float q1;
float q2;
float q3;

float k1=.5;
float k2=55;
float k3=.00001;

int milliOld;
int milliNew;
int dt;

float rollTarget=0;
float rollActual;
float rollError=0;
float rollErrorOld;
float rollErrorChange;
float rollErrorSlope=0;
float rollErrorArea=0;
float rollServoVal=90;

float pitchTarget=0;
float pitchActual;
float pitchError=0;
float pitchErrorOld;
float pitchErrorChange;
float pitchErrorSlope=0;
float pitchErrorArea=0;
float pitchServoVal=90;

#define BNO055_SAMPLERATE_DELAY_MS (100)
Adafruit_BNO055 myIMU = Adafruit_BNO055();

void setup() {
    Serial.begin(115200);
    myIMU.begin();
    delay(1000);
    int8_t temp=myIMU.getTemp();
    myIMU.setExtCrystalUse(true);
    rollServo.attach(2);
    pitchServo.attach(3);

    rollServo.write(rollServoVal);
    delay(20);
    pitchServo.write(pitchServoVal);
    delay(20);

    milliNew=millis();
}

void loop() {
    uint8_t system, gyro, accel, mg = 0;
    myIMU.getCalibration(&system, &gyro, &accel, &mg);

    imu::Quaternion quat=myIMU.getQuat();

    q0=quat.w();
    q1=quat.x();
    q2=quat.y();
    q3=quat.z();

    rollActual=atan2(2*(q0*q1+q2*q3),1-2*(q1*q1+q2*q2));
    pitchActual=asin(2*(q0*q2-q3*q1));

    rollActual=rollActual/(2*3.141592654)*360;
    pitchActual=pitchActual/(2*3.141592654)*360;

    milliOld=milliNew;
    milliNew=millis();
    dt=milliNew-milliOld;

    rollErrorOld=rollError;
    rollError=rollTarget-rollActual;
    rollErrorChange=rollError-rollErrorOld;
    rollErrorSlope=rollErrorChange/dt;
    rollErrorArea=rollErrorArea+rollError*dt;

    pitchErrorOld=pitchError;
    pitchError=pitchTarget-pitchActual;
    pitchErrorChange=pitchError-pitchErrorOld;
    pitchErrorSlope=pitchErrorChange/dt;
    pitchErrorArea=pitchErrorArea+pitchError*dt;

    rollServoVal=rollServoVal+k1*rollError+k2*rollErrorSlope+k3*rollErrorArea;
    rollServo.write(rollServoVal);

    pitchServoVal=pitchServoVal+k1*pitchError+k2*pitchErrorSlope+k3*pitchErrorArea;
    pitchServo.write(pitchServoVal);

    Serial.print(rollTarget);
    Serial.print(",");
    Serial.print(rollActual);
    Serial.print(",");
    Serial.print(pitchTarget);
    Serial.print(",");
    Serial.print(pitchActual);
    Serial.print(",");
    Serial.print(accel);
    Serial.print(",");
    Serial.print(gyro);
    Serial.print(",");
    Serial.print(mg);
    Serial.print(",");
    Serial.println(system);

    delay(BNO055_SAMPLERATE_DELAY_MS);
}