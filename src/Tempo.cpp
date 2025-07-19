/**
 * @file Tempo.cpp
 * @author Nicolas Fourgheon
 * @page https://github.com/boby15000/Tempo
 * @brief Tempo est une bibliothèque qui vise à fournir une fonctionnalité de délai non bloquante.
 * @version v1.5.4
 * @date 2023-05-24
 */

#ifndef Tempo_h
#include "Tempo.h"

#include <Arduino.h>

/**
 * Declare la Tempo.
 */
Tempo::Tempo() {}

void Tempo::Init(unsigned long value, BaseTemps unite, bool autoRestart) {
    tempo.actif = 0;
    tempo.seuil = this->ConversionUnite(unite, value);
    tempo.unite = unite;
    tempo.autoRestart = autoRestart;
}

void Tempo::Start(unsigned long value, BaseTemps unite, bool autoRestart) {
    if (tempo.actif && !tempo.fini) return;
    if (value > 0) this->Init(value, unite);
    tempo.actif = 1;
    tempo.depart = (tempo.unite == MICRO) ? micros() : millis();
    tempo.fini = 0;
    tempo.autoRestart = autoRestart;
}

void Tempo::ReStart() {
    tempo.actif = 1;
    tempo.depart = (tempo.unite == MICRO) ? micros() : millis();
    tempo.fini = 0;
}

void Tempo::Pause() {
    if (!tempo.actif || tempo.fini) return;
    tempo.pauseSeuil = tempo.seuil;
    tempo.actif = 0;
    tempo.seuil = tempo.seuil - (((tempo.unite == MICRO) ? micros() : millis()) - tempo.depart);
}

void Tempo::Stop() {
    tempo.actif = 0;
    tempo.depart = 0;
    tempo.pauseSeuil = 0;
}

void Tempo::OnEnd(Callback cb) {
    onEndCallback = cb;
}

void Tempo::Update() {
    if (tempo.actif && !tempo.fini) {
        unsigned long current = (tempo.unite == MICRO) ? micros() : millis();
        unsigned long elapsed = current - tempo.depart;
        tempo.fini = (elapsed >= tempo.seuil);
        tempo.restant = tempo.fini ? 0 : tempo.seuil - elapsed;

        if (tempo.fini && onEndCallback != nullptr) onEndCallback();

        if (tempo.pauseSeuil > 0 && tempo.fini) {
            tempo.seuil = tempo.pauseSeuil;
            tempo.pauseSeuil = 0;
        }

        if (tempo.fini && tempo.autoRestart) this->ReStart();
    }
}

bool Tempo::IsStart() {
    return tempo.actif;
}

bool Tempo::IsPause() {
    return tempo.pauseSeuil > 0 && !tempo.actif;
}

bool Tempo::IsEnd() {
    this->Update();
    return tempo.fini;
}

unsigned long Tempo::GetTime() {
    this->Update();
    return tempo.restant;
}

unsigned long Tempo::ConversionUnite(BaseTemps unite, unsigned long seuil) {
    switch (unite) {
        case SECONDE: return (seuil * 1000);
        case MINUTE: return (seuil * 60000);
        case HEURE:  return (seuil * 3600000);
        default:     return seuil;
    }
}
#endif
