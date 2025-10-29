# Si besoin d'explications

Ce fichier contient des explications détaillées trop longues pour tenir dans une simple documentation.

---

## 1.1 Formule pour l’index linéaire

> **Formule :** `index = z * (height * width) + y * width + x`

### Illustration

```
Couche 0 (z=0)
    [ 0,  1,  2,  3 ]  ← y=0
    [ 4,  5,  6,  7 ]  ← y=1
    [ 8,  9, 10, 11 ]  ← y=2

Couche 1 (z=1)
    [12, 13, 14, 15]  ← y=0
    [16, 17, 18, 19]  ← y=1
    [20, 21, 22, 23]  ← y=2
         ↑ élément d'indice x = 1
```

### Explications des composants

* **`z * height * width` →** saute toutes les couches complètes avant la couche `z`

  > Exemple : `z=1` → 1 * 3 * 4 = 12 → les 12 premiers éléments correspondent à la couche 0.

* **`y * width` →** saute toutes les lignes complètes avant la ligne `y` dans la couche `z`

  > Exemple : dans `z=1, y=2` → 2 * 4 = 8 → on saute les 2 premières lignes de la couche 1 (12 + 8 = 20).

* **`x` →** décalage à l’intérieur de la ligne pour atteindre la colonne souhaitée

  > Exemple : `x=1` → index final = 20 + 1 = 21 → valeur = 21.

---

## 1.2 La division tronquée et l’astuce du ceil entier

En C++, la **division entière** tronque toujours le résultat vers zéro :

```cpp
5 / 2 = 2   // pas 2.5
```

Or, dans certains calculs (comme le max-pooling ou la convolution), on a besoin de **l’arrondi supérieur** (`ceil` ou ceilling) pour connaître le nombre de positions ou la taille de sortie.

### Astuce pour obtenir le ceil entier

Pour obtenir `ceil(x / y)` avec des entiers en C++, on peut utiliser la formule :

ceil(x / y) = (x + y - 1) / y


#### Exemple 1 : x positif

* x = 5, y = 2

```
5 / 2 = 2                   // division entière classique
ceil(5/2) = 3               // résultat attendu
(5 + 2 - 1)/2 = 6 / 2 = 3
```


### Concrètement :

* `(x + y - 1)/y` → permet de faire un **ceil entier** en C++ sans utiliser de float (utile dans notre cas).
