#ifndef WORLD_H
#define WORLD_H

#include "sceneGraph.h"
#include <SFML/Graphics.hpp>


class World : public sf::Drawable {
public:
  World(sf::Vector2i size);

  void update(sf::Time const& dt);

  void deletePlane(sf::Keyboard::Key key);

private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  void handlePlayerMovement();

private:
  mutable PlaneNode mEagle;
  BackgrNode mBackground;
  sf::Vector2i mLastMousePos;
};

#endif
