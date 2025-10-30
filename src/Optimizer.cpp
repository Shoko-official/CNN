#include "Optimizer.hpp"
#include <iostream>
#include <cmath>

// Implémentation de SGD
void SGD::update(ConvLayer& layer, float lr) {
    // Mise à jour des noyaux
    auto& kernels = layer.getKernels();
    auto& kernelGradients = layer.getKernelGradients();
    
    for (size_t k = 0; k < kernels.size(); ++k) {
        for (int z = 0; z < kernels[k].getDepth(); ++z) {
            for (int y = 0; y < kernels[k].getHeight(); ++y) {
                for (int x = 0; x < kernels[k].getWidth(); ++x) {
                    kernels[k].at(z, y, x) -= lr * kernelGradients[k].at(z, y, x);
                }
            }
        }
    }
    
    // Mise à jour des biais
    auto& biases = layer.getBiases();
    auto& biasGradients = layer.getBiasGradients();
    
    for (size_t i = 0; i < biases.size(); ++i) {
        biases[i] -= lr * biasGradients[i];
    }
}

void SGD::update(FullyConnectedLayer& layer, float lr) {
    // Mise à jour des poids
    auto& weights = layer.getWeights();
    auto& weightGradients = layer.getWeightGradients();
    
    for (int i = 0; i < layer.getOutputSize(); ++i) {
        for (int j = 0; j < layer.getInputSize(); ++j) {
            weights[i][j] -= lr * weightGradients[i][j];
        }
    }
    
    // Mise à jour des biais
    auto& biases = layer.getBiases();
    auto& biasGradients = layer.getBiasGradients();
    
    for (int i = 0; i < layer.getOutputSize(); ++i) {
        biases[i] -= lr * biasGradients[i];
    }
}

// Implémentation de Adam
Adam::Adam(float beta1, float beta2, float epsilon) 
    : beta1(beta1), beta2(beta2), epsilon(epsilon), t(0) {
}

Adam::~Adam() {
}

void Adam::update(ConvLayer& layer, float lr) {
}

void Adam::update(FullyConnectedLayer& layer, float lr) {
}