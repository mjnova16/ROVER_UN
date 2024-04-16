#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver servos = Adafruit_PWMServoDriver(0x40);
unsigned int pos_0 = 102; // Calculo de pulsos para 0 grados
unsigned int pos_180 = 512; //Calculo de pulsos para 180 grados
const int servo_ch_1 = 0;// asignar el canal

#define N 2
#define CH1 A0
#define CH2 A1
//#define CH3 A2
int ch[N];

int velocidad = 3;
int Dir1A = 2;
int Dir1B = 4;
int Dir2A = 5;
int Dir2B = 6;
int aceleracion = 0;


void setup() {
  Serial.begin(9600);

  pinMode(Dir1A, OUTPUT);
  pinMode(Dir1B, OUTPUT);
  pinMode(Dir2A, OUTPUT);
  pinMode(Dir2B, OUTPUT);
  pinMode(velocidad, OUTPUT);

  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  //pinMode(CH3, INPUT);

  servos.begin();
  servos.setPWMFreq(50); //Frecuecia PWM de 60Hz

}

void loop() {
  ch[0] = pulseIn(CH1, HIGH); //Dirección (carrito: 990-1529-1945)435-205
  ch[1] = pulseIn(CH2, HIGH); //Velocidad
  //ch[2] = pulseIn(CH3, HIGH);

  Serial.print(ch[0]);
  Serial.print(",");
  Serial.println(ch[1]);
  //Serial.print(",");
 // Serial.println(ch[2]);



  if (ch[1] > 1580) {
    aceleracion = map(ch[1], 1580, 1885, 0, 255);
    MovAdelante();
  } else {
    MovAtras();
    aceleracion = map(ch[1], 1090, 1580, 255, 0);
  }
  aceleracion = map(ch[1], 1880, 1090, 0, 255);

  analogWrite(velocidad, aceleracion);

  servito(0, 205, 435, 0);
  servito(1, 205, 435, 0);
  servito(2, 435, 205, 7-0);
  servito(3, 435, 205, 0);

  
}//Fin


/* ====================================================================================================================


*/

void MovAdelante() {
  digitalWrite(Dir1A, 1);
  digitalWrite(Dir1B, 0);

  digitalWrite(Dir2A, 0);
  digitalWrite(Dir2B, 1);
}

void MovAtras() {
  digitalWrite(Dir1A, 0);
  digitalWrite(Dir1B, 1);

  digitalWrite(Dir2A, 1);
  digitalWrite(Dir2B, 0);
}

void MovDetener() {
  digitalWrite(Dir1A, 0);
  digitalWrite(Dir1B, 0);

  digitalWrite(Dir2A, 0);
  digitalWrite(Dir2B, 0);
}

void servito(int numero, int pos1, int pos2, int correct) {    //205-435
  int duty  
  ;
  duty = map(ch[0], 990, 1945, pos1, pos2);
  servos.setPWM(numero, 0, duty+correct);
 servos.setPWM(numero, 0,400 );
}
