#include <Arduino.h>
#include <Temporisation.h>

Temporisation Tempo;
int cpt[3] = {30, 5, 2};

void setup() {
  
  Serial.begin(9600);
  Tempo.SetSeuil(0, cpt[0], Tempo.Seconde);
  Tempo.SetSeuil(1, cpt[1], Tempo.Minute);
  Tempo.SetSeuil(2, cpt[1], Tempo.Heure);
  
}

String message;

void loop() {
 
  for (size_t i = 0; i < 3; i++)
  {
    if ( Tempo.GetEnd(i) )
    { message = "Compteur " + String(i) +  " " + cpt[i] + " terminé"; }
    else
    { message = "Compteur " + String(i) +  " à " + cpt[i] + " reste " + String(Tempo.GetHeure(i)) + "h " + String(Tempo.GetMinute(i)) + "mn " + String(Tempo.GetSeconde(i)) + "s"; }

    Serial.println(message);
    delay(1000);

  }
  
  Tempo.SetActif(0, true);
  Tempo.SetActif(1, true);
  Tempo.SetActif(2, true);
  Tempo.TemporisationRefresh();

}