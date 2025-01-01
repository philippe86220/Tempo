#include <Arduino.h>
#include <Tempo.h>

Tempo Minuterie;

void setup() {
  Serial.begin(9600);
  Minuterie.Init(5, Minuterie.Seconde);
}

void loop() {

  // Démarre le compteur si celui-ci n'est pas déjà en fonction
  Minuterie.Start();
  Serial.println(Minuterie.GetTime());
}