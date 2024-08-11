#include <Arduino.h>
#include <Temporisation.h>

Temporisation Tempo;


void setup() {
  
  Serial.begin(9600);
  Tempo.SetSeuil(0, 2000, Tempo.Millis);
  Tempo.SetSeuil(1, 5, Tempo.Seconde);
  Tempo.SetSeuil(2, 1, Tempo.Minute);
  Tempo.SetSeuil(3, 5, Tempo.Minute);
  Tempo.SetSeuil(4, 1, Tempo.Heure);
  Tempo.SetSeuil(5, 50, Tempo.Micro);
  
}



void loop() {
 
  if ( Tempo.GetEnd(0) )
  {
    Serial.println("Compteur 1 (2s) terminé"); 
  }

  if ( Tempo.GetEnd(1) )
  {
    Serial.println("Compteur 2 (5s) terminé"); 
  }

  if ( Tempo.GetEnd(2) )
  {
    Serial.println("Compteur 3 (1mn) terminé"); 
  }

  if ( Tempo.GetEnd(3) )
  {
    Serial.println("Compteur 4 (5mn) terminé"); 
  }

  if ( Tempo.GetEnd(4) )
  {
    Serial.println("Compteur 5 (1h) terminé"); 
  }

  if ( Tempo.GetEnd(5) )
  {
    Serial.println("Compteur 6 (50micro) terminé"); 
  }
  Tempo.SetActif(0, true);
  Tempo.SetActif(1, true);
  Tempo.SetActif(2, true);
  Tempo.SetActif(3, true);
  Tempo.SetActif(4, true);
  Tempo.SetActif(5, false);
  Tempo.TemporisationRefresh();

}