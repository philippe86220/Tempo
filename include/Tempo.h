/**
 * @file Tempo.h
 * @author Nicolas Fourgheon
 * @page https://github.com/boby15000/Tempo
 * @brief Tempo est une bibliothèque qui vise à fournir une fonctionnalité de délai non bloquante.
 * @version v1.5.2
 * @date 2023-05-24
 *
 * @copyright Copyright (c) 2024
 */

#if ARDUINO >= 100    
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#ifndef TEMPO_INCLUDED
#define TEMPO_INCLUDED

typedef void (*Callback)();

class Tempo
{
    public:
        enum BaseTemps {
            MICRO = 1,
            MILLIS = 2,
            SECONDE = 3,
            MINUTE = 4,
            HEURE = 5
        };

        Tempo(); // Declare la Tempo
        void Init(long value, BaseTemps unite, bool autoRestart = false); // Initialise la Tempo
        void Start(long value = 0, BaseTemps unite = MICRO, bool autoRestart = false); // Démarre la Tempo (si celle-ci n'est terminé ou pas actif)
        void ReStart(); // Force le redémarrage de la Tempo
        void Pause(); // Mise en pause de la Tempo.
        void Stop(); // Arrete la Tempo.
        void OnEnd(Callback cb); // Ajoute une fonction de CallBack
        void Update(); // Logique de Mise à jour de la Tempo - Doit être dans le loop() si IsEnd() non utilisé
        bool IsStart(); // Indique si la Tempo est en fonction.
        bool IsPause(); // Indique si la Tempo est en pause.
        int IsEnd(); // Indique la fin de la tempo.
        unsigned long GetTime(); // Retourne le temps restant en Millis ou Micro si Micro utilisé en tant qu'unité

    private:
        Callback onEndCallback = nullptr;
        long ConversionUnite(BaseTemps unite, long seuil);
        struct TempoData {
            bool actif; // => Etat du compteur
            unsigned long seuil; // => Seuil du compteur
            BaseTemps unite; // => Unite du compteur
            unsigned long depart; // => Temps initiale du compteur au démarrage
            bool fini; // => Etat fin de compteur
            unsigned long restant; // => Temps restant
            unsigned long pauseSeuil; // => Seuil du compteur (utilisé lors d'une pause)
            bool autoRestart = false; // => Redémarrage automatique (par défaut désactivé)
        };
        TempoData tempo;
    
};
#endif