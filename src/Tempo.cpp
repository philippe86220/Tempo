/**
 * @file Tempo.cpp
 * @author Nicolas Fourgheon
 * @page https://github.com/boby15000/Tempo
 * @brief Tempo est une bibliothèque qui vise à fournir une fonctionnalité de délai non bloquante.
 * @version v1.3.0
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
    this->_tempo[0] = 0 ; // Etat du compteur
    this->_tempo[1] = 0 ; // Seuil du compteur
    this->_tempo[2] = 0 ; // Unite du compteur
    this->_tempo[3] = 0 ; // Temps initiale du compteur au démarrage
    this->_tempo[4] = 0 ; // Etat fin de compteur
}

/*
* Initiale la Tempo.
*/
void Tempo::Init(long value, int unite){
    this->_tempo[0] = 0 ; // Etat du compteur
    this->_tempo[1] = this->ConversionUnite(unite, value); // Seuil du compteur
    this->_tempo[2] = unite; // Unite du compteur
}

/*
* Démarre la Tempo si il n'est pas en fonction.
*/
void Tempo::Start(long value, int unite){
    if ( this->_tempo[0] ) return;
    if ( value > 0 && unite > 0 ) this->Init(value, unite); // Réinitialise le compteur avec des nouvelles données
    this->_tempo[0] = 1 ; // Etat du compteur
    this->_tempo[3] = ( this->_tempo[2] < this->Millis ) ? micros() : millis(); // Défini le Temps initiale du compteur au démarrage
    this->_tempo[4] = 0 ; // Etat fin de compteur
}

/*
* Arrete la Tempo.
*/
void Tempo::Stop(){
    this->_tempo[0] = 0 ; // Etat du compteur
    this->_tempo[3] = 0 ; // Temps initiale du compteur au démarrage
}

/*
* Indique si la Tempo est en fonction.
*/
bool Tempo::IsStart(){
    return this->_tempo[0];
}

/*
* Indique la fin de la tempo.
*/
int Tempo::End(){
     // la Tempo est actif
    if ( this->_tempo[0] )
    {
        // Détermine la fin de la tempo.
        // (Temps Actuel - Temps de départ) >= Seuil
        if ( this->_tempo[2] == this->Micro )
        { 
            this->_tempo[4] = ( (micros() - this->_tempo[3]) >= this->_tempo[1] ); // Etat fin de compteur
            if (  this->_tempo[1] < (micros() - this->_tempo[3])   )
            { this->_tempo[5] = 0;  } // Temps restant
            else
            { this->_tempo[5] = ( this->_tempo[1]-(micros() - this->_tempo[3]) );  } // Temps restant
        }
        else
        {
            this->_tempo[4] = ( (millis() - this->_tempo[3]) >= this->_tempo[1] ); // Etat fin de compteur
            if ( this->_tempo[1] < (millis() - this->_tempo[3])   )
            { this->_tempo[5] = this->_tempo[3];  } // Temps restant
            else
            { this->_tempo[5] = ( this->_tempo[1]-(millis() - this->_tempo[3]) );  } // Temps restant
        }

        // Stop la Tempo si fin de celle-ci.
        if ( this->_tempo[4] ) this->Stop();
    }
    return this->_tempo[4];
}

/*
* Retourne le temps restant en Millis ou Micro si Micro utilisé en tant qu'unité
*/
unsigned long Tempo::GetTime(){
    this->End();
    return this->_tempo[5];
}


/*
* Converti le seuil en milliseconde pour les unités de Seconde à Heure
*/
long Tempo::ConversionUnite(long unite, long seuil)
{
    switch (unite) {
        case 3: // Seconde
            return (seuil *1000);
            break;
        case 4: // Minute
            return (seuil *60000);
            break;
        case 5: // Heure
            return (seuil *3600000);
            break;
        default:
            return seuil;
        break;
    };
}
#endif