#include<SoftwareSerial.h>
#define RX1 7
#define TX1 8
SoftwareSerial laser(RX1,TX1);
int byt[7];
int distance;
const int HEADER=0x59;

int laserfct(){ if(laser.available()){
    if((HEADER==laser.read()) && (HEADER==laser.read())){
        for(int i=0;i<7;i++){
          byt[i]=laser.read();
        }
        int check=0x59+0x59+byt[0]+byt[1]+byt[2]+byt[3]+byt[4]+byt[5];
        if(byt[6]==(check&0xff)){
        distance=byt[0]+byt[1]*256;
        return distance;
        }
    }
        
  }
}
  
void setup() {
  Serial.begin(250000);
  laser.begin(115200);
}

void loop() {
 Serial.println(laserfct());
}
