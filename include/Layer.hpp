#ifndef LAYER_HPP
#define LAYER_HPP

#include <vector>
#include <iostream>
#include <stdexcept>
#include "Matrix3D.hpp"

/**
Cette classe sert de classe de base pour toutes les couches d’un réseau de neurones (par exemple : 
couche dense, convolution, pooling, etc.). 

Elle définit une interface commune que toutes les couches doivent respecter :
- une méthode `forward()` pour effectuer la propagation avant,
- une méthode `printInfo()` pour afficher des informations sur la couche,
- un nom identifiant la couche.

L'objectif de cette abstraction est de permettre à un réseau (comme AlexNet, LeNet, etc.)
de manipuler un ensemble de couches différentes via un même type (`Layer*`), 
grâce au polymorphisme.
 */

class Layer {
protected:
    std::string name;

public:
/*
    Exemple de nom :
    - DenseLayer
    - ConvLayer
    - ReLULayer
     */
    Layer(const std::string& layerName = "Layer") : name(layerName) {}

    virtual ~Layer() {}

    /**
    Cette fonction représente le calcul effectué par la couche lors du passage des données :
    - Exemple pour une couche dense : `output = activation(Winput + b)`
    - Exemple pour une couche convolutionnelle : convolution + activation

    input : Données d’entrée de la couche
     */
    virtual Matrix3D forward(const Matrix3D& input) = 0;

    virtual void printInfo() const {
        std::cout << "Layer: " << name << std::endl; // Pour des classes dérivées, on pourra afficher poid, forme entrée sortie..
    }

    std::string getName() const { return name; }

};

#endif
