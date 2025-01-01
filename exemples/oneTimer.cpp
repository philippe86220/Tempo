#include <Arduino.h>
#include <Tempo.h>

Tempo Minuterie;

void setup() {
  // Initiale une communication série
  Serial.begin(9600);
  // Démarre le minuteur avec ses paramétres
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