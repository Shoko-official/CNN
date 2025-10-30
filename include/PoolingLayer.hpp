#ifndef POOLLAYER_HPP
#define POOLLAYER_HPP

#include "Layer.hpp"
#include "Matrix3D.hpp"

class PoolingLayer : public Layer {
private:
    int poolSize;
    int stride;

public:
    // Constructeur
    PoolingLayer(int poolSize, int stride = 1, const std::string& layerName = "MaxPooling");
    
    // Propagation avant
    Matrix3D forward(const Matrix3D& input) override;
    
    // Affichage des informations de la couche
    void printInfo() const override;
    
    // Getters
    int getPoolSize() const;
    int getStride() const;
};

#endif