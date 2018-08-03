#ifndef WORLD_H_IS_INCLUDED
#define WORLD_H_IS_INCLUDED

#include "snake.h"
#include <SFML/Graphics.hpp>

#include <random>

// "Svijet" se sastoji od okvira i jabuke. Zmija ne smije
// izaći iz okvira (odmah gubi) i ako pojede jabuku povećava
// duljinu.
class World : public sf::Drawable {
public:
  World(sf::Vector2i windowSize);

  //  Select a new random position for the apple
  void respawnApple();

  int getBlockSize() const {
    return mBlockSize;
  }
  // Provjeri je li zmija pojela jabuku ...
  void update(Snake& snake);

private:
  sf::Vector2i mWindowSize;      // Veličina ekrana
  int mBlockSize;                // Veličina bloka od kog je građena zmija
  sf::CircleShape mApple;        // jabuka
  sf::RectangleShape mBounds[4]; // rubovi domene

  std::default_random_engine mRndEngine;
  std::uniform_int_distribution<int> mDistX, mDistY;

  // iscrtavanje
  virtual void
    draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
