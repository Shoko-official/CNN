class Optimizer {
public:
    virtual void update(ConvLayer& layer, float lr) = 0;
    virtual void update(FullyConnectedLayer& layer, float lr) = 0;
    // ... autres couches
};

class SGD : public Optimizer {
    // Implémentation : poids = poids - lr * gradient
};

class Adam : public Optimizer {
    // Implémentation avec moments du 1er/2ème ordre
};