#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <math.h>

#define BNO055_SAMPLERATE_DELAY_MS (100) //taxa de amostragem e atraso de 100 ms
Adafruit_BNO055 myIMU = Adafruit_BNO055();

float thetaM; //medido
float phiM;
float thetaFold=0; //first
float thetaFnew;
float phiFold=0;
float phiFnew;

void setup() {
  Serial.begin(115200);
  myIMU.begin();
  delay(1000);
  int8_t temp=myIMU.getTemp();//armazena dado compacto
  //Serial.printIn(temp);
  myIMU.setExtCrystalUse(true);
}

void loop() {
  uint8_t system, gyro, accel, mg = 0; //variável para calibração
  myIMU.getCalibration(&system, &gyro, &accel, &mg);

  imu::Vector<3> acc = myIMU.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
      //3 componentes (para pegar os dados do aceletrômetro)

  //imu::Vector<3> gyro = myIMU.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  //imu::Vector<3> mag = myIMU.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
      //agora são 3 conjuntos de dados (ou seja, 9 pontos de dados)

  thetaM=-atan2(acc.x()/9.8,acc.z()/9.8)/2/3.141592654*360; //fórmula arctg (-1)
      //normalização do vetor pra g e 
      //theta em radianos para graus (cuz full circle is 2pi)
      // -atan2() is lil better (testei positive)
  phiM=atan2(acc.y()/9.8,acc.z()/9.8)/2/3.141592654*360;

  thetaFnew=.9*thetaFold+.1*thetaM; // 0.9(90%) e 0.1(10%)
  phiFnew=.9*phiFold+.1*phiM; // .75 e .25 pode ser mais responsivo

  Serial.print(acc.x()/9.8); // /9.8 da normalização para gravidade
  Serial.print(",");
  Serial.print(acc.y()/9.8);
  Serial.print(",");
  Serial.print(acc.z()/9.8);
  Serial.print(",");
  /*
  Serial.print(gyro.x());
  Serial.print(",");
  Serial.print(gyro.y());
  Serial.print(",");
  Serial.print(gyro.z());
  Serial.print(",");

  Serial.print(mag.x());
  Serial.print(",");
  Serial.print(mag.y());
  Serial.print(",");
  Serial.println(mag.z());
  */

  Serial.print(accel);
  Serial.print(",");
  Serial.print(gyro);
  Serial.print(",");
  Serial.print(mg);
  Serial.print(",");

  Serial.print(system);
  Serial.print(",");
  
  Serial.print(thetaM);
  Serial.print(",");
  Serial.print(phiM);

  Serial.print(thetaFnew);
  Serial.print(",");
  Serial.println(phiFnew);

  phiFold=phiFnew; // p/dar loop
  thetaFold=thetaFnew;

  delay(BNO055_SAMPLERATE_DELAY_MS);
}


/*
- serial
- plotter
- calibração (ax, gy e mg)
- editar pra estar no hackaday.io (SerialPlot)
- modelagem 3d em python (ao invés do processing)

- estrutura de dados/redes
- arquitetura de software
*/