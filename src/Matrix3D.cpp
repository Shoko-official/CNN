#include "Matrix3D.hpp"
#include <limits> // numeric_limits<float>

/*
  __  __      _       _       ____    _ 
 |  \/  |__ _| |_ _ _(_)_ __ |__ / __| |
 | |\/| / _` |  _| '_| \ \ /  |_ \/ _` |
 |_|  |_\__,_|\__|_| |_/_\_\ |___/\__,_|
                                                
 Shoko_ofi tout droits réservés
*/

// --- Constructeur ---
Matrix3D::Matrix3D(int d, int h, int w, const vector<float>& values)
    : depth(d), height(h), width(w), data(values)
{
    if (values.size() != static_cast<size_t>(d * h * w)) {
        throw invalid_argument("Erreur : La taille des donnees ne correspond pas aux dimensions de la matrice.");
    }
}

Matrix3D::Matrix3D(int d, int h, int w)
    : depth(d), height(h), width(w), data(d * h * w, 0.0f)
{
    // Initialisation à zéro
}

// --- Accès ---
float Matrix3D::at(int z, int y, int x) const {
    if (z < 0 || z >= depth || y < 0 || y >= height || x < 0 || x >= width)
        throw out_of_range("Erreur : Indice hors limites");
    return data[z * height * width + y * width + x];
}

float& Matrix3D::at(int z, int y, int x) {
    if (z < 0 || z >= depth || y < 0 || y >= height || x < 0 || x >= width)
        throw out_of_range("Erreur : Indice hors limites");
    return data[z * height * width + y * width + x];
}

// --- Getters ---
int Matrix3D::getDepth() const { return depth; }
int Matrix3D::getHeight() const { return height; }
int Matrix3D::getWidth() const { return width; }

// --- Convolution (Cross-Correlation pour CNN) ---
Matrix3D Matrix3D::convolve(const Matrix3D& kernel, int stride, bool samePadding) const {
    int outDepth = depth; // une carte de sortie par couche d'entrée
    int outHeight, outWidth;
    int paddingTop = 0, paddingLeft = 0;

    if (samePadding) {
        // Calcul correct du padding pour kernels pairs et impairs
        // Pour un kernel de taille k, on ajoute (k-1) pixels de padding au total
        int totalPaddingHeight = kernel.getHeight() - 1;
        int totalPaddingWidth = kernel.getWidth() - 1;
        
        // Répartition du padding (plus en bas/droite pour les kernels pairs)
        paddingTop = totalPaddingHeight / 2;
        paddingLeft = totalPaddingWidth / 2;
        
        outHeight = height;
        outWidth = width;
    } else {
        outHeight = (height - kernel.getHeight()) / stride + 1;
        outWidth = (width - kernel.getWidth()) / stride + 1;
    }

    vector<float> outData(outDepth * outHeight * outWidth, 0.0f);

    for (int z = 0; z < outDepth; ++z) {
        for (int y = 0; y < outHeight; ++y) {
            for (int x = 0; x < outWidth; ++x) {
                float sum = 0.0f;
                
                for (int ky = 0; ky < kernel.getHeight(); ++ky) {
                    for (int kx = 0; kx < kernel.getWidth(); ++kx) {
                        int ny = y * stride + ky - paddingTop;
                        int nx = x * stride + kx - paddingLeft;
                        
                        // Gestion du padding implicite (valeurs hors limites = 0)
                        if (ny >= 0 && ny < height && nx >= 0 && nx < width) {
                            sum += at(z, ny, nx) * kernel.at(0, ky, kx);
                        }
                    }
                }
                
                outData[z * outHeight * outWidth + y * outWidth + x] = sum;
            }
        }
    }

    return Matrix3D(outDepth, outHeight, outWidth, outData);
}

// --- ReLU ---
Matrix3D Matrix3D::ReLU() const {
    // valeurs négatives deviennent 0
    vector<float> outData(data.size());
    
    for (size_t i = 0; i < data.size(); ++i) {
        outData[i] = max(0.0f, data[i]);
    }
    
    return Matrix3D(depth, height, width, outData);
}

// --- Max Pooling ---
Matrix3D Matrix3D::maxPool(int poolSize, int stride) const {
    if (poolSize <= 0 || stride <= 0) {
        throw std::invalid_argument("maxPool: poolSize et stride doivent être > 0.");
    }
    
    int outDepth = depth;
    
    // Formule corrigée pour calculer la taille de sortie
    int outHeight = (height - poolSize) / stride + 1;
    int outWidth = (width - poolSize) / stride + 1;
    
    // Ajustement pour les cas où le dépassement est autorisé
    if ((height - poolSize) % stride != 0) outHeight++;
    if ((width - poolSize) % stride != 0) outWidth++;

    vector<float> outData(outDepth * outHeight * outWidth, 0.0f);

    for (int z = 0; z < outDepth; ++z) {
        for (int oy = 0; oy < outHeight; ++oy) {
            for (int ox = 0; ox < outWidth; ++ox) {
                float maxVal = std::numeric_limits<float>::lowest();
                
                for (int dy = 0; dy < poolSize; ++dy) {
                    for (int dx = 0; dx < poolSize; ++dx) {
                        int inY = oy * stride + dy;
                        int inX = ox * stride + dx;
                        
                        if (inY < height && inX < width) {
                            maxVal = std::max(maxVal, at(z, inY, inX));
                        }
                    }
                }
                
                outData[z * outHeight * outWidth + oy * outWidth + ox] = maxVal;
            }
        }
    }

    return Matrix3D(outDepth, outHeight, outWidth, outData);
}

// --- Affichage ---
void Matrix3D::print() const {
    for (int z = 0; z < depth; ++z) {
        cout << "Couche " << z << " :" << endl;
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                cout << at(z, y, x) << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}