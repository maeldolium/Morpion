# Morpion (Tic-Tac-Toe) – Projet C++


Un petit jeu du **Morpion** (Tic-Tac-Toe) en **C++**, jouable directement dans le terminal.

🎮 Modes disponibles :  
- **1 joueur** : Affrontez un **bot intelligent**  
- **2 joueurs** : Mode local, tour par tour

---

## 🚀 Démarrer

### 📦 Compilation (g++)

```bash
g++ -std=c++17 -o morpion morpion.cpp
./morpion
```

### 🧩 Compilation avec Visual Studio (Windows)

1. Créez un nouveau projet console en C++
2. Copiez-collez le contenu de `morpion.cpp` dans `main.cpp`
3. Compilez et exécutez

---

## 🎮 Comment jouer

- Chaque joueur entre les **coordonnées** (ligne et colonne) de la case où il souhaite jouer.
- Le jeu vérifie automatiquement la validité du coup, détecte les gagnants et annonce le résultat.
- À la fin d’une partie, vous pouvez **rejouer** ou **quitter**.

---

## 🧠 Intelligence du Bot

Le bot analyse :
- Les **coups gagnants**
- Les **menaces adverses** à bloquer
- Les **cases stratégiques** : centre, coins, etc.

Ce n’est pas un algorithme parfait (comme Minimax), mais il offre une vraie opposition.

---

## 📂 Structure du projet

```
📁 /morpion
├── morpion.cpp     // Code principal
└── README.md       // Ce fichier
```

---

## ✨ Exemple d'affichage console

```
Bienvenue dans le jeu du Morpion !
   0   1   2  
-------------
0| _ | _ | _ | 
-------------
1| _ | _ | _ | 
-------------
2| _ | _ | _ | 

Joueur O - Entrez la ligne et la colonne (0-2) :
```

---

## 👤 Auteur

Projet réalisé par **Maël DOLIUM**  
📘 Projet pédagogique pour apprendre la POO en C++

---

## 📝 Licence

Ce projet est en open-source sous licence **MIT**.  
Libre à toi de le modifier, redistribuer, ou t’en inspirer ✌️
