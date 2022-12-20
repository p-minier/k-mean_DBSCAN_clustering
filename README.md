# K-Means & DBSCAN clustering
Les algorithmes de clustering K-Means et DBSCAN sont implémentés en [MATLAB](https://github.com/Adrial-Knight/k-mean_DBSCAN_clustering/tree/main/src/matlab), en [Python](https://github.com/Adrial-Knight/k-mean_DBSCAN_clustering/tree/main/src/python) et en [C](https://github.com/Adrial-Knight/k-mean_DBSCAN_clustering/tree/main/src/c).

## MATLAB
Le [script MATLAB](https://github.com/Adrial-Knight/k-mean_DBSCAN_clustering/blob/main/src/matlab/main.m) peut tester les algorithmes à partir de fichiers csv de la forme:
|            |            |            |
|------------|------------|------------|
|    1.281   |  1.6431    |     1      |
|    1.121   |  1.431     |     1      |
|    1.671   |  0.761     |     2      |

où les deux premières colones représentent les coordonnées des points, et la troisème colone indique la classe à obtenir après traitement.

## Python
Le [script python](https://github.com/Adrial-Knight/k-mean_DBSCAN_clustering/blob/main/src/python/main.py) nécessite deux modules:
1. numpy pour le calcul vectoriel/matriciel: `pip install numpy`
2. matplotlib pour l'affichage graphique: `pip install matplotlib`

Ce script teste les algorithmes sur une distribution comportant deux anneaux: l'un à l'intérieur de l'autre.

## C
La version C nécessite d'être compilée à l'aide du [Makefile](https://github.com/Adrial-Knight/k-mean_DBSCAN_clustering/blob/main/src/c/Makefile) fourni.
```
cd src/c
make
```
Le dossier bin est alors crée et contient deux programmes `dbscan` et `kmean`.

### Lancement des programmes
#### K-Means
Pour lancer K-Means sur le dataset donuts avec K=2:
```
./bin/kmean data/donuts.csv 2
```

#### DBSCAN
Pour lancer DBSCAN sur le dataset donuts, avec $\epsilon=0.5$ et un nombre minimal de point par cluster à 10:
```
./bin/dsbcan data/donuts.csv .5  10
```

### Sorties
Les résultats sont écrits dans le dossier [output/kmean](https://github.com/Adrial-Knight/k-mean_DBSCAN_clustering/tree/main/src/c/output/kmean) ou [output/dbscan](https://github.com/Adrial-Knight/k-mean_DBSCAN_clustering/tree/main/src/c/output/dbscan) avec:
- un fichier `.txt` donnant certaines métriques sur le clustering effectué
- un fichier `.svg` pour visualiser les clusters.


## Résultats
Les algorithmes et résultats sont présentés dans le [rapport](https://github.com/Adrial-Knight/k-mean_DBSCAN_clustering/blob/main/doc/rapport.md), ainsi que dans les slides de [présentations](https://github.com/Adrial-Knight/k-mean_DBSCAN_clustering/blob/main/doc/pr%C3%A9sentation.pdf).
Ce projet a été mené avec Merwan Muller et Baptiste Roulliaux <3
