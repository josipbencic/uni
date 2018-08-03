#include "game.h"

// ručna kompilacija:
// g++ -std=c++11 -g -Wall main.cpp game.cpp sceneGraph.cpp -lsfml-graphics  -lsfml-window  -lsfml-system
int main()
{
    Game game;
    game.run();

    return 0;
}
