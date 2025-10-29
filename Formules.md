## Formules Utiles

---

## 1. Initialisation des poids

### 1.1 Xavier / Glorot

* Pour une couche Fully Connected ou Convolution :
  $$\text{standard deviation} = \sqrt{\frac{2}{\text{fan}_{\text{in}}}}$$
* $\text{fan}_{\text{in}}$ = nombre de connexions entrantes vers le neurone ou le filtre

**Explication :**
Cette formule permet de générer des poids aléatoires dont la variance est contrôlée, ce qui évite que les activations deviennent trop grandes ou trop petites lors du forward initial.

**Exemple :**

* Fully Connected : $\text{fan}_{\text{in}} = \text{inputSize}$
* ConvLayer : $\text{fan}_{\text{in}} = \text{depth} \times \text{height} \times \text{width}$ du filtre

---

### 1.2 He Initialization (pour ReLU)

$$\text{standard deviation} = \sqrt{\frac{2}{\text{fan}_{\text{in}}}}$$

* Même principe, mais optimisé pour les fonctions d’activation ReLU qui peuvent annuler certaines valeurs.
* Permet un apprentissage plus stable et rapide pour les réseaux avec ReLU.

---

## 2. Convolution

### 2.1 Sortie d’un filtre

$$\text{Output}[i,j] = \sum_{z} \sum_{y} \sum_{x} \left( \mathbf{X}[z, i+y, j+x] \cdot \mathbf{K}[z, y, x] \right) + b$$

* $i,j$ : indices spatiaux de la sortie
* $z$ : profondeur de l'entrée
* $y,x$ : indices du filtre
* $b$ : biais associé au filtre

**Explication :**
Chaque élément de sortie est calculé en multipliant les valeurs de la fenêtre d’entrée par les poids du filtre correspondant (`⋅` = produit scalaire), puis en ajoutant le biais. C’est le cœur de la convolution.

---

### 2.2 Dimensions de la sortie

$$\text{height}*{\text{out}} = \frac{\text{height}*{\text{in}} - \text{height}*{\text{f}} + 2p}{\text{stride}} + 1$$
$$\text{width}*{\text{out}} = \frac{\text{width}*{\text{in}} - \text{width}*{\text{f}} + 2p}{\text{stride}} + 1$$

* $p$ = padding, $\text{stride}$ = décalage

**Explication :**
Ces formules permettent de calculer la taille de la sortie après convolution, en tenant compte du padding et du stride.

---

## 3. Pooling

### Max Pooling

$$\text{Output}[i,j] = \max \big( \text{entrées dans la fenêtre} \big)$$

### Average Pooling

$$\text{Output}[i,j] = \text{mean} \big( \text{entrées dans la fenêtre} \big)$$

**Explication :**
Le pooling réduit la dimension spatiale tout en conservant les informations importantes : max pooling prend le maximum, average pooling la moyenne.

---

## 4. Activation

### ReLU

$$\text{ReLU}(x) = \max(0, x)$$

*Bloque les valeurs négatives à zéro, introduisant la non-linéarité nécessaire au réseau.*

### Sigmoid

$$\text{Sigmoid}(x) = \frac{1}{1 + e^{-x}}$$

*Construit une sortie entre 0 et 1, utile pour les probabilités. Si x très petit : 0, très grand : 1, si x=0 : 0.5*

### Tanh

$$\text{Tanh}(x) = \frac{e^{x} - e^{-x}}{e^{x} + e^{-x}}$$

*Semblable à Sigmoid. La sortie es entre -1 et 1, centrée autour de zéro (utile dans certaines architectures)*

### Softmax

$$\text{Softmax}(x_i) = \frac{e^{x_i}}{\sum_{j} e^{x_j}}$$

*Convertit un vecteur de scores en probabilités pour la classification multi-classes.*

---

## 5. Fully Connected Layer (Dense)

$$\mathbf{y} = \mathbf{W} \cdot \mathbf{x} + \mathbf{b}$$

* $\mathbf{W}$ : matrice $[\text{outputSize} \times \text{inputSize}]$
* $\mathbf{x}$ : vecteur d'entrée
* $\mathbf{b}$ : vecteur de biais $[\text{outputSize}]$

**Explication :**
Chaque neurone de sortie est une combinaison linéaire des entrées, pondérée par les poids (`⋅`) avec ajout du biais.

---

## 6. Fonction de perte

### 6.1 Cross Entropy Loss

$$\text{Loss} = - \sum_{i} \left( y_{\text{true}}[i] \cdot \log(y_{\text{pred}}[i]) \right)$$

*Mesure l’écart entre les probabilités prédites et la vérité terrain pour la classification.*

### 6.2 Mean Squared Error (régression)

$$\text{Loss} = \frac{1}{N} \sum_{i} \left( y_{\text{pred}}[i] - y_{\text{true}}[i] \right)^2$$

*Mesure l’erreur quadratique moyenne pour les problèmes de régression.*

---

## 7. Rétropropagation (**Backpropagation**)

### Fully Connected

$$\frac{\partial \text{Loss}}{\partial \mathbf{W}} = \frac{\partial \text{Loss}}{\partial \mathbf{y}} \cdot \mathbf{x}^T$$
$$\frac{\partial \text{Loss}}{\partial \mathbf{b}} = \frac{\partial \text{Loss}}{\partial \mathbf{y}}$$
$$\frac{\partial \text{Loss}}{\partial \mathbf{x}} = \mathbf{W}^T \cdot \frac{\partial \text{Loss}}{\partial \mathbf{y}}$$

**Explication :**
Permet de calculer le gradient des poids, biais et entrées pour mettre à jour le réseau lors de l’apprentissage.

### Convolution

$$\frac{\partial \text{Loss}}{\partial \mathbf{K}} = \text{convolution}(\mathbf{X}, \frac{\partial \text{Loss}}{\partial \text{Output}})$$
$$\frac{\partial \text{Loss}}{\partial b} = \sum_{\text{indices spatiaux}} \left( \frac{\partial \text{Loss}}{\partial \text{Output}} \right)$$

**Explication :**
Les gradients pour chaque filtre sont obtenus en convoluant l’entrée avec le gradient de la sortie, et le gradient du biais est la somme des gradients spatiaux.

---

## 8. Optimisation

### Gradient Descent

$$\mathbf{W} = \mathbf{W} - \text{lr} \cdot \frac{\partial \text{Loss}}{\partial \mathbf{W}}$$

### Momentum

$$\mathbf{v} = \beta \mathbf{v} + (1-\beta) \frac{\partial \text{Loss}}{\partial \mathbf{W}}$$
$$\mathbf{W} = \mathbf{W} - \text{lr} \cdot \mathbf{v}$$

### Adam

$$\mathbf{m} = \beta_1 \mathbf{m} + (1-\beta_1) \frac{\partial \text{Loss}}{\partial \mathbf{W}}$$
$$\mathbf{v} = \beta_2 \mathbf{v} + (1-\beta_2) \left(\frac{\partial \text{Loss}}{\partial \mathbf{W}}\right)^2$$
$$\mathbf{W} = \mathbf{W} - \text{lr} \cdot \frac{\mathbf{m}}{\sqrt{\mathbf{v}} + \epsilon}$$

**Explication :**
Ces méthodes permettent de mettre à jour les poids du réseau avec différentes stratégies pour accélérer et stabiliser l’apprentissage.

---

## 9. Notations générales

* $\text{fan}_{\text{in}}$ = nombre de connexions entrantes
* $\text{fan}_{\text{out}}$ = nombre de connexions sortantes
* $\text{stride}$ = décalage du filtre lors de la convolution
* $p$ (padding) = ajout de zéros autour de l'entrée

**Explication :**
Ces paramètres définissent la forme et la connectivité des couches dans un CNN, et sont essentiels pour calculer les dimensions de sortie et l’initialisation des poids.