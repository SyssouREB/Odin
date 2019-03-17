#include<SoftwareSerial.h>
#define RX 11
#define TX 10
SoftwareSerial Odin(RX,TX);
void setup() {
  // put your setup code here, to run once:
    Serial.begin(38400);
    delay(500);
    Serial.println("Hello, Reporting for duty sir!");
    Odin.begin(38400);
    delay(500);

}

void loop() {
  // put your main code here, to run repeatedly:
   while (Serial.available()){
    Odin.write(char(Serial.read()));
  }  
  while(Odin.available()){
    Serial.print(char(Odin.read())); 
  }
 
}
