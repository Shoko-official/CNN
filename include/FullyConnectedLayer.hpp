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
    
    // Ajout des gradients pour la rétropropagation
    std::vector<std::vector<float>> weightGradients;  // Gradients des poids
    std::vector<float> biasGradients;                // Gradients des biais

public:
    // Constructeur
    FullyConnectedLayer(int inputSize, int outputSize, const std::string& layerName = "FullyConnected");
    
    // Propagation avant
    Matrix3D forward(const Matrix3D& input) override;
    
    // Initialisation des poids et biais
    void initializeWeights();
    
    // Initialisation des gradients (à appeler avant la rétropropagation)
    void initializeGradients();
    
    // Affichage des informations de la couche
    void printInfo() const override;
    
    // Getters pour les poids et gradients
    std::vector<std::vector<float>>& getWeights();
    std::vector<std::vector<float>>& getWeightGradients();
    std::vector<float>& getBiases();
    std::vector<float>& getBiasGradients();
    
    // Getters existants
    int getInputSize() const;
    int getOutputSize() const;
};

#endif