#include<Servo.h>
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
//////////////////////////////////////////////////
int laserfct(){
    if(Serial2.available()){//vérifie que le laser possède des données
       for(int i=0;i<9;i++){//lecture des 9 bytes envoyé par le laser
          byt[i]=Serial2.read();//lit les 8 bytes et les place dans un tableau
        }
    if((HEADER==byt[0]) && (HEADER==byt[1])){//vérifie les 2 premiers bytes
        delay(1);
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
  for(int j=150;j>=20;j=j-10){//boucle pour le servo verticale
    servoVer.attach(6);// permet d'attacher le servo verticale au port lui correspondant
    servoVer.write(j);
    for(int i=10;i<=150;i++){//boucle pour le servo horizontale aller
      servoHor.attach(5);
      servoHor.write(i);
      Serial.println(laserfct());// on veut la distance en permanence
      delay(10);
      servoHor.detach();
    }
    j=j-10;
    servoVer.write(j);
    for(int i=150;i>=10;i--){// 2ème boucle pour le servo horizontale retour
      servoHor.attach(5);
      servoHor.write(i);
      Serial.println(laserfct());
      delay(10);
      servoHor.detach();
    }
    delay(10);
    servoVer.detach();//permet de détacher le servo verticale de son port (plus de fluifité)
  }
  servoVer.attach(6);
  servoHor.attach(5);
  servoVer.write(90);
}
////////////////////////////////////////////////////
void scanBT(){// fonction pour le bluetooth
   while(Serial3.available()){// si le bluetooth recoit quelque chose faire la suite
 scan=char(Serial3.read());// lit la lettre recu par le bluetooth
 }
if(scan=='A'){// lance scanner si le bluetooth recoit la lettre A
        scanner();
        scan='E';
      }
else{}
}
///////////////////////////////////////////////////////////
void setup() {
  servoVer.attach(6);
  servoHor.attach(5);
  Serial.begin(250000);
  Serial2.begin(115200);
  Serial3.begin(9600);
}

void loop() {
Serial.println(laserfct());// fonction laser qui print les valeurs ddistances
 for(int h=10;h<=150;h++){// boucles for afin de déplacer le servo horizontale de gauche à droite
      servoHor.write(h);
      scanBT();// appel de la fonction bluetooth a chaque boucle afin de recevoir l'information pour lancer scanner
      Serial.println(laserfct());
      delay(10);
     
      
    }
Serial.println(laserfct());
  for(int h=150;h>=10;h--){// boucles for afin de déplacer le servo horizontale de droite à gauche
      servoHor.write(h);
      scanBT();
      Serial.println(laserfct());
      delay(10);
    }
}
