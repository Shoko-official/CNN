#include "Matrix3D.hpp"
#include "Color.hpp"
#include "ConvLayer.hpp"
#include "ReLULayer.hpp"
#include "PoolingLayer.hpp"
#include "FullyConnectedLayer.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <random>

using namespace ConsoleColor;
using namespace std;

/*
  _____       _      
 |_   _|__ __| |_ ___
   | |/ -_|_-<  _(_-<
   |_|\___/__/\__/__/

  Shoko_ofi tout droits réservés
*/

// Modes d'affichage
enum class Mode { VERBOSE, NORMAL, QUIET };
Mode currentMode = Mode::NORMAL;

// Compteurs de tests
int totalTests = 0;
int passedTests = 0;
int failedTests = 0;

// Fonctions d'affichage conditionnelles
void printVerbose(const string& message) {
    if (currentMode == Mode::VERBOSE) {
        cout << "[VERBOSE] " << message << endl;
    }
}

void printNormal(const string& message) {
    if (currentMode != Mode::QUIET) {
        cout << message << endl;
    }
}

void printError(const string& message) {
    if (currentMode != Mode::QUIET) {
        cout << ROUGE << "[ERREUR] " << RESET << message << endl;
    }
}

void printSuccess(const string& message) {
    if (currentMode != Mode::QUIET) {
        cout << VERT << "[SUCCÈS] " << RESET << message << endl;
    }
}

// Fonction de comparaison de matrices avec tolérance
bool areMatricesEqual(const Matrix3D& a, const Matrix3D& b, float tolerance = 1e-5) {
    if (a.getDepth() != b.getDepth() || 
        a.getHeight() != b.getHeight() || 
        a.getWidth() != b.getWidth()) {
        return false;
    }
    
    for (int z = 0; z < a.getDepth(); ++z) {
        for (int y = 0; y < a.getHeight(); ++y) {
            for (int x = 0; x < a.getWidth(); ++x) {
                if (fabs(a.at(z, y, x) - b.at(z, y, x)) > tolerance) {
                    return false;
                }
            }
        }
    }
    return true;
}

// Fonctions de test
void testConvolution() {
    printVerbose("Test de convolution...");
    
    // Cas de test 1: Convolution simple
    {
        vector<float> inputValues = {
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
        };
        Matrix3D input(1, 3, 3, inputValues);
        
        vector<float> kernelValues = {
            1, 0,
            0, -1
        };
        Matrix3D kernel(1, 2, 2, kernelValues);
        
        // Valeurs attendues corrigées
        vector<float> expectedValues = {
            -4, -4,
            -4, -4
        };
        Matrix3D expected(1, 2, 2, expectedValues);
        
        Matrix3D result = input.convolve(kernel);
        
        totalTests++;
        if (areMatricesEqual(result, expected)) {
            printSuccess("Convolution simple");
            passedTests++;
        } else {
            printError("Convolution simple: FAILED");
            printNormal("Résultat attendu:");
            expected.print();
            printNormal("Résultat obtenu:");
            result.print();
            failedTests++;
        }
    }
    
    // Cas de test 2: Convolution avec padding
    {
        vector<float> inputValues = {
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
        };
        Matrix3D input(1, 3, 3, inputValues);
        
        vector<float> kernelValues = {
            1, 0,
            -1, 2
        };
        Matrix3D kernel(1, 2, 2, kernelValues);
        
        // Valeurs attendues corrigées
        vector<float> expectedValues = {
            7, 9, -3,
            13, 15, -3,
            7, 8, 9
        };
        Matrix3D expected(1, 3, 3, expectedValues);
        
        Matrix3D result = input.convolve(kernel, 1, true);
        
        totalTests++;
        if (areMatricesEqual(result, expected)) {
            printSuccess("Convolution avec padding");
            passedTests++;
        } else {
            printError("Convolution avec padding: FAILED");
            failedTests++;
        }
    }
}

void testMaxPooling() {
    printVerbose("Test de Max Pooling...");
    
    // Cas de test 1: Max Pooling simple
    {
        vector<float> inputValues = {
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16
        };
        Matrix3D input(1, 4, 4, inputValues);
        
        vector<float> expectedValues = {
            6, 8,
            14, 16
        };
        Matrix3D expected(1, 2, 2, expectedValues);
        
        Matrix3D result = input.maxPool(2, 2);
        
        totalTests++;
        if (areMatricesEqual(result, expected)) {
            printSuccess("Max Pooling simple");
            passedTests++;
        } else {
            printError("Max Pooling simple: FAILED");
            failedTests++;
        }
    }
    
    // Cas de test 2: Max Pooling avec stride
    {
        vector<float> inputValues = {
            1, 2, 3, 4, 5,
            6, 7, 8, 9, 10,
            11, 12, 13, 14, 15,
            16, 17, 18, 19, 20
        };
        Matrix3D input(1, 4, 5, inputValues);
        
        vector<float> expectedValues = {
            7, 9, 10,
            17, 19, 20
        };
        Matrix3D expected(1, 2, 3, expectedValues);
        
        Matrix3D result = input.maxPool(2, 2);
        
        totalTests++;
        if (areMatricesEqual(result, expected)) {
            printSuccess("Max Pooling avec stride");
            passedTests++;
        } else {
            printError("Max Pooling avec stride: FAILED");
            failedTests++;
        }
    }
}

void testReLU() {
    printVerbose("Test de ReLU...");
    
    // Cas de test 1: ReLU simple
    {
        vector<float> inputValues = {
            -1, 2, -3,
            4, -5, 6
        };
        Matrix3D input(1, 2, 3, inputValues);
        
        vector<float> expectedValues = {
            0, 2, 0,
            4, 0, 6
        };
        Matrix3D expected(1, 2, 3, expectedValues);
        
        Matrix3D result = input.ReLU();
        
        totalTests++;
        if (areMatricesEqual(result, expected)) {
            printSuccess("ReLU simple");
            passedTests++;
        } else {
            printError("ReLU simple: FAILED");
            failedTests++;
        }
    }
    
    // Cas de test 2: ReLU avec toutes valeurs positives
    {
        vector<float> inputValues = {
            1, 2, 3,
            4, 5, 6
        };
        Matrix3D input(1, 2, 3, inputValues);
        
        Matrix3D result = input.ReLU();
        
        totalTests++;
        if (areMatricesEqual(result, input)) {
            printSuccess("ReLU valeurs positives");
            passedTests++;
        } else {
            printError("ReLU valeurs positives: FAILED");
            failedTests++;
        }
    }
}

void testCombinations() {
    printVerbose("Test de combinaisons d'opérations...");
    
    // Cas de test: Convolution + ReLU + Max Pooling
    {
        vector<float> inputValues = {
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16
        };
        Matrix3D input(1, 4, 4, inputValues);
        
        vector<float> kernelValues = {
            1, 0,
            0, -1
        };
        Matrix3D kernel(1, 2, 2, kernelValues);
        
        // Opérations enchaînées
        Matrix3D conv = input.convolve(kernel);
        Matrix3D relu = conv.ReLU();
        Matrix3D pooled = relu.maxPool(2, 2);
        
        // Valeurs attendues corrigées
        vector<float> expectedValues = {
            0, 0,
            0, 0
        };
        Matrix3D expected(1, 2, 2, expectedValues);
        
        totalTests++;
        if (areMatricesEqual(pooled, expected)) {
            printSuccess("Combinaison d'opérations");
            passedTests++;
        } else {
            printError("Combinaison d'opérations: FAILED");
            failedTests++;
        }
    }
}

void testConvLayer(){
    printVerbose("Test de Convolution Layer...");
    
    try {
        // Cas de test 1: Création et propagation simple
        {
            vector<float> inputValues = {
                1, 2, 3,
                4, 5, 6,
                7, 8, 9
            };
            Matrix3D input(1, 3, 3, inputValues);
            
            // Création d'une couche de convolution
            ConvLayer convLayer(1, 2, 2, 1, 1, false); // 1 noyau 2x2, stride=1, pas de padding
            
            // Propagation avant
            Matrix3D output = convLayer.forward(input);
            
            // Vérification des dimensions
            totalTests++;
            if (output.getDepth() == 1 && output.getHeight() == 2 && output.getWidth() == 2) {
                printSuccess("ConvLayer dimensions");
                passedTests++;
            } else {
                printError("ConvLayer dimensions: FAILED");
                failedTests++;
            }
            
            // Affichage des informations
            if (currentMode == Mode::VERBOSE) {
                convLayer.printInfo();
                cout << "Output:" << endl;
                output.print();
            }
        }
        
        // Cas de test 2: Test avec plusieurs noyaux
        {
            Matrix3D input(3, 5, 5); // Input 3x5x5
            
            // Création d'une couche avec plusieurs noyaux
            ConvLayer convLayer(4, 3, 3, 3, 1, true); // 4 noyaux 3x3, stride=1, padding=same
            
            // Propagation avant
            Matrix3D output = convLayer.forward(input);
            
            // Vérification des dimensions
            totalTests++;
            if (output.getDepth() == 4 && output.getHeight() == 5 && output.getWidth() == 5) {
                printSuccess("ConvLayer multiple kernels");
                passedTests++;
            } else {
                printError("ConvLayer multiple kernels: FAILED");
                failedTests++;
            }
        }
        
        // Cas de test 3: Test d'erreur de dimensions
        {
            vector<float> inputValues = {1, 2, 3, 4};
            Matrix3D input(2, 2, 1, inputValues); // Profondeur 2
            
            // Création d'une couche avec profondeur incompatible
            ConvLayer convLayer(1, 2, 2, 3, 1, false); // Attend profondeur 3
            
            // Doit lever une exception
            totalTests++;
            try {
                Matrix3D output = convLayer.forward(input);
                printError("ConvLayer dimension check: FAILED (no exception thrown)");
                failedTests++;
            } catch (const std::invalid_argument& e) {
                printSuccess("ConvLayer dimension check");
                passedTests++;
            }
        }
    } catch (const exception& e) {
        printError("Exception in testConvLayer: " + string(e.what()));
        failedTests++;
    }
}

void testReLULayer() {
    printVerbose("Test de ReLU Layer...");
    
    try {
        // Cas de test 1: Création et propagation simple
        {
            vector<float> inputValues = {
                -1, 2, -3,
                4, -5, 6
            };
            Matrix3D input(1, 2, 3, inputValues);
            
            // Création d'une couche ReLU
            ReLULayer reluLayer("TestReLU");
            
            // Propagation avant
            Matrix3D output = reluLayer.forward(input);
            
            // Valeurs attendues
            vector<float> expectedValues = {
                0, 2, 0,
                4, 0, 6
            };
            Matrix3D expected(1, 2, 3, expectedValues);
            
            totalTests++;
            if (areMatricesEqual(output, expected)) {
                printSuccess("ReLULayer simple");
                passedTests++;
            } else {
                printError("ReLULayer simple: FAILED");
                failedTests++;
            }
            
            // Affichage des informations
            if (currentMode == Mode::VERBOSE) {
                reluLayer.printInfo();
                cout << "Output:" << endl;
                output.print();
            }
        }
    } catch (const exception& e) {
        printError("Exception in testReLULayer: " + string(e.what()));
        failedTests++;
    }
}

void testPoolingLayer() {
    printVerbose("Test de Pooling Layer...");
    
    try {
        // Cas de test 1: Création et propagation simple
        {
            vector<float> inputValues = {
                1, 2, 3, 4,
                5, 6, 7, 8,
                9, 10, 11, 12,
                13, 14, 15, 16
            };
            Matrix3D input(1, 4, 4, inputValues);
            
            // Création d'une couche de pooling
            PoolingLayer poolLayer(2, 2, "TestPooling");
            
            // Propagation avant
            Matrix3D output = poolLayer.forward(input);
            
            // Valeurs attendues
            vector<float> expectedValues = {
                6, 8,
                14, 16
            };
            Matrix3D expected(1, 2, 2, expectedValues);
            
            totalTests++;
            if (areMatricesEqual(output, expected)) {
                printSuccess("PoolingLayer simple");
                passedTests++;
            } else {
                printError("PoolingLayer simple: FAILED");
                failedTests++;
            }
            
            // Affichage des informations
            if (currentMode == Mode::VERBOSE) {
                poolLayer.printInfo();
                cout << "Output:" << endl;
                output.print();
            }
        }
    } catch (const exception& e) {
        printError("Exception in testPoolingLayer: " + string(e.what()));
        failedTests++;
    }
}

void testFullyConnectedLayer() {
    printVerbose("Test de Fully Connected Layer...");
    
    try {
        // Cas de test 1: Création et propagation simple
        {
            vector<float> inputValues = {1, 2, 3, 4, 5, 6};
            Matrix3D input(1, 2, 3, inputValues); // 6 éléments au total
            
            // Création d'une couche entièrement connectée
            FullyConnectedLayer fcLayer(6, 3, "TestFC");
            
            // Propagation avant
            Matrix3D output = fcLayer.forward(input);
            
            // Vérification des dimensions
            totalTests++;
            if (output.getDepth() == 3 && output.getHeight() == 1 && output.getWidth() == 1) {
                printSuccess("FullyConnectedLayer dimensions");
                passedTests++;
            } else {
                printError("FullyConnectedLayer dimensions: FAILED");
                failedTests++;
            }
            
            // Affichage des informations
            if (currentMode == Mode::VERBOSE) {
                fcLayer.printInfo();
                cout << "Output:" << endl;
                output.print();
            }
        }
        
        // Cas de test 2: Test d'erreur de dimensions
        {
            vector<float> inputValues = {1, 2, 3, 4};
            Matrix3D input(1, 2, 2, inputValues); // 4 éléments au total
            
            // Création d'une couche avec taille d'entrée incompatible
            FullyConnectedLayer fcLayer(6, 3, "TestFCError"); // Attend 6 éléments
            
            // Doit lever une exception
            totalTests++;
            try {
                Matrix3D output = fcLayer.forward(input);
                printError("FullyConnectedLayer dimension check: FAILED (no exception thrown)");
                failedTests++;
            } catch (const std::invalid_argument& e) {
                printSuccess("FullyConnectedLayer dimension check");
                passedTests++;
            }
        }
    } catch (const exception& e) {
        printError("Exception in testFullyConnectedLayer: " + string(e.what()));
        failedTests++;
    }
}

void printSummary() {
    cout << "\n" << "=== RÉSUMÉ DES TESTS ===" << endl;
    cout << "Tests totaux: " << totalTests << endl;
    if (passedTests != 0) {
        cout << "Tests réussis: " << passedTests << endl;
    }
    if (failedTests != 0) {
        cout << "Tests échoués: " << failedTests << endl;
    }
    if (failedTests == 0) {
        cout << "> Tout les test ont réussi !\n" << endl;

    } else {
        cout << ROUGE << "Certains tests ont échoué." << RESET << endl;
        cout << "Taux de réussite: " << fixed << setprecision(2) 
             << (static_cast<float>(passedTests) / totalTests * 100) << "%\n" << endl;
    }
}

void printHelp() {
    cout << CYAN << "Usage: ./alexnet [options]" << RESET << endl;
    cout << "Options:" << endl;
    cout << "  -v, --verbose  Mode parlant (affiche tous les détails)" << endl;
    cout << "  -q, --quiet    Mode silencieux (affiche seulement le résumé)" << endl;
    cout << "  -h, --help     Affiche cette aide" << endl;
}

int main(int argc, char* argv[]) {
    // Analyse des arguments
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-v" || arg == "--verbose") {
            currentMode = Mode::VERBOSE;
        } else if (arg == "-q" || arg == "--quiet") {
            currentMode = Mode::QUIET;
        } else if (arg == "-h" || arg == "--help") {
            printHelp();
            return 0;
        }
    }
    
    // Affichage du mode avec couleurs cohérentes
    if (currentMode == Mode::VERBOSE) {
        cout << ITALIQUE << "\nMode: VERBEUX" << RESET << endl;
    } else if (currentMode == Mode::QUIET) {
        cout << ITALIQUE << "\nMode: SILENCIEUX" << RESET << endl;
    } else {
        cout << ITALIQUE << "\nMode: NORMAL" << RESET << endl;
    }
    
    // Exécution des tests
    testConvolution();
    testMaxPooling();
    testReLU();
    testCombinations();
    testConvLayer();
    testReLULayer();
    testPoolingLayer();
    testFullyConnectedLayer();
    
    // Affichage du résumé
    printSummary();
    
    return (failedTests == 0) ? 0 : 1;
}