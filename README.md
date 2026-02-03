# 🌍 Simulation d'Écosystème Interactive

Une simulation interactive d'écosystème développée en C++ avec SDL3 et ImGui, permettant d'observer les dynamiques prédateur-proie dans différents environnements naturels.

![C++](https://img.shields.io/badge/C++-17-orange.svg)
![SDL3](https://img.shields.io/badge/SDL3-3.0-blue.svg)
![ImGui](https://img.shields.io/badge/ImGui-1.89-green.svg)
![Python](https://img.shields.io/badge/Python-3.8+-yellow.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

## 📋 Table des matières

- [Aperçu](#aperçu)
- [Écosystèmes](#écosystèmes)
- [Fonctionnalités](#fonctionnalités)
- [Structure du projet](#structure-du-projet)
- [Prérequis](#prérequis)
- [Installation](#installation)
- [Utilisation](#utilisation)
- [Configuration](#configuration)
- [Licence](#licence)

## 🎮 Aperçu

Cette simulation met en scène un écosystème dynamique où les populations évolvent en temps réel. Les proies cherchent de la nourriture, les prédateurs chassent, et la végétation se régénère automatiquement. Le cycle jour/nuit ajoute une dimension visuelle immersive avec un changement automatique de fond toutes les 30 secondes.

## 🌍 Écosystèmes

### 🌲 Forêt Tempérée
- **Prédateurs** : Loups (3 frames d'animation)
- **Proies** : Lapins (3 frames d'animation)
- **Végétation** : Herbe

### 🌊 Océan
- **Prédateurs** : Requins
- **Proies** : Poissons
- **Végétation** : Algues

### ✈️ Aérien *(en développement)*
- À venir prochainement

## ✨ Fonctionnalités

- 🎬 Animation fluide frame par frame (60 FPS)
- 🔄 Cycle jour/nuit automatique (30 secondes par phase)
- 🐺 Direction automatique des animaux (gauche/droite)
- 📊 Graphiques en temps réel des populations
- ⚙️ Panneau de contrôle avec pause et relance
- 🎨 Interface ImGui moderne et réactive
- 🌲 Plusieurs écosystèmes avec textures uniques

## 📁 Structure du projet

```
simulation-ecosysteme/
├── Assets/
│   ├── fonts/                  # Polices
│   ├── images/                 # Images générales
│   └── Img/
│       ├── Animaux/
│       │   ├── Modeles/        # Modèles d'animaux
│       │   └── REMOVE/         # Textures optimisées
│       ├── Background/         # Fonds jour/nuit
│       ├── Lapin_moves/
│       │   ├── ORIGINAL/       # Images originales
│       │   └── REMOVE/         # Frames animées (3 frames)
│       ├── Loup_moves/
│       │   ├── ORIGINAL/       # Images originales
│       │   └── REMOVE/         # Frames animées (3 frames)
│       └── Plantes/
│           ├── ORIGINAL/       # Images originales
│           └── REMOVE/         # Textures optimisées
├── Build/                      # Dossier de compilation
├── Externals/
│   ├── imgui/                  # Bibliothèque ImGui
│   └── SDL3/                   # Bibliothèque SDL3 + SDL3_image
├── Src/
│   ├── Core/                   # Logique principale (Main.cpp)
│   ├── Events/                 # Gestion des événements
│   ├── Graphics/               # Rendu (Renderer)
│   ├── Population/             # Logique écosystème (Animal, Proie, Predateur, Plante)
│   └── UI/                     # Interface (GUI)
├── build.py                    # Script de compilation Python
├── README.md
├── requirements.txt
└── LICENSE
```

## 🔧 Prérequis

- **Compilateur** : Clang 10+ ou GCC 9+
- **Python** : 3.8 ou supérieur
- **SDL3** : 3.0.0+ *(inclus dans Externals)*
- **SDL3_image** : 3.2.4 *(inclus dans Externals)*
- **ImGui** : 1.89+ *(inclus dans Externals)*
- **OS** : Windows 10+, macOS 10.15+, Linux (Ubuntu 20.04+)

## 📦 Installation

### Windows

```bash
# 1. Cloner le dépôt
git clone https://github.com/votre-username/simulation-ecosysteme.git
cd simulation-ecosysteme

# 2. Lancer le script de compilation
python build.py

# 3. Exécuter la simulation
Build/simulation.exe
```

### Linux / macOS

```bash
# 1. Cloner le dépôt
git clone https://github.com/votre-username/simulation-ecosysteme.git
cd simulation-ecosysteme

# 2. Lancer le script de compilation
python3 build.py

# 3. Exécuter la simulation
./Build/simulation
```

## 🚀 Utilisation

### Démarrage

1. Lancer l'exécutable
2. Le menu de **configuration** apparaît :
   - Choisir un écosystème (Forêt, Océan, Aérien)
   - Définir le nombre de proies et prédateurs
   - Ajuster le nombre de plantes et le délai de régénération
   - Cliquer **"Lancer"**

### Contrôles pendant la simulation

| Bouton | Action |
|--------|--------|
| Pause | Met la simulation en pause |
| Relancer | Redémarre avec les paramètres actuels |
| Quitter | Ferme l'application |

### Indicateurs

- **Graphiques à gauche** : Courbes des populations (vert = proies, rouge = prédateurs, bleu = plantes)
- **Panneau à droite** : Sliders et contrôles en temps réel
- **Fond** : Change automatiquement jour/nuit toutes les 30 secondes

## ⚙️ Configuration

Les paramètres sont ajustables depuis le menu de démarrage :

| Paramètre | Description | Valeur par défaut |
|-----------|-------------|-------------------|
| Écosystème | Type d'environnement | Forêt |
| Nb Proies | Nombre initial de proies | 20 |
| Nb Prédateurs | Nombre initial de prédateurs | 5 |
| Nb Plantes | Nombre initial de plantes | 30 |
| Délai Plantes | Temps de régénération (s) | 3.0 |

## 📜 Licence

Ce projet est sous licence **MIT**.

## 👥 Auteurs

- **Votre Nom** - MOUDIME MOBE MARTIN JUNIOR

## 🔗 Liens

- 📘 [Documentation](https://github.com/votre-username/simulation-ecosysteme)
- 🐛 [Signaler un bug](https://github.com/votre-username/simulation-ecosysteme/issues)
