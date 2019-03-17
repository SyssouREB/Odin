#include <SoftwareSerial.h>
#include<Servo.h>
#include<math.h>
int etat_dep=1;// varible d'état pour les boutons
Servo servoVer;// variable pour le servomoteur vertical
Servo servoHor;// variable pour le servomoteur horizontal
char scan=' ';
int byt[9];
int distance;
const int HEADER=0x59;

char etat;// varible d'état pour les boutons
int k;// varible pour la distance
int l;// varible pour la distance
char c;// varible pour lire le bluetooth
float temps;//variable de temps
float currentmillis;//variable de temps
//////////////////////////////////////////////////
int laserfct(){
    if(Serial2.available()){//vérifie que le laser possède des données
       for(int i=0;i<9;i++){//lecture des 9 bytes envoyé par le laser
          byt[i]=Serial2.read();//lit les 9 bytes et les place dans un tableau
        }
    if((HEADER==byt[0]) && (HEADER==byt[1])){//vérifie les 2 premiers bytes
       
        int check=byt[0]+byt[1]+byt[2]+byt[3]+byt[4]+byt[5]+byt[6]+byt[7];//variable qui va vérifier le bon fonctionnement du laser et si les données recues sont bonnes
        if(byt[8]==(check&0xff)){
          distance=byt[2]+byt[3]*256;//calcul de la distance
          delay(10);
          return distance;//retour de la distance
        }
    }
        
  }
  return;
}
////////////////////////////////////////////////
void envBT(){//envoie la lettre p au bluetooth qui nous signal la détection d'un obstacle
    Serial3.print("P");
}

////////////////////////////////////////////////
void rcvBT(){//lit les données recues par le bluetooth
  while(Serial3.available()){
    c=char(Serial3.read());
    if(c=='S'){// lance scanner si la lettre s est recue
      scanner();
  }
}
}
///////////////////////////////////////////////
void scanner(){ //fonction permettant de scanner
  Serial3.print("D");//envoie la lettre d au bluetooth pour lui confirmer le début du scan
  Serial2.begin(115200);
  delay(5);
  for(int j=110;j>=50;j--){//boucle pour le servo vertical
    servoVer.attach(6);// permet d'attacher le servo vertical au port lui correspondant
    servoVer.write(j);
    for(int i=40;i<=120;i+=1){//boucle pour le servo horizontale aller
      servoHor.attach(5);// permet d'attacher le servo horizontal au port lui correspondant
      servoHor.write(i);
      Serial2.end();//met fin a la communication avec le laser(le vide)
      Serial2.begin(115200);//commence la communication avec le laser
      delay(10);
      k=laserfct();//distance par rapport a l'objet
      Serial3.println(k);// envoie de la distance au bluetooth
      delay(5);
      servoHor.detach();//permet de détacher le servo horizontale (plus de fluidité)
    }
    j=j-1;
    servoVer.write(j);
    for(int i=120;i>=40;i--){// 2ème boucle pour le servo horizontale retour
      servoHor.attach(5);
      servoHor.write(i);
      Serial2.end();
      Serial2.begin(115200);
      delay(10);
      k=laserfct();
      Serial3.println(k);
      delay(5);
      servoHor.detach();
    }
    delay(10);
    servoVer.detach();//permet de détacher le servo vertical de son port (plus de fluifité)
  }
  servoVer.attach(6);
  servoHor.attach(5);
  servoVer.write(100);
}
///////////////////////////////////////////////
//-- MOTEUR A -
int ENA=9; //Connecté à Arduino pin 3(sortie PWM) 
int IN1=3; //Connecté à Arduino pin 4 
int IN2=4; //Connecté à Arduino pin 5
//-- MOTEUR B -
int ENB=11; //Connecté à Arduino pin 10(Sortie PWM) 
int IN3=10; //Connecté à Arduino pin 6 
int IN4=12; //Connecté à Arduino pin 7

void setup() {
  Serial.begin(38400);
  Serial3.begin(38400);
  Serial2.begin(115200);
  servoVer.attach(6);
  servoHor.attach(5);
   servoVer.write(100);
  pinMode(ENA,OUTPUT); // Configurer 
  pinMode(ENB,OUTPUT); // les broches 
  pinMode(IN1,OUTPUT); // comme sortie 
  pinMode(IN2,OUTPUT); 
  pinMode(IN3,OUTPUT); 
  pinMode(IN4,OUTPUT); 
  digitalWrite(ENA,LOW);// Moteur A - Ne pas tourner 
  digitalWrite(ENB,LOW);// Moteur B - Ne pas tourne
  //Les moteurs tournent toujours dans le même sens:
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  Serial.println("Esclave setup");

}

//Définition des fonctions de déplacement:
void avancer(){ //Le robot avance
  analogWrite(ENA,255);
  analogWrite(ENB,255);
}

void droite(){ //Le robot tourne à gauche
  analogWrite(ENA,255);
  analogWrite(ENB,0);
}
void gauche(){ //Le robot tourne a gauche
  analogWrite(ENA,0);
  analogWrite(ENB,255);
  
  
}
void arret(){// arret du déplacement
  analogWrite(ENA,0);
  analogWrite(ENB,0);
}
void bouton(){// fonction qui gère la direction du robot selon l'état des boutons
  while (Serial3.available()) {
    etat = char(Serial3.read());//lit le bluetooth
    if (etat == 'Z'){// permet de faire avancer le robot en continue
        etat_dep=1-etat_dep;
        if (etat_dep==1){avancer();}
        else {arret();}
      }
        
      
      else if (etat == 'D'){
        gauche();
        }

      
      
    
    else if (etat == 'Q'){
          droite();}

      
    }
  }


void loop() {
for(int h=10;h<=150;h++){// boucles for afin de déplacer le servo horizontale de gauche à droite
      servoHor.write(h);
      k=laserfct();//distance
      bouton();// permet de se déplacer
      if((k<60)&&(k>10)){//pause en cas de détection d'un objet
        Serial2.end();
        temps=millis();
        currentmillis=millis();
        envBT();
        while((currentmillis-temps)/1000<5){// première pause pour l'attente du scan
          arret();
          rcvBT();
          currentmillis=millis();
         
        }
      temps=millis();
      currentmillis=millis();
      while((currentmillis-temps)/1000<=5){// pause pour se déplacer sans détecter d'objet
             bouton();
             currentmillis=millis();
      }
      Serial2.begin(115200);
      delay(10);
      }
    }
  for(int h=150;h>=10;h--){// boucles for afin de déplacer le servo horizontale de droite à gauche
      servoHor.write(h);
      l=laserfct();
      bouton();
      if((l<60)&&(l>10)){
        Serial2.end();
        temps=millis();
        currentmillis=millis();
        envBT();
        while((currentmillis-temps)/1000<5){
          arret();
          rcvBT();
          currentmillis=millis();
         
        }
      temps=millis();
      currentmillis=millis();
      while((currentmillis-temps)/1000<=5){
             bouton();
             currentmillis=millis();
      }
      Serial2.begin(115200);
      delay(10);
      }
    }
}
