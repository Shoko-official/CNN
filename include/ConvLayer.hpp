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

public:
    // Constructeur
    ConvLayer(int numKernels, int kernelHeight, int kernelWidth, int inputDepth, 
              int stride = 1, bool samePadding = false);

    // Propagation avant
    Matrix3D forward(const Matrix3D& input) override;

    // Initialisation des poids et biais
    void initializeWeights();

    // Affichage des informations de la couche
    void printInfo() const override;

    // Getters
    int getNumKernels() const;
    int getKernelHeight() const;
    int getKernelWidth() const;
    int getStride() const;
    bool hasSamePadding() const;
};

#endif // CONVLAYER_HPP
