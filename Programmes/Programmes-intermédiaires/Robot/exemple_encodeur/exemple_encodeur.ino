//Prérequis savoir utiliser un timer
#include <TimerOne.h> //Bibliothèque du timer

//Broches pour l'encodeur du moteur A:
#define ENCODEURA1 1
#define ENCODEURA2 2

//Broches pour l'encodeur du moteur B:
#define ENCODEURB1 6
#define ENCODEURB2 7

//définition des variables:
//Variables de l'encodeur A:
volatile int compteA=0; //comptage de tick d'encodeur A qui sera incrémenté sur interruption 
volatile int compteB=0; //comptage de tick d'encodeur B qui sera incrémenté sur interruption
//" On change " sur l'interruption matériel 0 qui se fait ssur le pin 1
volatile double vitesse=0.0; // vitesse des moteur
volatile byte laststateA=0; //état précédent de l'encoder A
volatile byte laststateB=0; //état précédent de l'encoder B

//Variable du moteur A:
int ENA=3; //Connecté à Arduino pin 3(sortie PWM) 
int IN1=4; //Connecté à Arduino pin 4 
int IN2=5; //Connecté à Arduino pin 5

//Moteur B:
int ENB=10;
int IN3=8;
int IN4=9;



//Définition des fonctions de déplacement
void stop(){ //les moteur s'arrètent
  digitalWrite(ENA,0);
  digitalWrite(ENB,0);
}
void avance(char a){ // les moteurs avancent à une vitesse a
  analogWrite(ENA,a);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  analogWrite(ENB,a);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}
void recule(char a){
  analogWrite(ENA,a);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  analogWrite(ENB,a);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}
// Encoder counter 0
void counter(){
  byte state=PIND;
  
  state|=B11111001;  // mask pour ne regarder que les changements sur 2 et 4 
  // Modifier le MASK  B01111011 par BXXXXXXXX mettre des 0 là où sont les pins utilisés par l'encodeur
  if( state!=laststate){
    (((state&(1<<ENCODEURA1))>>ENCODEURA1)^((state&(1<<ENCODEURA1))>>ENCODEURA2))?compte--:compte++;
    laststate=state;
  }
}


// Timer event to calculate speed from counters
void timerIsr()
{
    vitesse=compte; // on a le nombre de tick ( signé ) par unité de temps  = vitesse
    compte=0; // On remet le compteur de tick à 0 
}
void setup() {
  pinMode(ENCODEURA1, INPUT_PULLUP);
  pinMode(ENCODEURA2, INPUT_PULLUP);

  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENA,OUTPUT);

  attachInterrupt(0,compte, CHANGE);// on crée l'interruption sur changement sur la pin 2 => interruption 0, la routine counter va se faire toute seule sans l'appeler à chaque changement d'état sur le pin 2

  Timer1.initialize(100000); // On défini le timeur : 100000 microseconds ( 0.1 sec - or 10Hz )
  Timer1.attachInterrupt( timerIsr );
  
  Serial.begin(9600); // Définit vitesse de transmission série
}

void loop(){
  if(Serial.available()){
    char val = Serial.read(); //récupération des caractères sur le
    if(val != -1){
      
      switch(val){
      case 'z':// En avant si touche "z"
      avance(255); // en avant vitesse max
                        // le driver fonctionne à l'état bas en marche avant
      break;
      case 's':// En arrière si touche "s"
      recule(255); // en arrière vitesse max
                    // le driver fonctionne à l'état haut en marche arrière
      break;
      case 'x': // arrêt si touche "x"
      stop();
      break;
      }
    }
    else stop();
  }
}
    
