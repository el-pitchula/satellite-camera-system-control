#include <Wire.h>
#include <math.h>

#define TSAMPLE 50000

const int MPU = 0x68; // Endereco 12¢ do sensor

int AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ, GyZ2; // Dados Lidos dos sensores
unsigned long tempoAnterior  =0,  tempoAtual = 0; // Variaveis de tempo
float ang_accel; // Angulo calculado a partir do acelerémetro
static float ang_giro =0;int aux=0;

void deslocaVetor( float *vetorAddr, int tam, float valor)
{
	for(int k = tam-1;  k > 0; k--)
	{
 	*(vetorAddr  +  k) =  *(vetorAddr + k  - 1);
	}
	*vetorAddr = valor;
}

float filtro( float x, int f)
{
	static float y_pass[2] = {0,0},  x_pass[2] = {0,0};
	const float a = 0.75, b= 0.750;
	float y;
	if (f==0){// FILTRO PASSA BAIXA
		y = a*y_pass[1] + (1-a)*x_pass[1];
		deslocaVetor(y_pass,2 , y);
		deslocaVetor(x_pass, 2, x);
	}
	else{// FILTRO PASSA ALTA
		y = b*y_pass[1] + x_pass[0] - x_pass[1];
		deslocaVetor(y_pass,2 , y);
		deslocaVetor(x_pass, 2, x);
		}
		return y;
}

void setup()
{
Serial.begin( 9600) ;
Wire.begin();
Wire.beginTransmission(MPU) ;
Wire.write(0x6B) ;
Wire.write(0);
Wire. endTransmission( true) ;
}
 
void loop()
{
	tempoAtual = micros();
	if (tempoAtual - tempoAnterior >= TSAMPLE)
	{
	Wire. beginTransmission(MPU) ;
	Wire.write(0x3B) ;
	Wire. endTransmission( false) ;
	Wire.requestFrom(MPU, 14, true);
	AcX= Wire.read() << 8 | Wire.read();
	AcY = Wire.read() << 8 | Wire.read();
	AcZ= Wire.read() << 8 | Wire.read();
	Tmp = Wire.read() <<8 |Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
	GyX = Wire.read() << 8 | Wire.read();
	GyY = Wire.read() << 8 | Wire.read();
	GyZ = Wire.read() << 8 | Wire.read();

  ang_accel = atan2(-AcY, AcX) * 180 / PI;
	float velocidade= GyZ/131;
	Serial.print(filtro(velocidade, 0));Serial.print(" , ");
	Serial.print(filtro(velocidade, 1));Serial.print(" , ");
	Serial.println(velocidade);
	tempoAnterior = tempoAtual;
	}
}
