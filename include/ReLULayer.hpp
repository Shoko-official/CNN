#ifndef RELULAYER_HPP
#define RELULAYER_HPP

#include "Layer.hpp"
#include "Matrix3D.hpp"

class ReLULayer : public Layer {
public:
    // Constructeur
    ReLULayer(const std::string& layerName = "ReLU");
    
    // Propagation avant
    Matrix3D forward(const Matrix3D& input) override;
    
    // Affichage des informations de la couche
    void printInfo() const override;
};

#endif