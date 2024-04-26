# casse_brique

Ce projet consiste à faire un remake  du jeu classique de casse-briques, il sera développé en C++ avec l'utilisation de la bibliothèque SDL2 pour l'affichage.

## Fonctionnalités

- [] Plateforme déplaçable au clavier ou à la souris.
- [] Balle rebondissant en fonction de son angle d'impact.
- [] Briques de différents types avec différentes résistances.
- [] Bonus/malus, y compris le multi-balle.
- [] Grilles chargées depuis un fichier ASCII.


## Compilation et exécution

1. Il faut avoir installé SDL2 sur votre machine.
2. Après, il faut ce dépôt sur votre machine.
3. Ensuite, il faut générez le projet avec CMake et le compiler avec make:

```bash
mkdir build
cd build
cmake ..
make
```

4. Exécutez le jeu :

```bash
./CasseBrique
```


## Auteur

Nicolas MARRA
Eddine NASRI

## Licence

Ce projet est sous [licence MIT](LICENSE).