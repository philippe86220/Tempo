
# ⏱️ Tempo – Minuterie simple pour Arduino

`Tempo` est une bibliothèque Arduino conçue pour faciliter la gestion des temporisations non bloquantes, avec un support natif des **callbacks** et une option de **redémarrage automatique**. Elle permet d’exécuter facilement une action après un certain délai, sans bloquer le programme avec `delay()`.

---

## 🚀 Fonctionnalités

- ✅ Temporisation non bloquante
- 🔁 Redémarrage automatique optionnel
- 🧠 Support des **callbacks** à la fin du compte à rebours
- ⏳ Unités supportées : millisecondes, secondes, minutes
- 🔧 Facile à intégrer, légère et optimisée pour les petits microcontrôleurs

---

## 📦 Installation

1. Télécharge ou clone ce dépôt :
   ```bash
   git clone https://github.com/ton-utilisateur/Tempo.git
   ```

2. Copie le dossier `Tempo` dans ton répertoire `libraries/` d’Arduino :
   - Sous Windows : `Documents/Arduino/libraries`
   - Sous Linux/macOS : `~/Arduino/libraries/`

3. Redémarre l’IDE Arduino.

---

## 🛠️ Utilisation de base

```cpp
#include <Tempo.h>

Tempo Minuterie;

void setup() {
  Serial.begin(9600);

  // Définir une fonction appelée à la fin du compte à rebours
  Minuterie.OnEnd(FinDeTempo);

  // Lancer une tempo de 20 secondes sans redémarrage automatique
  Minuterie.Start(20, Tempo::SECONDE, false);
}

void loop() {
  Minuterie.Update(); // Nécessaire pour vérifier l’état de la tempo
}

// Callback appelé à la fin
void FinDeTempo() {
  Serial.println("La tempo est terminée !");
}
```

---

## ⌚ Méthodes principales

| Méthode                         | Description |
|-------------------------------|-------------|
| `Start(valeur, unité, auto)`  | Démarre la temporisation. |
| `Update()`                     | À appeler régulièrement dans `loop()` pour que la tempo fonctionne. |
| `OnEnd(callback)`              | Définit une fonction à appeler à la fin. |
| `IsRunning()`                  | Renvoie `true` si la tempo est en cours. |
| `Stop()`                       | Arrête la tempo manuellement. |

---

## 📌 Unités de temps disponibles

```cpp
Tempo::MILLISECONDE
Tempo::SECONDE
Tempo::MINUTE
```

---

## 🧪 Exemples fournis

- `SimpleTempo.ino` – Exemple de base avec callback
- `AutoRestart.ino` – Exemple avec redémarrage automatique
- `MultipleTempo.ino` – Utilisation de plusieurs minuteries

---

## 🧰 Compatibilité

- ATmega328 (Uno, Nano)
- ATtiny85 ✅ (fonctionne avec mise à jour régulière de `.Update()`)
- ESP8266, ESP32
- Arduino Mega

---

## 📄 Licence

MIT – Utilisation libre avec attribution.

---

## 🤝 Contribuer

Les contributions sont les bienvenues ! Forkez le dépôt, créez une branche, puis ouvrez une *pull request*.

---

> Mainteneur : Nicolas Fourgheon
>  
> Pour toute question, ouvrez un [Issue](https://github.com/ton-utilisateur/Tempo/issues).
