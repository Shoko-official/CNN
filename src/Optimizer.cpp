#include "Optimizer.hpp"
#include <iostream>
#include <cmath>

// Implémentation de SGD
void SGD::update(ConvLayer& layer, float lr) {
}

void SGD::update(FullyConnectedLayer& layer, float lr) {
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