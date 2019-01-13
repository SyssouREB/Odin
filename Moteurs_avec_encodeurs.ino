/*
* 
*/

#include <SimpleTimer.h>
#define _DEBUG false

SimpleTime timer;
const int ENA = 3;          //pin controle moteur
const int codeuseA = 2;     //pin controle codeuse
unsigned tick_codeuse = 0;  //compteur de tick de la codeuse
int cmd = 0;                //commande donnée au moteur au final

const int frequence_echantillonage = 50; //Fréquence d'éxecution de l'asservissement
const float rapport_reducteur=47.3;      //Rapport entre le nombre de tours de l'arbre moteur et de la roue
const int tick_par_tour_codeuse = 64;    //Nombre de tick codeuse par tour de l'arbe moteur

float consigne_moteur_nombre_tours_par_seconde = 5.;  //  Nombre de tours de roue par seconde

float erreur_precedente = consigne_moteur_nombre_tours_par_seconde;
float somme_erreur = 0; //Somme des erreurs pour l'intégrateur
float kp = 300;         //Coefficient proportionnel
float ki = 5.5;         //Coefficient intégrateur
float kd = 100;         //Coefficient dérivateur

/*Routine d'initialisation */
void setup() {
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);   //Moteur en sortie
  analogWrite(ENA, 0);    //Arrêt du moteur
  
  delay(5000);            //Pause pour laisser le temps au moteur de s'arréter s'il était en marche

  attachInterrupt(codeuseA, compteur, CHANGE); // Interruption sur tick de la codeuse 
  timer.setInterval(1000/frequence_echantillonage, asservissement); //interruption pour calcul du PID et asservissement
}

/* Fonction principale */
void loop(){ 
}

/*Interruption sur tick de la codeuse */
void compteur(){
  tick_codeuse++; //On incrémente le nombre de tick de la codeuse
}

/*Interruption pour calcul du PID */
void asservissement(){

  //Caclul des erreurs
  int frequence_codeuse = frequence_echantillonage*tick_codeuse;
  float nb_tour_par_sec = (float)frequence_codeuse/(float)tick_par_tour_codeuse/(float)rapport_reducteur;
  float erreur == consigne_moteur_nombre_tours_par_seconde - nb_tour_par_sec;
  somme_erreur +=erreur;
  float delta_erreur = erreur-erreur_precedente;
  erreur_precendte = erreur;

  cmd=kp*erreur + ki*somme_erreur + kd*delta_erreur; //Calcul de la commande

  //Normalisation et controle du moteur
  if(cmd<0) cmd=0;
  else if(cmd > 255) cmd =255;
  analogWrite(ENA, cmd);

  //DEBUG
  if(_DEBUG) Serial.println(nb_tour_par_sec,8);
}
