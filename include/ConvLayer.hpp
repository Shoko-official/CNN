#ifndef CONVLAYER_HPP
#define CONVLAYER_HPP

#include "Layer.hpp"
#include "Matrix3D.hpp"
#include <vector>
#include <random>
#include <string>

class ConvLayer : public Layer {
private:
    std::vector<Matrix3D> kernels;
    std::vector<float> biases;
    int stride;
    bool samePadding;
    
    // Ajout des gradients pour la rétropropagation
    std::vector<Matrix3D> kernelGradients;  // Gradients des noyaux
    std::vector<float> biasGradients;       // Gradients des biais

public:
    // Constructeur
    ConvLayer(int numKernels, int kernelHeight, int kernelWidth, int inputDepth, 
              int stride = 1, bool samePadding = false);

    // Propagation avant
    Matrix3D forward(const Matrix3D& input) override;

    // Initialisation des poids et biais
    void initializeWeights();
    
    // Initialisation des gradients (à appeler avant la rétropropagation)
    void initializeGradients();

    // Affichage des informations de la couche
    void printInfo() const override;

    // Getters pour les poids et gradients
    std::vector<Matrix3D>& getKernels();
    std::vector<Matrix3D>& getKernelGradients();
    std::vector<float>& getBiases();
    std::vector<float>& getBiasGradients();
    
    // Getters existants
    int getNumKernels() const;
    int getKernelHeight() const;
    int getKernelWidth() const;
    int getStride() const;
    bool hasSamePadding() const;
};

#endif // CONVLAYER_HPP