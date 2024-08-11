#if ARDUINO >= 100    
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif


#ifndef TEMPO_INCLUDED
#define TEMPO_INCLUDED

class Tempo
{
    public:
        const int Micro = 0;
        const int Millis = 1;
        const int Seconde = 2;
        const int Minute = 3;
        const int Heure = 4;

        Tempo();
        Tempo(byte nbr);

        void SetActif(unsigned int i, bool etat);
        void SetSeuil(unsigned int i, unsigned long value);
        void SetSeuil(unsigned int i, unsigned long value, unsigned int unite);
       
        bool GetActif(unsigned int i);
        bool GetEnd(unsigned int i);
        unsigned long GetSeuil(unsigned int i);
        unsigned long GetHWO(unsigned int i);
        unsigned long GetHWOR(unsigned int i);
        byte GetMicro(unsigned int i);
        byte GetMillis(unsigned int i);
        byte GetSeconde(unsigned int i);
        byte GetMinute(unsigned int i);
        byte GetHeure(unsigned int i);

        byte GetTempo();
        byte GetTempoActif();
        

        void TempoRefresh();

    private:
        const byte TEMPO_MAX = 255;
        
        unsigned int _nbrTempo = 10;
        unsigned long _tempos[10][12];
        unsigned long ConversionUnite(unsigned long unite, unsigned long seuil);
        
        void CalculTempsRestant(unsigned int i);
};
#endif