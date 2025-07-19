#include <Arduino.h>
#include "Tempo.h"  // Inclut la bibliothèque Tempo

// Création d'une instance de tempo
Tempo Minuterie;

void setup() {
  Serial.begin(115200);  // Initialisation de la communication série
  // Démarre un compte à rebours de 20 secondes
  Minuterie.Start(20, Tempo::SECONDE);
}

void loop() {
  // Variable statique pour mémoriser la dernière seconde affichée
  static int last = -1;

  // Calcule le nombre de secondes restantes avec arrondi au plus proche
  unsigned long sec = (Minuterie.GetTime() + 500) / 1000;

  // Si la minuterie est terminée, affiche un message une seule fois
  if (Minuterie.IsEnd()) {
    Serial.println("Compteur 20s terminé");
  }
  // Sinon, affiche le temps restant si une nouvelle seconde est atteinte
  else if ((int)sec != last) {
    last = sec;
    Serial.print("Compteur 20s en cours. Reste encore : ");
    Serial.println(sec);
  }

  // Petit délai pour lisibilité et fluidité (sans bloquer l'affichage final)
  delay(100);
}
