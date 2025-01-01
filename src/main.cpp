#include <Arduino.h>
#include <Tempo.h>

Tempo Minuterie;
Tempo Minuterie1;
Tempo Minuterie2;

void setup() {
  Serial.begin(9600);
  Minuterie.Init(5, Minuterie.Seconde);
}

String message;
String message1;
String message2;

void loop() {

  // Démarre le compteur si celui-ci n'est pas déjà en fonction
  Minuterie.Start();
  Serial.println(Minuterie.GetTime());
}