#ifndef OPTIMIZER_HPP
#define OPTIMIZER_HPP

#include "ConvLayer.hpp"
#include "FullyConnectedLayer.hpp"

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
    float* m_weights; // Moment du premier ordre
    float* v_weights; // Moment du second ordre
    float* m_bias;
    float* v_bias;
    int t; // Pas de temps

public:
    Adam(float beta1 = 0.9f, float beta2 = 0.999f, float epsilon = 1e-8f);
    ~Adam();
    void update(ConvLayer& layer, float lr) override;
    void update(FullyConnectedLayer& layer, float lr) override;
};

#endif