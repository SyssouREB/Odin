#include<Servo.h>
#include<SoftwareSerial.h>
#define RX 2
#define TX 3
Servo servoVer;
Servo servoHor;
SoftwareSerial BlueT(RX,TX);
char scan=' ';
void scanner(){
  for(int j=150;j>=20;j=j-10){
    servoVer.attach(6);
    servoVer.write(j);
    for(int i=10;i<=150;i++){
      servoHor.attach(5);
      servoHor.write(i);
      delay(8);
      servoHor.detach();
    }
    j=j-10;
    servoVer.write(j);
    for(int i=150;i>=10;i--){
      servoHor.attach(5);
      servoHor.write(i);
      delay(8);
      servoHor.detach();
    }
    Serial.println(j);
    
    delay(8);
    servoVer.detach();
  }
  servoVer.attach(6);
  servoHor.attach(5);
  servoVer.write(90);
}
void setup() {
  servoVer.attach(6);
  servoHor.attach(5);
  Serial.begin(9600);
  servoVer.write(90);
  BlueT.begin(9600);
}

void loop() {
 /*while(Serial.available()){
  BlueT.write(char(Serial.read()));
 }*/
 while(BlueT.available()){
 scan=char(BlueT.read());
 }
 Serial.println(scan);
 for(int h=10;h<=150;h++){
      servoHor.write(h);
      delay(8);
      if(scan=='A'){
        scanner();
      }
    }
    for(int h=150;h>=10;h--){
      servoHor.write(h);
      delay(8);
       if(scan=='A'){
        scanner();
      } 
    }
  
}
