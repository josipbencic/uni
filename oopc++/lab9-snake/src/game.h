#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "snake.h"
#include "world.h"
#include <SFML/Graphics.hpp>

class Game {
public:
  Game();

  // starts the main loop
  void run();

private:
  //  process everything caught by sfml
  void processEvents();

  // all game logic
  void update(sf::Time dt);

  void render();

private:
  sf::RenderWindow mWindow;
  World mWorld;
  Snake mSnake;
  sf::Time mTimePerFrame;

  void handlePlayerInput(sf::Keyboard::Key code);
};

#endif // GAME_H_INCLUDED
