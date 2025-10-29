#ifndef MATRIX3D_HPP
#define MATRIX3D_HPP

#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>

using namespace std;

class Matrix3D {
private:
    int depth;
    int height;
    int width;
    vector<float> data;

public:
    // --- Constructeur ---
    Matrix3D(int d, int h, int w, const vector<float>& values);
    Matrix3D(int d, int h, int w); // Constructeur avec initialisation à zéro

    // --- Accès ---
    float at(int z, int y, int x) const;
    float& at(int z, int y, int x);

    // --- Getters ---
    int getDepth() const;
    int getHeight() const;
    int getWidth() const;

    // --- Opérations principales ---
    Matrix3D convolve(const Matrix3D& kernel, int stride = 1, bool samePadding = false) const;
    Matrix3D maxPool(int poolSize, int stride = 1) const;
    Matrix3D ReLU() const;

    // --- Affichage ---
    void print() const;
};

#endif