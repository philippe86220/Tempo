#ifndef Tempo_h
#include "Tempo.h"
#endif

/* Nombre Maximum de Temporisation */
const byte TEMPO_MAX = 255;

/* Nombre de Temporisation par défaut */
const byte NBR_TEMPO_DEFAUT = 10;

/* Défini les diffrentes unités*/
const int Micro = 0;
const int Millis = 1;
const int Seconde = 2;
const int Minute = 3;
const int Heure = 4;

/*
Tempo[0] => Etat du compteur
Tempo[1] => Seuil du compteur
Tempo[2] => Initialise départ compteur
Tempo[3] => Decompte du compteur
Tempo[4] => Etat fin de compteur
Tempo[5] => Unite du compteur
Tempo[6] => Heure
Tempo[7] => Minute
Tempo[8] => seconde
Tempo[9] => Millis
Tempo[10] => Micro
Tempo[11] => Temps restant en seconde
*/
unsigned long _tempos[TEMPO_MAX][12];
unsigned int _nbrTempo;


/* --- Fonction Public --- */

Tempo::Tempo(){
    _nbrTempo = NBR_TEMPO_DEFAUT ;
}

Tempo::Tempo(byte nbr){
    _nbrTempo = nbr ;
}

void Tempo::SetActif(unsigned int i, bool etat){
    if ( i < _nbrTempo ) 
    {
        if ( _tempos[i][0] == 0 && etat ) _tempos[i][2] = millis() ;
        if (  !etat ) _tempos[i][4] = 0 ;
        _tempos[i][0] = long(etat);
    }
}

void Tempo::SetSeuil(unsigned int i, unsigned long value){
    if ( i < _nbrTempo ) 
    {
        _tempos[i][1] = ConversionUnite( _tempos[i][5], value);
    }
}

void Tempo::SetSeuil(unsigned int i, unsigned long value, unsigned int unite){
    if ( i < _nbrTempo && unite < 5 ) 
    {
        _tempos[i][5] = unite;
        _tempos[i][1] = ConversionUnite( _tempos[i][5], value);
    }
}


bool Tempo::GetActif(unsigned int i){
    if ( i > _nbrTempo ) return false;
    return bool(_tempos[i][0]) ;
}

bool Tempo::GetEnd(unsigned int i){
    if ( i > _nbrTempo ) return false;
    return bool(_tempos[i][4]) ;
}

unsigned long Tempo::GetSeuil(unsigned int i){
    if ( i > _nbrTempo ) return false;
    return _tempos[i][1] ;
}

unsigned long Tempo::GetHWO(unsigned int i){
    if ( i > _nbrTempo ) return false;
    return _tempos[i][3] ;
}

unsigned long Tempo::GetHWOR(unsigned int i){
    if ( i > _nbrTempo ) return false;
    return _tempos[i][11] ;
}

byte Tempo::GetTempo()
{
    return _nbrTempo;
}

byte Tempo::GetTempoActif()
{
    byte nbr;
    for (size_t i = 0; i < _nbrTempo; i++)
    {
         if ( _tempos[i][0] ) nbr+=1;
    }

    return nbr;
}

byte Tempo::GetMicro(unsigned int i){
    return byte(_tempos[i][10]);
}

byte Tempo::GetMillis(unsigned int i){
    return byte(_tempos[i][9]);
}

byte Tempo::GetSeconde(unsigned int i){
    return byte(_tempos[i][8]);
}

byte Tempo::GetMinute(unsigned int i){
    return byte(_tempos[i][7]);
}

byte Tempo::GetHeure(unsigned int i){
    return byte(_tempos[i][6]);
}

void Tempo::TempoRefresh(){
/*
Tempo[0] => Etat du compteur
Tempo[1] => Seuil du compteur
Tempo[2] => Initialise départ compteur
Tempo[3] => Decompte du compteur
Tempo[4] => Etat fin de compteur
Tempo[5] => Unite du compteur
Tempo[6] => Heure
Tempo[7] => Minute
Tempo[8] => seconde
Tempo[9] => Millis
Tempo[10] => Micro
Tempo[11] => Temps restant en seconde
*/   
    for (size_t i = 0; i < _nbrTempo; i++)
    {
        // Le compteur est actif
        if ( _tempos[i][0] )
        {
            // temps écoulé depuis le départ du compteur
            unsigned long _decompte;
            _decompte = micros() - _tempos[i][2];
            if ( _tempos[i][5] > 0 ) _decompte = millis() - _tempos[i][2];
            _tempos[i][3] = _decompte; 

            // Détermine la fin de la tempo
            _tempos[i][4] = ( _decompte >= _tempos[i][1] );
                      
            // Fin du compteur
            if ( _tempos[i][4] ) 
            {
                _tempos[i][0] = 0;
                _tempos[i][2] = 0;
                _tempos[i][3] = 0;
                _tempos[i][11] = 0;
            }
            else
            {
                // Calcul du Temps Restant si compteur non terminé
                _tempos[i][11] = _tempos[i][1] - _decompte ;
                CalculTempsRestant(i);
            } 
        }
    }
}


/* ------------------------ */
/* --- Fonction Private --- */
/*
Micro = 0;
Millis = 1;
Seconde = 2;
Minute = 3;
Heure = 4;
----------
Tempo[6] => Heure
Tempo[7] => Minute
Tempo[8] => seconde
Tempo[9] => Millis
Tempo[10] => Micro
*/

unsigned long Tempo::ConversionUnite(unsigned long unite, unsigned long seuil)
{
    switch (unite) {
    case 2:
        return (seuil *1000);
        break;
    case 3:
        return (seuil *60000);
        break;
    case 4:
        return (seuil *3600000);
        break;
    default:
        return seuil;
    break;
    };
}

void Tempo::CalculTempsRestant(unsigned int i){
   
    // Remise à zéro
    _tempos[i][6] = 0;
    _tempos[i][7] = 0;
    _tempos[i][8] = 0;
    _tempos[i][9] = 0;
    _tempos[i][10] = 0;
    
    switch (_tempos[i][5]) {
        case 1: // Millis
            _tempos[i][8] = _tempos[i][11];
            break;
        case 2: // Seconde
            _tempos[i][8] =  (_tempos[i][11] / 1000) ;
            break;
        case 3: // Minute
            _tempos[i][7] = (_tempos[i][11] / 60000) ;
            _tempos[i][8] = ((_tempos[i][11] % 60000) / 1000) ;
            break;
        case 4: // heure
            _tempos[i][6] = (_tempos[i][11] / 3600000);
            _tempos[i][7] = ((_tempos[i][11] % 3600000) / 60000) ; 
            _tempos[i][8] = (((_tempos[i][11] % 3600000) % 60000) / 1000);
            break;
        default: // Micro
            _tempos[i][8] = _tempos[i][11];
        break;
    };   
}