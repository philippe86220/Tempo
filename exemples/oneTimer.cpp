#include <Arduino.h>
#include <Tempo.h>

Tempo Minuterie;

void setup() {
  
  Serial.begin(9600);
  //Minuterie.Init(5, Minuterie.Seconde);
  Minuterie.Start(5, Minuterie.Seconde);
}

String message;

void loop() {

  if ( Minuterie.End() )
  { message = "Compteur 5s terminé"; }
  else
  { message = "Compteur 5s en cours, Reste encore : " + String(Minuterie.GetTime()/1000); }

  Serial.println(message);
  delay(1000);
}