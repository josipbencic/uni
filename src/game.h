#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SFML/Graphics.hpp>

class Game{
public:
    Game();
    void run();
private:
    // Procesiraj događaje
    void processEvents();
    // konstruiraj novo stanje igre
    void update(sf::Time const &);
    // iscrtaj novo stanje
    void render();
private:
    // implementacijski detalji
};


#endif
