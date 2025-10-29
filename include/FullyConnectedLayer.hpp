#ifndef FULLYCONNECTEDLAYER_HPP
#define FULLYCONNECTEDLAYER_HPP

#include "Layer.hpp"
#include "Matrix3D.hpp"
#include <vector>

class FullyConnectedLayer : public Layer {
private:
    int inputSize;
    int outputSize;
    std::vector<std::vector<float>> weights;
    std::vector<float> biases;

public:
    // Constructeur
    FullyConnectedLayer(int inputSize, int outputSize, const std::string& layerName = "FullyConnected");
    
    // Propagation avant
    Matrix3D forward(const Matrix3D& input) override;
    
    // Initialisation des poids et biais
    void initializeWeights();
    
    // Affichage des informations de la couche
    void printInfo() const override;
    
    // Getters
    int getInputSize() const;
    int getOutputSize() const;
};

#endif // FULLYCONNECTEDLAYER_HPP