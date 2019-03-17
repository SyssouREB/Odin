#include<Servo.h>
#include<SoftwareSerial.h>
#define RX 7
#define TX 8
Servo servoVer;
Servo servoHor;
SoftwareSerial laser(RX,TX);
int byt[7];
int distance;
const int HEADER=0x59;
//////////////////////////////////////////////////
void laserfct(){ if(laser.available()){
    if((HEADER==laser.read()) && (HEADER==laser.read())){
        for(int i=0;i<7;i++){
          byt[i]=laser.read();
        }
        int check=0x59+0x59+byt[0]+byt[1]+byt[2]+byt[3]+byt[4]+byt[5];
        if(byt[6]==(check&0xff)){
          distance=byt[0]+byt[1]*256;
          Serial.println(distance);
        }
    }
        
  }
}
////////////////////////////////////////////////
void scanner(){
  for(int j=150;j>=20;j=j-10){
    servoVer.attach(6);
    servoVer.write(j);
    for(int i=10;i<=150;i++){
      servoHor.attach(5);
      servoHor.write(i);
      laserfct();
      delay(10);
      servoHor.detach();
    }
    j=j-10;
    servoVer.write(j);
    for(int i=150;i>=10;i--){
      servoHor.attach(5);
      servoHor.write(i);
      laserfct();
      delay(10);
      servoHor.detach();
    }
    delay(10);
    servoVer.detach();
  }
  servoVer.attach(6);
  servoHor.attach(5);
  servoVer.write(90);
}
////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void setup() {
  servoVer.attach(6);
  servoHor.attach(5);
  Serial.begin(250000);
  laser.begin(115200);
}

void loop() {
 laserfct();
 for(int h=10;h<=150;h++){
      servoHor.write(h);
      laserfct();
      delay(10);
    }
    laserfct();
    for(int h=150;h>=10;h--){
      servoHor.write(h);
      laserfct();
      delay(10);
    }
}
