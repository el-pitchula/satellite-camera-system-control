//lembrar enviar os documentos das bibliotecas
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Servo.h>

Servo servo;
Adafruit_MPU6050 mpu;

float setpoint = 0;
float errorSum = 0; //soma dos erros acumulados
float lastError = 0;
float Kp = 2.2;  // 1.6 0.2 0.1 ou 2.2 0.001 0.003 tmb podem funcionar
float Ki = 0.002;
float Kd = 0.001;
unsigned long lastTime = 0;

//para o filtro
float alpha = 0.98; //suavização
float angleY = 0; //ângulo filtrado

void setup(void) {
  Serial.begin(115200);
  servo.attach(3);
  Wire.begin();
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  
  Serial.println("MPU6050 ready!");
  
  delay(100);
  lastTime = millis();
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  //obtem a aceleração nos eixos X, Y e Z
  float xAccel = a.acceleration.x;
  float yAccel = a.acceleration.y;
  float zAccel = a.acceleration.z;
  
  //calcula o ângulo com base na aceleração
  float accelAngleY = atan2(xAccel, sqrt(yAccel * yAccel + zAccel * zAccel)) * 180 / PI;

  //tempo decorrido
  unsigned long currentTime = millis();
  float deltaTime = (currentTime - lastTime) / 1000.0;
  lastTime = currentTime;

  //calculo do ângulo com base no giroscópio
  float gyroRateY = g.gyro.y;
  float gyroAngleY = gyroRateY * deltaTime;

  //filtro complementar
  angleY = alpha * (angleY + gyroAngleY) + (1.0 - alpha) * accelAngleY;

  //erro
  float error = setpoint - angleY;
  errorSum += error * deltaTime;
  float dError = (error - lastError) / deltaTime;

  //a saída do PID
  float pidOutput = Kp * error + Ki * errorSum + Kd * dError;

  //ajusta a posição do servo
  int servoValue = map(pidOutput, -10, 10, 0, 180); // de -10 a 10 graus (sensibilidade)
  servoValue = constrain(servoValue, 0, 180);
  servo.write(servoValue);

  Serial.print("Accel Angle Y: "); Serial.println(accelAngleY);
  Serial.print("Filtered Angle Y: "); Serial.println(angleY);
  Serial.print("PID Output: "); Serial.println(pidOutput);
  Serial.print("Servo: "); Serial.println(servoValue);

  //plotter
  Serial.print(accelAngleY); Serial.print(",");
  Serial.print(angleY); Serial.print(",");
  Serial.print(pidOutput); Serial.print(",");
  Serial.println(servoValue);

  delay(10); //suavidade da resposta
}
