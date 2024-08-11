#include <Arduino.h>
#include <Tempo.h>

Tempo Tempo;

void setup() {
  
  Serial.begin(9600);
  Tempo.SetSeuil(0, 5, Tempo.Heure);
  
}

String message;

void loop() {
 

    if ( Tempo.GetEnd(0) )
    { message = "Compteur 5h terminé"; }
    else
    { message = "Compteur 5h reste " + String(Tempo.GetHeure(0)) + "h " + String(Tempo.GetMinute(0)) + "mn " + String(Tempo.GetSeconde(0)) + "s"; }

    //message = "Seuil : " +   String(Tempo.GetSeuil(0)) + " moins le Décompte : " + String(Tempo.GetHWO(0)) + " ===> Restant : " + String(Tempo.GetHWOR(0));
    Serial.println(message);
    delay(1000);

 
  Tempo.SetActif(0, true);
  Tempo.TempoRefresh();

}