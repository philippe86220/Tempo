/**
 * @file Tempo.h
 * @author Nicolas Fourgheon
 * @page https://github.com/boby15000/Tempo
 * @brief Tempo est une bibliothèque qui vise à fournir une fonctionnalité de délai non bloquante.
 * @version v1.5.4
 * @date 2023-05-24
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
        void Init(unsigned long value, BaseTemps unite, bool autoRestart = false); // Initialise la Tempo
        void Start(unsigned long value = 0, BaseTemps unite = MICRO, bool autoRestart = false); // Démarre la Tempo
        void ReStart(); // Redémarrage forcé
        void Pause(); // Pause
        void Stop(); // Arrêt
        void OnEnd(Callback cb); // Callback
        void Update(); // Mise à jour (à appeler dans loop)
        bool IsStart(); // Si la tempo est active
        bool IsPause(); // Si elle est en pause
        bool IsEnd(); // Vérifie la fin de tempo et met à jour
        unsigned long GetTime(); // Temps restant

    private:
        Callback onEndCallback = nullptr;
        unsigned long ConversionUnite(BaseTemps unite, unsigned long seuil);
        struct TempoData {
            bool actif;
            unsigned long seuil;
            BaseTemps unite;
            unsigned long depart;
            bool fini;
            unsigned long restant;
            unsigned long pauseSeuil;
            bool autoRestart = false;
        };
        TempoData tempo;
};
#endif
