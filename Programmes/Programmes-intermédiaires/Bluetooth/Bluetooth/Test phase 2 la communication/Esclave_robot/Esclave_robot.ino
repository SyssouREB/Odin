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
  digitalWrite(led_rouge,HIGH);
  
  Serial.println("Je suis esclave");

}

void loop() {
  // put your main code here, to run repeatedly:
  if (BTSerial.available()) {
    etat = BTSerial.read();
    delay(100);
    Serial.println("Premier checkpoint");
    Serial.println(etat);
    if (etat == 'A'){
    digitalWrite(led_rouge,LOW);
    delay(1000);
    digitalWrite(led_rouge,HIGH);
    Serial.println("Deuxième checkpoint");
    }
  }
}
