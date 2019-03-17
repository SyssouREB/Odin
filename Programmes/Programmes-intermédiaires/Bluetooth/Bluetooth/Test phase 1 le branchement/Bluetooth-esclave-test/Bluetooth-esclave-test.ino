
#include <SoftwareSerial.h>
#define RX 10
#define TX 11
SoftwareSerial BTSerial(RX, TX); // RX 10   TX 11

int led_rouge=3;
char etat;


void setup() {
  Serial.begin(38400);
  BTSerial.begin(38400);//démarre la liaison avec module bluetooth
  pinMode(led_rouge,OUTPUT);
  digitalWrite(led_rouge,LOW);
  
  Serial.println("Je suis esclave");

}

void loop() {//boucle infinie
  delay(500);
  //if (BTSerial.available()>0) {// tant que bluetooth recoit de nouvelles informations
   //Serial.print("Debug");
   etat = BTSerial.read();
   Serial.println(char(etat));
  
    if (etat=="A") {
      digitalWrite(led_rouge,HIGH);
      //} 
     
    }
}//fin void loop  
