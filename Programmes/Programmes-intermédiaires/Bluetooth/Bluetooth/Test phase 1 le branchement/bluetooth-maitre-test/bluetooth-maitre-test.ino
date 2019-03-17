#include <SoftwareSerial.h>
#define RX 10
#define TX 11
SoftwareSerial BTSerial(RX,TX);

int bouton=3;
int etat;

void setup() {
  // put your setup code here, to run once:
  BTSerial.begin(38400);
  Serial.begin(38400);
  pinMode(bouton,INPUT);
  Serial.println("Fin setup");

}

void loop() {
          BTSerial.print("A");
          BTSerial.print("\r\n");
          Serial.println("A");
          delay(500);
          
  /*
        etat=digitalRead(bouton);
        
        if (etat==0){
          delay(20);
          Serial.println("Debug");
          BTSerial.print("A");
          BTSerial.print("\r\n");
          delay(20);
          
        }
*/
}
