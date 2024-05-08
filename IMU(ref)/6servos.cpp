#include <Servo.h>

Servo panServo; //panoram (servo1)
Servo tiltServo; //inclinação (servo2)
int pos=0; //posição inicial

void setup() {
    panServo.attach(2); //pin 2
    tiltServo.attach(3); //pin 3
    //panServo.write(90); //90°
    //tiltServo.write(90);
}

void loop() {
    for (pos=0; pos<=180; pos=pos+1){ //ordens de giro (alterar pra teste)
        panServo.write(pos);
        delay(15);
    }
    for (pos=180; pos>=0; pos=pos-1){ // vai e volta 180°
        panServo.write(pos);
        delay(15);
    }
    for (pos=0; pos<=180; pos=pos+1){ //para o outro servo (tilt)
        tiltServo.write(pos);
        delay(15);
    }
    for (pos=180; pos<=0; pos=pos-1){
        tiltpanServo.write(pos);
        delay(15);
    }
}
