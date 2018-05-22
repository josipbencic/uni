#include "snake.h"

Snake::Snake(int blockSize)
  : sf::Drawable(),
    mSnakeBody(1, {120, 160}),
    msize(blockSize),
    mspeed(20),
    mlives(3),
    mscore(0),
    mlost(false) {
  float flbl = static_cast<float>(blockSize);
  mbodyRect.setSize({flbl, flbl});
  mbodyRect.setOrigin({flbl / 2, flbl / 2});
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  mbodyRect.setFillColor({0, 0, 179});

  auto createVec2f = [](const SnakeSegment& s) -> sf::Vector2f {
    return {
      static_cast<float>(s.x), static_cast<float>(s.y)};
  };

  mbodyRect.setPosition(createVec2f(mSnakeBody[0]));
  target.draw(mbodyRect);
  mbodyRect.setFillColor({0, 10, 120});
  for (auto i = 1u; i < mSnakeBody.size(); ++i) {
    mbodyRect.setPosition(createVec2f(mSnakeBody[i]));
    target.draw(mbodyRect);
  }
}

sf::Vector2i Snake::getPosition() {
  return {mSnakeBody[0].x, mSnakeBody[0].y};
}

void Snake::extend() {
  if (mSnakeBody.size() == 1) {
    sf::Vector2i offset;
    switch (mdir) {
      case Direction::Down:
        offset = {0, -msize};
      case Direction::Up:
        offset = {0, msize};
      case Direction::Right:
        offset = {-msize, 0};
      case Direction::Left:
        offset = {msize, 0};
    }
    mSnakeBody.push_back({mSnakeBody[0].x + offset.x,
                          mSnakeBody[0].y + offset.y});
  }
  auto x = mSnakeBody.back().x;
  auto y = mSnakeBody.back().y;
  auto difx = x - (mSnakeBody.end() - 2)->x;
  auto dify = y - (mSnakeBody.end() - 2)->y;
  if (difx != 0) {
    mSnakeBody.push_back({mSnakeBody.back().x + difx, mSnakeBody.back().y});
  } else {
    mSnakeBody.push_back({mSnakeBody.back().x, mSnakeBody.back().y + dify});
  }
}

void Snake::reset() {
  mSnakeBody.clear();
  mSnakeBody.push_back({120, 160});
}

void Snake::update() {
}

void Snake::cut(int n) {
  if (mSnakeBody.size() < n) {
    return;
  }
  mSnakeBody.erase(begin(mSnakeBody) + n, end(mSnakeBody));
}


void Snake::move() {
}

void Snake::checkCollision() {
}
