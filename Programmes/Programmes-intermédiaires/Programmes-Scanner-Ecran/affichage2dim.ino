#include<Servo.h>
#include<math.h>
#include<SoftwareSerial.h>
#define RX 7
#define TX 8
#define RXb 2
#define TXb 3
Servo servoVer;
Servo servoHor;
char scan=' ';
int byt[9];
int distance;
const int HEADER=0x59;
char printout[4];
#include <TFT.h>
#include <SPI.h>


#define TFT_CS     10
#define TFT_RST    9  
#define TFT_DC     8

#define TFT_SCLK 52   
#define TFT_MOSI 51   

TFT screen=TFT(TFT_CS,TFT_DC,TFT_RST);//mise en place de l'écran

//////////////////////////////////////////////////
int laserfct(){
    if(Serial2.available()){//vérifie que le laser possède des données
       for(int i=0;i<9;i++){//lecture des 9 bytes envoyé par le laser
          byt[i]=Serial2.read();//lit les 8 bytes et les place dans un tableau
          
        }
    if((HEADER==byt[0]) && (HEADER==byt[1])){//vérifie les 2 premiers bytes
       
        int check=byt[0]+byt[1]+byt[2]+byt[3]+byt[4]+byt[5]+byt[6]+byt[7];//variable qui va vérifier le bon fonctionnement du laser et si les données recu sont bonnes
        if(byt[8]==(check&0xff)){
          distance=byt[2]+byt[3]*256;//calcul de la distance
          return distance;//retour de la distance
        }
    }
        
  }
  return;
}
////////////////////////////////////////////////

////////////////////////////////////////////////
void scanner(){ //fonction permettant de scanner
  Serial2.begin(115200);
  float k=0;
  float l=0;
  for(int j=110;j>=50;j--){//boucle pour le servo verticale
    servoVer.attach(6);// permet d'attacher le servo verticale au port lui correspondant
    servoVer.write(j);
    for(int i=40;i<=120;i+=1){//boucle pour le servo horizontale aller
      servoHor.attach(5);
      servoHor.write(i);
      Serial2.end();
      Serial2.begin(115200);
      delay(10);
      k=sin((float)j*PI/180)*sin((float)i*PI/180)*laserfct();
      Serial.println(k);
      if((k<60)&&(k>=40)){// si la distance est inférieur a 30cm active la couleur
        screen.stroke(255-k,0,0);
      }
      else if((k<40)&&(k>=30)){
        screen.stroke(0,255-k,255-k);
      }
       else if((k<30)&&(k>=20)){
        
        screen.stroke(0,165-k,255-k);
      }
      else if((k<20)&&(k>0)){
        screen.stroke(0,0,255-k);
      }
      else{
        screen.stroke(0,0,0);
      }
      screen.point(i,j);// dessin du point aux coordonnées x,y
      delay(10);
      servoHor.detach();
    }
    j=j-1;
    servoVer.write(j);
    for(int i=120;i>=40;i--){// 2ème boucle pour le servo horizontale retour
      servoHor.attach(5);
      servoHor.write(i);
      Serial2.end();
      Serial2.begin(115200);
      delay(10);
      l=sin((float)j*PI/180)*sin((float)i*PI/180)*laserfct();
      Serial.println(l);
     if((l<60)&&(l>=40)){// si la distance est inférieur a 30cm active la couleur
        screen.stroke(255-l,0,0);
      }
      else if((l<40)&&(l>=30)){
        screen.stroke(0,255-l,255-l);
      }
       else if((l<30)&&(l>=20)){
        
        screen.stroke(0,165-l,255-l);
      }
      else if((l<20)&&(l>0)){
        screen.stroke(0,0,255-l);
      }
      else{
        screen.stroke(0,0,0);
      }
      screen.point(i,j);
      delay(10);
      servoHor.detach();
    }
    delay(10);
    servoVer.detach();//permet de détacher le servo verticale de son port (plus de fluifité)
  }
  servoVer.attach(6);
  servoHor.attach(5);
  servoVer.write(90);
  delay(3000);
  screen.background(0,0,0);
}
//////////////////////
bool scanBT(){// fonction pour le bluetooth

   while(Serial3.available()){// si le bluetooth recoit quelque chose faire la suite
 scan=char(Serial3.read());// lit la lettre recu par le bluetooth
 }
if(scan=='A'){// lance scanner si le bluetooth recoit la lettre A
        scanner();
        scan="E";
        return true;
      }
else{return false;}
}
///////////////////////////////////////////////////////////
void setup() {
  servoVer.attach(6);
  servoHor.attach(5);
  Serial.begin(250000);
  Serial2.begin(115200);
  Serial3.begin(9600);
  screen.begin();//allume l'écran
  screen.background(0,0,0);//met le fond en noir
}

void loop() {
 int temps=millis();
 int k;
 int currentmillis=millis();
 Serial.println(laserfct());// fonction laser qui print les valeurs ddistances
 for(int h=10;h<=150;h++){// boucles for afin de déplacer le servo horizontale de gauche à droite
      servoHor.write(h);
      k=laserfct();
      scanBT();// appel de la fonction bluetooth a chaque boucle afin de recevoir l'information pour lancer scanner
      delay(10);
      if((k<50)&&(k>10)){
        Serial.println("cc");
        Serial2.end();
        temps=millis();
        currentmillis=millis();
        while((currentmillis-temps)/1000<5){
          if(scanBT()){
            temps=millis();
          }
          currentmillis=millis();
          screen.stroke(255,0,255);
          screen.setTextSize(1);
          screen.text("Appuyez sur le bouton rouge",1,1);
          int t=(currentmillis-temps)/1000;
          String ts=String(t);
          ts.toCharArray(printout,4);
          screen.text(printout,1,30);
          delay(1000);
          screen.background(0,0,0);
        }
      temps=millis();
      currentmillis=millis();
      while((currentmillis-temps)/1000<=5){
             currentmillis=millis();
      }
      Serial2.begin(115200);
      }
      Serial.println(k);
      delay(5);
     
      
    }
Serial.println(laserfct());
  for(int h=150;h>=10;h--){// boucles for afin de déplacer le servo horizontale de droite à gauche
      servoHor.write(h);
      scanBT();
      k=laserfct();
      delay(10);
      if((k<60)&&(k>10)){
        Serial2.end();
                Serial.println("cc");
        temps=millis();
        currentmillis=millis();
        while((currentmillis-temps)/1000<5){
          if(scanBT()){
            temps=millis();
          }
          currentmillis=millis();
          screen.stroke(255,0,255);
          screen.setTextSize(1);
          screen.text("Appuyez sur le bouton rouge",1,1);
          int t=(currentmillis-temps)/1000;
          String ts=String(t);
          ts.toCharArray(printout,4);
          screen.text(printout,1,30);
          delay(1000);
          screen.background(0,0,0);
        }
      temps=millis();
      currentmillis=millis();
      while((currentmillis-temps)/1000<=5){
             currentmillis=millis();
      }
      Serial2.begin(115200);
      }
      Serial.println(k);
      delay(5);
    }
}
