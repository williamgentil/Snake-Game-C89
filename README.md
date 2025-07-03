# 🐍 Snake (C89)

Un clone du célèbre jeu **Snake** développé en **langage C89**.  
Ce projet a été réalisé dans le cadre d’un exercice de programmation en collaboration avec **Fabio Étoile**.

## 🎮 Aperçu

Ce jeu propose une version terminale du Snake classique :  
- Le serpent grandit en mangeant des fruits.  
- Le jeu se termine si le serpent heurte un mur ou lui-même.

Compatible avec les systèmes Unix/Linux, le jeu s’exécute directement dans le terminal.

---

## ⚙️ Prérequis

- Un compilateur C compatible C89 (`gcc`)
- `make` installé

---

## 📦 Installation et exécution

Cloner le dépôt et compiler le jeu avec `make` :

```bash
git clone https://github.com/williamgentil/Snake-Game-c89.git
cd snake-c89
make        # Compile le jeu
make run    # Lance le jeu
make clean  # Supprime les fichiers de build
