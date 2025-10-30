#include "Optimizer.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>

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
    : beta1(beta1), beta2(beta2), epsilon(epsilon), t(0), conv_initialized(false), fc_initialized(false) {
}

void Adam::update(ConvLayer& layer, float lr) {
    t++;
    
    auto& kernels = layer.getKernels();
    auto& kernelGradients = layer.getKernelGradients();
    auto& biases = layer.getBiases();
    auto& biasGradients = layer.getBiasGradients();
    
    // Initialiser les moments si nécessaire
    if (!conv_initialized) {
        m_conv_kernels.resize(kernels.size());
        v_conv_kernels.resize(kernels.size());
        
        for (size_t k = 0; k < kernels.size(); ++k) {
            m_conv_kernels[k].resize(kernels[k].getDepth());
            v_conv_kernels[k].resize(kernels[k].getDepth());
            
            for (int z = 0; z < kernels[k].getDepth(); ++z) {
                m_conv_kernels[k][z].assign(kernels[k].getHeight() * kernels[k].getWidth(), 0.0f);
                v_conv_kernels[k][z].assign(kernels[k].getHeight() * kernels[k].getWidth(), 0.0f);
            }
        }
        
        m_conv_biases.assign(biases.size(), 0.0f);
        v_conv_biases.assign(biases.size(), 0.0f);
        
        conv_initialized = true;
    }
    
    // Mise à jour des noyaux
    for (size_t k = 0; k < kernels.size(); ++k) {
        for (int z = 0; z < kernels[k].getDepth(); ++z) {
            for (int y = 0; y < kernels[k].getHeight(); ++y) {
                for (int x = 0; x < kernels[k].getWidth(); ++x) {
                }
            }
        }
    }
    
    // Mise à jour des biais
    for (size_t i = 0; i < biases.size(); ++i) {

    }
}

void Adam::update(FullyConnectedLayer& layer, float lr) {
    t++;
    
    auto& weights = layer.getWeights();
    auto& weightGradients = layer.getWeightGradients();
    auto& biases = layer.getBiases();
    auto& biasGradients = layer.getBiasGradients();
    
    // Initialiser les moments si nécessaire
    if (!fc_initialized) {
        m_fc_weights.resize(weights.size());
        v_fc_weights.resize(weights.size());
        
        for (size_t i = 0; i < weights.size(); ++i) {
            m_fc_weights[i].assign(weights[i].size(), 0.0f);
            v_fc_weights[i].assign(weights[i].size(), 0.0f);
        }
        
        m_fc_biases.assign(biases.size(), 0.0f);
        v_fc_biases.assign(biases.size(), 0.0f);
        
        fc_initialized = true;
    }
    
    // Ajouter : mise à jour des poids
}


// watching vidéo : https://www.youtube.com/watch?v=NE88eqLngkg