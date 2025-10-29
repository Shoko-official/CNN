#include "PoolingLayer.hpp"
#include <iostream>

/*
  ___          _ _             _                      
 | _ \___  ___| (_)_ _  __ _  | |   __ _ _  _ ___ _ _ 
 |  _/ _ \/ _ \ | | ' \/ _` | | |__/ _` | || / -_) '_|
 |_| \___/\___/_|_|_||_\__, | |____\__,_|\_, \___|_|  
                       |___/             |__/              
 Shoko_ofi - Tous droits réservés
*/

PoolingLayer::PoolingLayer(int poolSize, int stride, const std::string& layerName)
    : Layer(layerName), poolSize(poolSize), stride(stride) {
    if (poolSize <= 0 || stride <= 0) {
        throw std::invalid_argument("PoolingLayer: poolSize et stride doivent être positifs");
    }
}

Matrix3D PoolingLayer::forward(const Matrix3D& input) {
    // Applique le max pooling avec les paramètres de la couche
    return input.maxPool(poolSize, stride);
}

void PoolingLayer::printInfo() const {
    std::cout << "=== " << name << " ===" << std::endl;
    std::cout << "Type: Max Pooling" << std::endl;
    std::cout << "Taille du pool: " << poolSize << "x" << poolSize << std::endl;
    std::cout << "Stride: " << stride << std::endl;
}

int PoolingLayer::getPoolSize() const {
    return poolSize;
}

int PoolingLayer::getStride() const {
    return stride;
}