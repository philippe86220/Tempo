/**
 * @file Tempo.cpp
 * @author Nicolas Fourgheon
 * @page https://github.com/boby15000/Tempo
 * @brief Tempo est une bibliothèque qui vise à fournir une fonctionnalité de délai non bloquante.
 * @version v1.5.4
 * @date 2023-05-24
 *
 * @copyright Copyright (c) 2024
 */

#ifndef Tempo_h
#include "Tempo.h"

#include <Arduino.h>

/**
 * Declare la Tempo.
 */
Tempo::Tempo(){

}


/*
* Initiale la Tempo.
*/
void Tempo::Init(long value, BaseTemps unite, bool autoRestart){
    tempo.actif = 0 ; // Etat du compteur
    tempo.seuil = this->ConversionUnite(unite, value); // Seuil du compteur
    tempo.unite = unite; // Unite du compteur
    tempo.autoRestart = autoRestart;
}

/*
* Démarre la Tempo (si celle-ci est terminé ou pas actif).
*/
void Tempo::Start(long value, BaseTemps unite, bool autoRestart){
    if ( tempo.actif && !tempo.fini ) return;    
    if ( value > 0 ) this->Init(value, unite); // Réinitialise le compteur avec des nouvelles données
    tempo.actif = 1 ; // Etat du compteur
    tempo.depart = ( tempo.unite == MICRO ) ? micros() : millis(); // Défini le Temps initiale du compteur au démarrage
    tempo.fini = 0 ; // Etat fin de compteur
    tempo.autoRestart = autoRestart;
}

/*
* Force le Redémarrage de la Tempo.
*/
void Tempo::ReStart(){
    tempo.actif = 1 ; // Etat du compteur
    tempo.depart = ( tempo.unite == MICRO ) ? micros() : millis(); // Défini le Temps initiale du compteur au démarrage
    tempo.fini = 0 ; // Etat fin de compteur
}

/*
* Mise en Pause de la Tempo.
*/
void Tempo::Pause(){
    if ( !tempo.actif || tempo.fini ) return;
    tempo.pauseSeuil = tempo.seuil;
    tempo.actif = 0 ; // Etat du compteur
    tempo.seuil = tempo.seuil - ((( tempo.unite == MICRO ) ? micros() : millis()) - tempo.depart); // Seuil du compteur
}

/*
* Arrete la Tempo.
*/
void Tempo::Stop(){
    tempo.actif = 0 ; // Etat du compteur
    tempo.depart = 0 ; // Temps initiale du compteur au démarrage
    tempo.pauseSeuil = 0 ; // Seuil du compteur (utilisé lors d'une pause)
}

/*
* Ajoute une fonction de CallBack
*/
void Tempo::OnEnd(Callback cb) {
    onEndCallback = cb;
}

/*
* Logique de Mise à jour de la Tempo - Doit être dans le loop()
*/
void Tempo::Update() {
    // la Tempo est actif et n'est pas terminé
    if ( tempo.actif && !tempo.fini )
    {
        // Détermine la fin de la tempo. => (Temps Actuel - Temps de départ) >= Seuil 
        switch (tempo.unite)
        {
        case MICRO:
            tempo.fini = ( (micros() - tempo.depart) >= tempo.seuil ); // Etat fin de compteur
            if (tempo.fini) {
                tempo.restant = 0;
            } else {
                tempo.restant = tempo.seuil - (micros() - tempo.depart);
            }
            break;
        default:
            tempo.fini = ( (millis() - tempo.depart) >= tempo.seuil ); // Etat fin de compteur
            if (tempo.fini) {
                tempo.restant = 0;
            } else {
                tempo.restant = tempo.seuil - (millis() - tempo.depart);
            }
            break;
        }

        // Appel la fonction de CallBack si elle existe
        if (tempo.fini && onEndCallback != nullptr) onEndCallback();

        // Réinitialise le seuil capteur "Pause" si la tempo est terminé     
        if ( tempo.pauseSeuil > 0 && tempo.fini )
        {
            tempo.seuil = tempo.pauseSeuil;
            tempo.pauseSeuil = 0;
        }

        // Redémarre la Tempos automatiquement si défini
        if (tempo.fini && tempo.autoRestart) this->ReStart();
        
    }
}

/*
* Indique si la Tempo est en fonction.
*/
bool Tempo::IsStart(){
    return tempo.actif;
}

/*
* Indique si la Tempo est en pause.
*/
bool Tempo::IsPause(){
    return tempo.pauseSeuil > 0 && !tempo.actif;
}

/*
* Indique la fin de la tempo.
*/
int Tempo::IsEnd(){
    this->IsEnd();
    return tempo.fini;
}

/*
* Retourne le temps restant en Millis ou Micro si Micro utilisé en tant qu'unité
*/
unsigned long Tempo::GetTime(){
    this->IsEnd();
    return tempo.restant;
}

/*
* Converti le seuil en milliseconde pour les unités de Seconde à Heure
*/
long Tempo::ConversionUnite(BaseTemps unite, long seuil)
{
    switch (unite) {
        case SECONDE: // Seconde
            return (seuil *1000);
            break;
        case MINUTE: // Minute
            return (seuil *60000);
            break;
        case HEURE: // Heure
            return (seuil *3600000);
            break;
        default:
            return seuil;
        break;
    };
}
#endif