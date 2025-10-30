#ifndef OPTIMIZER_HPP
#define OPTIMIZER_HPP

#include "ConvLayer.hpp"
#include "FullyConnectedLayer.hpp"
#include <vector>

class Optimizer {
public:
    virtual ~Optimizer() {}
    virtual void update(ConvLayer& layer, float lr) = 0;
    virtual void update(FullyConnectedLayer& layer, float lr) = 0;
};

class SGD : public Optimizer {
public:
    void update(ConvLayer& layer, float lr) override;
    void update(FullyConnectedLayer& layer, float lr) override;
};

class Adam : public Optimizer {
private:
    float beta1;
    float beta2;
    float epsilon;
    int t; // Pas de temps
    
    // Stockage des moments pour ConvLayer
    std::vector<std::vector<std::vector<float>>> m_conv_kernels; 
    std::vector<std::vector<std::vector<float>>> v_conv_kernels; 
    std::vector<float> m_conv_biases;     
    std::vector<float> v_conv_biases;     
    
    // Stockage des moments pour FullyConnectedLayer
    std::vector<std::vector<float>> m_fc_weights; 
    std::vector<std::vector<float>> v_fc_weights; 
    std::vector<float> m_fc_biases;              
    std::vector<float> v_fc_biases;              
    
    // Indicateurs pour savoir si les moments ont été initialisés
    bool conv_initialized;
    bool fc_initialized;

public:
    Adam(float beta1 = 0.9f, float beta2 = 0.999f, float epsilon = 1e-8f);
    void update(ConvLayer& layer, float lr) override;
    void update(FullyConnectedLayer& layer, float lr) override;
};

#endif // OPTIMIZER_HPP