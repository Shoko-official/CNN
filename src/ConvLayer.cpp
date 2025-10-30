#include "ConvLayer.hpp"
#include "Layer.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <random>

using namespace std;

/*
   ___               _                      
  / __|___ _ ___ __ | |   __ _ _  _ ___ _ _ 
 | (__/ _ \ ' \ V / | |__/ _` | || / -_) '_|
  \___\___/_||_\_/  |____\__,_|\_, \___|_|  
                               |__/         
 Shoko_ofi - Tous droits réservés
*/

ConvLayer::ConvLayer(int nbKernels, int kernelHeight, int kernelWidth, int inputDepth,
                     int stride, bool samePadding)
    : Layer("ConvLayer"),
      stride(stride),
      samePadding(samePadding) {
    /*
    inputDepth = Nombre de canaux d’entrée (ex : 3 RGB, sorti couche précédente : 16 si 16 filtres)
    samePadding = True (ajoute un padding) | False (sortie plus petite que entrée)
    */

    if (nbKernels <= 0 || kernelHeight <= 0 || kernelWidth <= 0 || inputDepth <= 0) {
        throw invalid_argument("Paramètres invalides pour ConvLayer : dimensions négatives ou nulles");
    }

    kernels.reserve(nbKernels);  // On réserve la mémoire de taille nbKernels (+ performant)
    for (int i = 0; i < nbKernels; ++i) {
        kernels.emplace_back(inputDepth, kernelHeight, kernelWidth); // on créer l'obj directement dans le vecteur (push_back aurait copié)
    }

    biases.resize(nbKernels, 0.0f);

    initializeWeights();
}

void ConvLayer::initializeWeights() {
    random_device rd;
    mt19937 gen(rd());
    float standDeviat = sqrt(2.0f / (kernels[0].getHeight() * kernels[0].getWidth() * kernels[0].getDepth()));
    normal_distribution<float> dist(0.0f, standDeviat);

    for (auto& kernel : kernels) {
        for (int z = 0; z < kernel.getDepth(); ++z) {
            for (int y = 0; y < kernel.getHeight(); ++y) {
                for (int x = 0; x < kernel.getWidth(); ++x) {
                    kernel.at(z, y, x) = dist(gen);
                }
            }
        }
    }
}

// Nouvelle méthode pour initialiser les gradients
void ConvLayer::initializeGradients() {
    // Initialiser les gradients des noyaux à zéro
    kernelGradients.clear();
    for (const auto& kernel : kernels) {
        kernelGradients.emplace_back(kernel.getDepth(), kernel.getHeight(), kernel.getWidth());
    }
    
    // Initialiser les gradients des biais à zéro
    biasGradients.assign(biases.size(), 0.0f);
}

// Implémentations des getters pour les poids et gradients
std::vector<Matrix3D>& ConvLayer::getKernels() {
    return kernels;
}

std::vector<Matrix3D>& ConvLayer::getKernelGradients() {
    return kernelGradients;
}

std::vector<float>& ConvLayer::getBiases() {
    return biases;
}

std::vector<float>& ConvLayer::getBiasGradients() {
    return biasGradients;
}

Matrix3D ConvLayer::forward(const Matrix3D& input) {
    if (kernels.empty()) {
        throw runtime_error("Aucun noyau initialisé dans ConvLayer");
    }

    if (input.getDepth() != kernels[0].getDepth()) {
        throw invalid_argument("Erreur : la profondeur de l'entrée ne correspond pas à celle des noyaux");
    }

    const int kernelHeight = kernels[0].getHeight();
    const int kernelWidth = kernels[0].getWidth();

    int outHeight, outWidth;

    if (samePadding) {
        outHeight = input.getHeight();
        outWidth = input.getWidth();
    } else {
        outHeight = (input.getHeight() - kernelHeight) / stride + 1;
        outWidth = (input.getWidth() - kernelWidth) / stride + 1;
    }

    Matrix3D output(static_cast<int>(kernels.size()), outHeight, outWidth);

    for (size_t k = 0; k < kernels.size(); ++k) {

        Matrix3D convResult = input.convolve(kernels[k], stride, samePadding);

        for (int y = 0; y < outHeight; ++y) {
            for (int x = 0; x < outWidth; ++x) {
                float value = convResult.at(0, y, x) + biases[k];

                output.at(static_cast<int>(k), y, x) = max(0.0f, value);
            }
        }
    }

    return output;
}

void ConvLayer::printInfo() const {
    cout << "=== " << name << " ===\n";
    cout << "Nombre de noyaux : " << kernels.size() << '\n';
    if (!kernels.empty()) {
        cout << "Taille des noyaux : "
                  << kernels[0].getDepth() << "x"
                  << kernels[0].getHeight() << "x"
                  << kernels[0].getWidth() << '\n';
    }
    cout << "Stride : " << stride << '\n';
    cout << "Padding : " << (samePadding ? "same" : "valid") << '\n';
    cout << "Biais : " << biases.size() << " valeurs\n";
}

int ConvLayer::getNumKernels() const { return static_cast<int>(kernels.size()); }
int ConvLayer::getKernelHeight() const { return kernels.empty() ? 0 : kernels[0].getHeight(); }
int ConvLayer::getKernelWidth() const { return kernels.empty() ? 0 : kernels[0].getWidth(); }
int ConvLayer::getStride() const { return stride; }
bool ConvLayer::hasSamePadding() const { return samePadding; }