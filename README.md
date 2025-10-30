# CNN :

### Description
Ce projet est une implémentation en C++ d'un réseau de neurones convolutif (CNN). Il fournit les fonctionnalités de base pour le traitement d'images avec des opérations de convolution, de pooling et d'activation, ainsi qu'une suite complète de tests unitaires pour valider chaque composant.

### Structure du projet

```
📁 CNN-Shoko_official/
├── 📁 build/                       # Répertoire de compilation (généré)
├── 📄 Explications.md              # Explications détaillées des techniques
├── 📄 Formules.md                  # Référence mathématique complète
├── 📁 include/
│   ├── 📄 Color.hpp                # Utilitaires pour la coloration de sortie console
│   ├── 📄 ConvLayer.hpp            # Couche de convolution
│   ├── 📄 FullyConnectedLayer.hpp  # Couche entièrement connectée
│   ├── 📄 Layer.hpp                # Classe de base pour les couches du réseau
│   ├── 📄 Matrix3D.hpp             # Classe pour la manipulation de matrices 3D
│   ├── 📄 PoolingLayer.hpp         # Couche de pooling
│   └── 📄 ReLULayer.hpp            # Couche d'activation ReLU
├── 📄 License.txt                  # Fichier contenant la licence du projet
├── 📄 Makefile                     # Système de compilation
├── 📄 README.md                    # Ce fichier
└── 📁 src/
    ├── 📄 ConvLayer.cpp            # Implémentation de la couche de convolution
    ├── 📄 FullyConnectedLayer.cpp  # Implémentation de la couche entièrement connectée
    ├── 📄 main.cpp                 # Programme principal avec tests unitaires
    ├── 📄 Matrix3D.cpp             # Implémentation des opérations matricielles
    ├── 📄 PoolingLayer.cpp         # Implémentation de la couche de pooling
    └── 📄 ReLULayer.cpp            # Implémentation de la couche d'activation ReLU
```

### Fonctionnalités
- **Manipulation de matrices 3D** : Représentation efficace des données d'entrée et feature maps avec indexation linéaire
- **Opérations de convolution** : Application de noyaux avec support pour stride et padding (same/valid)
- **Max Pooling** : Réduction dimensionnelle avec conservation des caractéristiques importantes
- **Activation ReLU** : Fonction d'activation non linéaire intégrée aux couches
- **Couches entièrement connectées** : Couches denses pour la classification finale
- **Architecture modulaire** : Classes polymorphes pour une extension facile
- **Initialisation des poids** : Méthode Xavier/Glorot pour une convergence stable
- **Tests unitaires complets** : Validation systématique de chaque composant

### Compilation et exécution

#### Compilation avec Makefile
```bash
make clean    # Nettoie les fichiers de compilation
make          # Compile le projet
make run      # Compile et exécute le programme
make debug    # Compile en mode debug
```

#### Compilation manuelle
```bash
g++ src/Matrix3D.cpp src/ConvLayer.cpp src/ReLULayer.cpp src/PoolingLayer.cpp src/FullyConnectedLayer.cpp src/main.cpp -o alexnet -I./include
```

#### Options d'exécution
```bash
./alexnet          # Mode normal (affiche les résultats des tests)
./alexnet -v       # Mode verbeux (affiche tous les détails)
./alexnet -q       # Mode silencieux (affiche seulement le résumé)
./alexnet -h       # Affiche l'aide
```

#### Jamais utilisé Make ? (Sous Windows avec WSL)

```bash
# 1. Installer WSL depuis PowerShell en mode administrateur
wsl --install

# 2. Lancer Ubuntu (depuis le menu Windows : tapez "Ubuntu")
sudo apt update
sudo apt install build-essential  # Installe les outils de compilation (gcc, make, etc.)

# 3. Accéder au répertoire du projet
# Remplacez le chemin par celui où se trouve votre projet
# Note : Les disques Windows apparaissent sous /mnt/, par ex. C: → /mnt/c/
cd /mnt/c/Chemin/Vers/CNN-Shoko_official

# 4. Compiler et exécuter le projet avec Make
make run      # Compile et lance le programme
# ou
make          # Compile seulement
./alexnet -q  # Exécute en mode silencieux (résumé uniquement)
```

### Exemple d'utilisation
Le programme principal (`main.cpp`) possède une suite de tests unitaires :
1. **Tests de convolution** : Validation des opérations avec et sans padding
2. **Tests de max pooling** : Vérification de la réduction dimensionnelle
3. **Tests d'activation ReLU** : Validation de la fonction non linéaire
4. **Tests combinés** : Enchaînement des opérations
5. **Tests des couches** : Validation de chaque type de couche (Conv, ReLU, Pooling...)

### Documentation technique
- **Formules.md** : Contenant des référence mathématique utiles pour comprendre le code (initialisation, convolution, activation, backpropagation)
- **Explications.md** : Détails techniques sur l'indexation linéaire et les astuces de calcul

### Développement futur
- Implémentation complète de l'architecture AlexNet (normalisation, dropout)
- Ajout des fonctionnalités d'entraînement (rétropropagation, optimisation)
- Support pour le chargement et prétraitement d'images réelles
- Intégration avec des bibliothèques de calcul (BLAS, Eigen)
- Sauvegarde/chargement des modèles entraînés

### Licence
Ce projet est sous licence personnalisée. Voir le fichier `License.txt` pour plus de détails.

### Auteur
Projet réalisé par Shoko_official.  
GitHub : https://github.com/Shoko-official/AlexNet

### PS : Toutes suggestions d'amélioration, contribution sera la bienvenue. Je suis ouvert à toute forme de collaboration, ou simple question technique ;)
