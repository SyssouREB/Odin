/*
* 
*/

//-- MOTEUR A -
int ENA=11; //Connecté à Arduino pin (sortie PWM) 
int IN1=13; //Connecté à Arduino pin  
int IN2=12; //Connecté à Arduino pin 
//-- MOTEUR B -
int ENB=10; //Connecté à Arduino pin (Sortie PWM) 
int IN3=; //Connecté à Arduino pin  
int IN4=; //Connecté à Arduino pin

int PWM=0;
char DATA;

#include<SoftwareSerial.h>
#define RX 
#define TX 
SoftwareSerial Odin(RX,TX);

void setup() {
  Odin.begin(9600);
    delay(500);
    pinMode(ENA,OUTPUT); // Configurer 
    pinMode(ENB,OUTPUT); // les broches 
    pinMode(IN1,OUTPUT);
    pinMode(IN2,OUTPUT); 
    pinMode(IN3,OUTPUT); 
    pinMode(IN4,OUTPUT); 
    digitalWrite(ENA,LOW);// Moteur A - Ne pas tourner 
    digitalWrite(ENB,LOW);// Moteur B - Ne pas tourner

}

void loop() {
  // put your main code here, to run repeatedly:
  if (Odin.available()){
    DATA=char(Odin.read());
    if (DATA=='Z'){
      digitalWrite(ENA,0);
      digitalWrite(ENB,0);
    }
    if (DATA=='D'){
      digitalWrite(ENA,0);
      digitalWrite(ENB,125);
    }
    if (DATA=='Q'){
      digitalWrite(ENA,125);
      digitalWrite(ENB,0);
    }
    if (DATA=='S'){
      digitalWrite(ENA,PWM);
      digitalWrite(ENB,PWM);
    }
    if (DATA='v'){
      PWM=Odin.parseInt();
    }
  }

}
