#include "FullyConnectedLayer.hpp"
#include <iostream>
#include <cmath>
#include <random>

using namespace std;

/*
  ___     _ _         ___                      _          _   _                      
 | __|  _| | |_  _   / __|___ _ _  _ _  ___ __| |_ ___ __| | | |   __ _ _  _ ___ _ _ 
 | _| || | | | || | | (__/ _ \ ' \| ' \/ -_) _|  _/ -_) _` | | |__/ _` | || / -_) '_|
 |_| \_,_|_|_|\_, |  \___\___/_||_|_||_\___\__|\__\___\__,_| |____\__,_|\_, \___|_|  
              |__/                                                      |__/                                  

 Shoko_ofi - Tous droits réservés
*/

FullyConnectedLayer::FullyConnectedLayer(int inputSize, int outputSize, const string& layerName)
    : Layer(layerName), inputSize(inputSize), outputSize(outputSize) {
    
    if (inputSize <= 0 || outputSize <= 0) {
        throw invalid_argument("FullyConnectedLayer: inputSize et outputSize doivent être positifs");
    }
    
    // Initialisation des poids et biais
    initializeWeights();
}

void FullyConnectedLayer::initializeWeights() {
    random_device rd;
    mt19937 gen(rd());
    
    // Initialisation de Xavier/Glorot
    float standDeviat = sqrt(2.0f / (inputSize + outputSize)); // 2.0f es le facteur empirique (basé sur des recherches), on calcule poids avec variance controlée = Xavier/Glorot
    normal_distribution<float> dist(0.0f, standDeviat);
    
    // Initialisation des poids
    weights.resize(outputSize, vector<float>(inputSize)); // weights = matrice, weights[i][j] représente le poids entre neuronne entée j et sortie i
    for (int i = 0; i < outputSize; ++i) {
        for (int j = 0; j < inputSize; ++j) {
            weights[i][j] = dist(gen);
        }
    }
    
    // Initialisation des biais à zéro
    biases.resize(outputSize, 0.0f);
}

Matrix3D FullyConnectedLayer::forward(const Matrix3D& input) {
    // Vérifier que l'entrée peut être aplatie à la bonne taille
    int totalElements = input.getDepth() * input.getHeight() * input.getWidth();
    if (totalElements != inputSize) {
        throw invalid_argument("FullyConnectedLayer: la taille de l'entrée ne correspond pas à inputSize");
    }
    
    // Aplatir l'entrée en un vecteur
    vector<float> flatInput(inputSize);
    int index = 0;
    for (int z = 0; z < input.getDepth(); ++z) {
        for (int y = 0; y < input.getHeight(); ++y) {
            for (int x = 0; x < input.getWidth(); ++x) {
                flatInput[index++] = input.at(z, y, x);
            }
        }
    }
    
    // Calculer la sortie: output = weights * input + biases
    vector<float> output(outputSize);
    for (int i = 0; i < outputSize; ++i) {
        output[i] = biases[i];
        for (int j = 0; j < inputSize; ++j) {
            output[i] += weights[i][j] * flatInput[j];
        }
    }
    
    // Retourner une matrice 3D de dimensions (outputSize, 1, 1)
    return Matrix3D(outputSize, 1, 1, output);
}

void FullyConnectedLayer::printInfo() const {
    cout << "=== " << name << " ===" << endl;
    cout << "Type: Fully Connected" << endl;
    cout << "Taille d'entrée: " << inputSize << endl;
    cout << "Taille de sortie: " << outputSize << endl;
    cout << "Poids: " << outputSize << "x" << inputSize << " matrice" << endl;
    cout << "Biais: " << outputSize << " valeurs" << endl;
}

int FullyConnectedLayer::getInputSize() const {
    return inputSize;
}

int FullyConnectedLayer::getOutputSize() const {
    return outputSize;
}