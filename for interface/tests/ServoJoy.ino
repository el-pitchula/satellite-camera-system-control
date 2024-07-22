#include <Servo.h> //Inclui biblioteca para servo motor

const int SW = 2; // Pino para o botão do joystick
const int PIN_SERVO = 9; // Pino de comandos para o servo motor
const int VRY = A4; // Pino para leitura do eixo Y
const int VRX = A5; // Pino para leitura do eixo X

const int CLOSE = 170; // Limite de fechamento do servo
const int OPEN = 90; // Limite de abertura do servo

int leitura_vrx; // Variável de armazenamento do Eixo X
int leitura_vry; // Variável de armazenamento do Eixo Y
int leitura_sw; // Variável de armazenamento da leitura do botão
int posi_atual = 520; // Variável de referência
boolean abrir = 0; // Variável de sentido.
boolean fechar = 0; // Variável de sentido.

Servo servo_motor;

void setup() {
  pinMode(VRX, INPUT);
  pinMode(VRY, INPUT);
  pinMode(SW, INPUT_PULLUP);
  servo_motor.attach(PIN_SERVO);
}

void loop() {

  leitura_vry = analogRead(VRY);
  leitura_vrx = analogRead(VRX);
  leitura_vrx = map(leitura_vrx, 0, 1023, CLOSE, OPEN);  // Converte valor do potenciometro
  servo_motor.write(leitura_vrx); // Aciona servo motor, com base na leitura do eixo x
  delay(10);
  //Verificação da posição do joytick
  if (leitura_vry >= 550) {
    abrir = 1; // Seta a flag caso o movimento do joystick indicar uma tendencia de abertura
  }
  else if (leitura_vry <= 490) {
    fechar = 1; // Seta a flag caso o movimento do joystick indicar uma tendencia de fechamento
  }
  while (abrir == 1) { // Executa os comando que estiverem dentro das chaves
    leitura_vry = analogRead(VRY);
    leitura_sw = digitalRead(SW);

    if (leitura_sw == HIGH) { // Verifica o botão
      // Verifica a posição da garra
      if (leitura_vry > posi_atual) { // Se a posição da garra for maior que a posição anterior
        posi_atual = leitura_vry; // Atualiza a varivel de posição
        leitura_vry = map(leitura_vry, 0, 1023, CLOSE, OPEN);
        servo_motor.write(leitura_vry);
      }
    }
    // Atualiza a flag e a posiçao da garra se o botao for pressionado
    else {
      abrir = 0;
      posi_atual = 520;
    }
  }

  while (fechar == 1) { // Executa os comando que estiverem dentro das chaves
    leitura_vry = analogRead(VRY);
    leitura_sw = digitalRead(SW);

    if (leitura_sw == HIGH) { // Verifica o botão
      // Verifica a posição da garra
      if (leitura_vry < posi_atual) { // Se a posição da garra for maior que a posição anterior
        posi_atual = leitura_vry; // Atualiza a varivel de posição
        leitura_vry = map(leitura_vry, 0, 1023, CLOSE, OPEN);
        servo_motor.write(leitura_vry);
      }
    }
    // Atualiza a flag e a posiçao da garra se o botao for pressionado
    else {
      fechar = 0;
      posi_atual = 520;
    }
  }
}