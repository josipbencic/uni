#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "world.h"


class Game {
public:
  Game();

  void run();

private:
  void processEvents();

  void update(sf::Time const&);

  void render();

  void handleKeyPressed(sf::Keyboard::Key key);

private:
  sf::RenderWindow mWindow;
  World mWorld;
  sf::Time mTimePerFrame;
};


#endif
