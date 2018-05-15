#ifndef GAME_V1_H_INCLUDED
#define GAME_V1_H_INCLUDED

#include <SFML/Graphics.hpp>

// Klasa koja predstavlja igru. Osim konstruktora ima samo
// jednu javnu metodu - run().
class Game{
public:
    Game();
    void run();
private:
    // Procesiraj događaje
    void processEvents();
    // konstruiraj novo stanje igre
    void update();
    // iscrtaj novo stanje
    void render();
private:
    sf::RenderWindow mWindow;
    sf::Texture      mTexture;
    sf::Sprite       mSprite;
};

#endif // GAME-V1_H_INCLUDED
