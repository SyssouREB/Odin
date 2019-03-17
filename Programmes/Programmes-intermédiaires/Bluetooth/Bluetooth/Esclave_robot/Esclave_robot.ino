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

void loop() {
  // put your main code here, to run repeatedly:
  if (BTSerial.available()) {
    Serial.println("Debug 1");
    etat = BTSerial.read();
    if ((char)etat == "A"){
      Serial.println("Debug 2");
      digitalWrite(led_rouge,HIGH);
    }
  }
  delay(20);
  digitalWrite(led_rouge,HIGH);
}
