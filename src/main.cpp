#include "Game.h"
#include <iostream>

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <nom_fichier> | type de brique"
                  << std::endl;
        return 1;
    }

    Game game;
    game.run(argv[1]);

    return 0;
}