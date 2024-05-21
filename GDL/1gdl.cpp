#include "Wire.h"
#include "I2Cdev.h" 
#include "MPU6050.h" 
#include "Servo.h" 

MPU6050 mpu; 
int16_t ax, ay, az; 
int16_t gx, gy, gz; 
Servo servo1; 
Servo servo2;

int val1; 
int val2; 
int prevVal1; 
int prevVal2; 

void setup() 
{ 
  Wire.begin(); 
  Serial.begin(38400); 
  Serial.println("Initialize MPU"); 
  mpu.initialize(); 
  Serial.println(mpu.testConnection() ? "Connected" : "Connection failed"); 
  servo1.attach(9); 
  servo2.attach(10);
} 

void loop() 
{ 
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); 
  val1 = map(ax, -17000, 17000, 0, 179); 
  if (val1 != prevVal1) 
  { 
    servo1.write(val1); 
    prevVal1 = val1; 
  } 
  val2 = map(ay, -17000, 17000, 0, 179); 
  if (val2 != prevVal2) 
  { 
    servo2.write(val2); 
    prevVal2 = val2; 
  } 
  delay(50); 
}

//add o filtro complementar
//mostrar mais sinais no serial e plotter (comparação filtro e PID)
//provavelmente será apenas para X ou um eixo (ainda ñ tenho certeza)

/*

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Servo.h>

Servo servo;
Adafruit_MPU6050 srituhobby;

void setup(void) {
  Serial.begin(115200);
  servo.attach(3);
  Wire.begin();
  srituhobby.begin();
  servo.write(0);

  srituhobby.setAccelerometerRange(MPU6050_RANGE_8_G);//2_G,4_G,8_G,16_G
  srituhobby.setGyroRange(MPU6050_RANGE_500_DEG);//250,500,1000,2000
  srituhobby.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);
}

void loop() {

  // Get new sensor events with the readings
  sensors_event_t a, g, temp;
  srituhobby.getEvent(&a, &g, &temp);

  int value = a.acceleration.y;

  value = map(value,  -10, 10, 180, 0);
  servo.write(value);  
  Serial.println(value);
  delay(1000);
}

*/

/*
// c/filtro complementar

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Servo.h>

Servo servo;
Adafruit_MPU6050 mpu;

// Variáveis do filtro complementar
float angleY = 0;
float alpha = 0.98; // Fator de suavização do filtro complementar
unsigned long lastTime = 0;

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
  
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G); // 2_G, 4_G, 8_G, 16_G
  mpu.setGyroRange(MPU6050_RANGE_500_DEG); // 250, 500, 1000, 2000
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  
  Serial.println("MPU6050 ready!");
  
  delay(100);
  lastTime = millis();
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Obter a aceleração nos eixos X, Y e Z
  float xAccel = a.acceleration.x;
  float yAccel = a.acceleration.y;
  float zAccel = a.acceleration.z;
  
  // Calcular o ângulo com base na aceleração
  float accelAngleY = atan2(xAccel, sqrt(yAccel * yAccel + zAccel * zAccel)) * 180 / PI;

  // Calcular o tempo decorrido
  unsigned long currentTime = millis();
  float deltaTime = (currentTime - lastTime) / 1000.0;
  lastTime = currentTime;

  // Calcular o ângulo com base no giroscópio
  float gyroRateY = g.gyro.y;
  float gyroAngleY = gyroRateY * deltaTime;

  // Aplicar o filtro complementar
  angleY = alpha * (angleY + gyroAngleY) + (1.0 - alpha) * accelAngleY;

  // Inverter o ângulo para o servo motor para manter o equilíbrio
  float invertedAngleY = angleY; // Remova o sinal de menos para mover no sentido contrário

  // Aumentar a faixa de mapeamento para aumentar a movimentação do servo
  int servoValue = map(invertedAngleY, -10, 10, 180, 0); // Ajuste de -90 a 90 graus para aumentar a sensibilidade
  servoValue = constrain(servoValue, 0, 180);

  // Mover o servo para a posição calculada
  servo.write(servoValue);

  // Printar os valores para debug
  Serial.print("Accel Angle Y: "); Serial.print(accelAngleY);
  Serial.print(" -> Filtered Angle Y: "); Serial.print(angleY);
  Serial.print(" -> Inverted Angle Y: "); Serial.print(invertedAngleY);
  Serial.print(" -> Servo: "); Serial.println(servoValue);

  delay(10); // Ajuste o delay conforme necessário para a suavidade da resposta
}


*/