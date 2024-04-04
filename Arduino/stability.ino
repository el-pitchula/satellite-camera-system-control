#include <Wire.h>
#include <MPU6050.h>
#include <Servo.h>

MPU6050 mpu;
Servo servoX, servoY, servoZ;

// Definições do PID
double Kp = 2.0;
double Ki = 0.5;
double Kd = 1.0;

double setpoint = 0.0;
double input, output;
double error, lastError = 0.0;
double integral = 0.0;
double derivative;

unsigned long lastTime;
double deltaTime = 0.01; // Intervalo de amostragem em segundos

void setup() {
  Wire.begin();
  mpu.initialize();

  servoX.attach(9);
  servoY.attach(10);
  servoZ.attach(11);

  lastTime = millis();
}

void loop() {
  unsigned long now = millis();
  double dt = (now - lastTime) / 1000.0;
  if (dt >= deltaTime) {
    lastTime = now;

    input = mpu.getAngleX(); // Obtenha o ângulo do giroscópio
    error = setpoint - input;

    integral += error * dt;
    derivative = (error - lastError) / dt;

    output = Kp * error + Ki * integral + Kd * derivative;

    // Aplique o controle de saída aos servos
    servoX.writeMicroseconds(1500 + output);
    servoY.writeMicroseconds(1500 + output);
    servoZ.writeMicroseconds(1500 + output);

    lastError = error;
  }
}
