//Programme maître: télécommande bluetooth du robot
#include <SoftwareSerial.h>
#define RX 10
#define TX 11
SoftwareSerial BTSerial(RX,TX);

int bouton=3;
int etat=0;

void setup() {
  // put your setup code here, to run once:
  BTSerial.begin(38400);
  Serial.begin(38400);
  pinMode(bouton,INPUT);
  Serial.println("Fin setup");

}

void loop() {
  // put your main code here, to run repeatedly:
  etat=digitalRead(bouton);
  delay(100);
  if (etat==0){
    BTSerial.print("A");
    BTSerial.print("\r\n");
    Serial.println(etat);
    
  }

}
