//Programme maître: télécommande bluetooth du robot
#include <SoftwareSerial.h>
#include<math.h>
//Pourl e bluetooth
#define RX 5
#define TX 3
SoftwareSerial BTSerial(RX,TX);
int bouton_avant=4;
int bouton_gauche=2;
int bouton_droite=7;
int bouton_scan=6;
char BT;
float k;
float l;

//Pour l'écran
char printout[4];
#include <TFT.h>
#include <SPI.h>


#define TFT_CS     10
#define TFT_RST    9  
#define TFT_DC     8

#define TFT_SCLK 13 
#define TFT_MOSI 11   

TFT screen=TFT(TFT_CS,TFT_DC,TFT_RST);//mise en place de l'écran

void setup() {
  // put your setup code here, to run once:
  BTSerial.begin(38400);
  Serial.begin(38400);
  pinMode(bouton_avant,INPUT);
  pinMode(bouton_gauche,INPUT);
  pinMode(bouton_droite,INPUT);
  pinMode(bouton_scan,INPUT);
  screen.begin();
  screen.background(0,0,0);
  screen.stroke(254,0,0);
  screen.text("Fin setup",1,1);
  delay(1000);
  screen.background(0,0,0);
  Serial.println("Fin setup");
}
//Fonction qui affiche les points scanner en couleurs selon la distance
void couleur(float k){ 
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
}


void loop() {
  // put your main code here, to run repeatedly:
  int etat_avant=digitalRead(bouton_avant);
  delay(20);
  int etat_gauche=digitalRead(bouton_gauche);
  delay(20);
  int etat_droite=digitalRead(bouton_droite);
  delay(100);
  //Dis au robot d'aller vers l'avant
  if (etat_avant == 0){
    BTSerial.print("Z");
    BTSerial.print("\r\n");  
    Serial.println("1");
  }
  //Dis au robot d'aller vers la gauche
  else if (etat_gauche == 0){
    BTSerial.print("Q");
    BTSerial.print("\r\n");
    Serial.println("2");
  }
  //Dis au robot d'aller vers la droite
  else if (etat_droite == 0){
    BTSerial.print("D");
    BTSerial.print("\r\n");
    Serial.println("3");
  }       
  //Lorsque le robot envoie une information
  while(BTSerial.available()){
       BT=char(BTSerial.read());
       screen.background(0,0,0);
       
       Serial.println(BT);
       //Le robot a atteint un obstacle et fait une pause de 5 secondes
       if (BT=='P'){
        //On laisse 5 secondes à l'utilisateur pour appuyer sur le bouton
        Serial.println("J'ai reçus P");
        screen.stroke(255,0,0);
        screen.text("Appuyez sur le bouton scan",1,1);
        screen.text("Pour scanner l'objet",1,20);
        float temps=millis();
        float currentmillis=millis();
        while((currentmillis-temps)/1000<5){
          int etat_scan=digitalRead(bouton_scan);
          delay(10); //delaie pour éviter un rebond du bouton
          //L'utilisateur a appuyé sur le bouton
          if (etat_scan == 0){
            //On dit au robot de commencer à scanner
            currentmillis=temps+10000;
            BTSerial.print("S");
            BTSerial.print("\r\n");
            delay(1000);
            Serial.println("Etat=1");
          }
          currentmillis=millis();
         }
         screen.background(0,0,0);
        }
        //Si le rebot commence à scanner, le dessin se fait
        if (BT=='D'){
          //Double boucle for pour dessiner sur chaque pixel
          Serial.println("J'ai recus D");
          for(int j=110;j>=50;j--){
            for(int i=40;i<=120;i+=1){
              //On récupère la distance du scanner
              BT=BTSerial.parseInt();
              k=sin((float)j*PI/180)*sin((float)i*PI/180)*BT;
              couleur(k); //donne la couleur au point en fonction de la distance
              screen.point(i,j);// dessin du point aux coordonnées x,y
            }
            j-=1;
            for(int i=120;i>=40;i--){
              BT=BTSerial.parseInt();
              l=sin((float)j*PI/180)*sin((float)i*PI/180)*BT;
              couleur(l);
              screen.point(i,j);
            }       
          }
        }
     }
  
}
