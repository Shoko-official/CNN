#include "ReLULayer.hpp"
#include <iostream>

/*
  ___     _   _   _   _                      
 | _ \___| | | | | | | |   __ _ _  _ ___ _ _ 
 |   / -_) |_| |_| | | |__/ _` | || / -_) '_|
 |_|_\___|____\___/  |____\__,_|\_, \___|_|  
                                |__/                  
 Shoko_ofi - Tous droits réservés
*/

ReLULayer::ReLULayer(const std::string& layerName) 
    : Layer(layerName) {
}

Matrix3D ReLULayer::forward(const Matrix3D& input) {
    // Applique la fonction ReLU: output(d,i,j) = max(0, input(d, i, j))
    return input.ReLU();
}

void ReLULayer::printInfo() const {
    std::cout << "=== " << name << " ===" << std::endl;
    std::cout << "Type: Activation ReLU" << std::endl;
}