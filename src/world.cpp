#include "world.h"
#include <ctime>
#include <random>

World::World(sf::Vector2i windowSize)
  : mWindowSize(windowSize),
    mBlockSize(40),
    mApple(),
    mRndEngine(std::random_device{}()),
    mDistX(0, windowSize.x / mBlockSize),
    mDistY(0, windowSize.y / mBlockSize) {
  mApple.setFillColor(sf::Color(130, 180, 20));
  mApple.setOrigin({10.f, 10.f});
  mApple.setRadius(10.f);
  mApple.setPosition({160.0f, 160.0f});

  float winszx = static_cast<float>(windowSize.x);
  float winszy = static_cast<float>(windowSize.y);
  float flblock = static_cast<float>(mBlockSize);

  //  0 - up; 1 - left; 2 - down; 3 - right;

  mBounds[0].setSize({winszx, 2 * flblock});
  mBounds[2].setSize({winszx, 2 * flblock});
  mBounds[0].setOrigin({winszx / 2, flblock});
  mBounds[2].setOrigin({winszx / 2, flblock});
  mBounds[0].setPosition({winszx / 2, 0});
  mBounds[2].setPosition({winszx / 2, winszy});

  mBounds[3].setSize({flblock * 2, winszy});
  mBounds[1].setSize({flblock * 2, winszy});
  mBounds[1].setOrigin({flblock, winszy / 2});
  mBounds[3].setOrigin({flblock, winszy / 2});
  mBounds[1].setPosition({0, winszy / 2});
  mBounds[3].setPosition({winszx, winszy / 2});

  for (auto i = 0u; i < 4u; i++) {
    mBounds[i].setFillColor(sf::Color(133, 200, 133));
  }

  respawnApple();
}


void World::respawnApple() {
  sf::Vector2i pos{mDistX(mRndEngine), mDistY(mRndEngine)};
  mApple.setPosition({static_cast<float>(pos.x * mBlockSize), static_cast<float>(pos.y * mBlockSize)});
}

void World::update(Snake& snake) {
  auto insideSq = [&](sf::Vector2f a, sf::Vector2f b) -> bool {
    return (a.x < b.x + mBlockSize / 2.f) &&
           (a.x > b.x - mBlockSize / 2.f) &&
           (a.y < b.y + mBlockSize / 2.f) &&
           (a.y > b.y - mBlockSize / 2.f);
  };
  //  Has the snake eaten the apple?
  if (insideSq(mApple.getPosition(), sf::Vector2f(snake.getPosition()))) {
    snake.increaseScore();
    snake.extend();
    respawnApple();
  }
  {
    // Has snake hit the wall?
    auto sx = snake.getPosition().x;
    auto sy = snake.getPosition().y;

    if (sx < mBlockSize || sx > mWindowSize.x - mBlockSize ||
        sy < mBlockSize || sy > mWindowSize.y - mBlockSize) {
      snake.lose();
      snake.reset();
    }
  }
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  for (int i = 0; i < 4; ++i) {
    target.draw(mBounds[i]);
  }

  target.draw(mApple);
}
