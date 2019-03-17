//const int led_rouge=3;
const int bouton=4;
int val=0;

void setup(){
  Serial.begin(38400);
  //pinMode(led_rouge,OUTPUT);
  pinMode(bouton,INPUT);
  //digitalWrite(led_rouge,LOW);
  delay(2000);
  Serial.print("All setup");
}

void loop(){
  val=digitalRead(bouton);
  delay(50);
  Serial.println(val);
  if(val==0){
   // digitalWrite(led_rouge,HIGH);
    Serial.println("LOW");
  }/*
  else {
     digitalWrite(led_rouge,LOW);
     Serial.println("LOW");
  }*/
}
