#include<SoftwareSerial.h> 
#define RX 2
#define TX 3
SoftwareSerial BlueT(RX,TX);

void bt(){
   while (BlueT.available()) {
Serial.print(char(BlueT.read())); } 
}
void setup() {
  Serial.begin(250000); 
  delay(500); 
  Serial.println("Bonjour -Pret pour les commandes AT"); 
  BlueT.begin(9600); 
  delay(500);
}

void loop() {

//while (Serial.available()) {
  //BlueT.write(char(Serial.read())); }

bt();
}
