#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();   // Initiates library.

#define SERVOMIN  100  // Minimum pulse length count out of 4096.
#define SERVOMAX  2200 // Maximum pulse length count out of 4096.

int servoNo = 0; // Defines a counter for servos.


void setup() 
{
  Serial.begin(9600);       // Starts serial connecton at 9600 baud rate.
  
  pwm.begin();         // Sends PWM signals.
  pwm.setPWMFreq(60);  // Makes servos run at 60 Hz rate.
  delay(20);
}


void loop() 
{   
  
  for (int pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) // Drives each servo one at a time first                                                                                                
    pwm.setPWM(servoNo, 0, pulselen);                            // to maximum pulse length then to minimum pulse length.
  delay(300);
  
  for (int pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--)
    pwm.setPWM(servoNo, 0, pulselen);
  delay(300);

  servoNo ++;            // Proceeds to next servo.
  if (servoNo > 3) servoNo = 0;
}