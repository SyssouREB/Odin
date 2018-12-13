/*
Projet:
Partie moteur:
Programme test d'un seul moteur:
*/

// MOTEUR A 
int ENA=9; //Connecté à Arduino pin 9(sortie PWM) 
int IN1=4; //Connecté à Arduino pin 4 
int IN2=5; //Connecté à Arduino pin 5
// MOTEUR B 
int ENB=10; //Connecté à Arduino pin 10(Sortie PWM) 
int IN3=6; //Connecté à Arduino pin 6 
int IN4=7; //Connecté à Arduino pin 7

void setup() {
pinMode(ENA,OUTPUT); //Placer les broches en sorites
pinMode(ENB,OUTPUT); 
pinMode(IN1,OUTPUT);  
pinMode(IN2,OUTPUT); 
pinMode(IN3,OUTPUT); 
pinMode(IN4,OUTPUT); 
digitalWrite(ENA,LOW);// Moteur A - Ne pas tourner 
digitalWrite(ENB,LOW);// Moteur B - Ne pas tourner

// Direction du Moteur A 
digitalWrite(IN1,LOW); 
digitalWrite(IN2,HIGH); 
analogWrite(ENA,255);

// Direction du Moteur B // NB: en sens inverse du moteur A
digitalWrite(IN3,HIGH); 
digitalWrite(IN4,LOW); 
digitalWrite(ENB,0);}

void loop() { // teste les moteurs en les faisant alterner entre avant et arrière
  digitalWrite(IN1,HIGH); //Moteur A...
  digitalWrite(IN2,LOW);  //... vers l'arrière
  digitalWrite(IN3,LOW);  //Moteur B...
  digitalWrite(IN4,HIGH); //... vers l'avant
  digitalWrite(ENB,255);  //vitesse max
  digitalWrite(ENA,255);  //pour les deux
  delay(1000);
  digitalWrite(IN1,LOW);  //même chose mais dans l'autre sens
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  digitalWrite(ENA,255);
  digitalWrite(ENB,255);
  delay(1000);
}
