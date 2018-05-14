#include "world.h"
#include <ctime>
#include <random>

// Implementacija klase World dolazi ovdje.


void World::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for(int i=0; i<4; ++i)
      target.draw(mBounds[i]);
    target.draw(mApple);
}
