#include "snake.h"

Snake::Snake(int blockSize)
  : sf::Drawable(),
    mSnakeBody(1, {120, 160}),
    msize(blockSize),
    mspeed(blockSize * 2.f / 60.f),
    mlives(3),
    mscore(0),
    mlost(false),
    mcurdelta(0.0f) {
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
  mscore++;
  if (mSnakeBody.size() == 1) {
    sf::Vector2i offset;
    switch (mdir) {
      case Direction::None:
      case Direction::Down:
        offset = {0, -msize};
        break;
      case Direction::Up:
        offset = {0, msize};
        break;
      case Direction::Right:
        offset = {-msize, 0};
        break;
      case Direction::Left:
        offset = {msize, 0};
        break;
    }
    mSnakeBody.push_back({mSnakeBody[0].x + offset.x,
                          mSnakeBody[0].y + offset.y});
    return;
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
  mdir = Direction::None;
  mlives = 3;
  mscore = 0;
  mlost = false;
  mcurdelta = 0.0f;
  mSnakeBody.clear();
  mSnakeBody.push_back({120, 160});
}

void Snake::update() {
  checkCollision();
  mcurdelta += mspeed;
  if (mcurdelta > msize) {
    mcurdelta -= msize;
    move();
  }
}

void Snake::cut(int n) {
  if (mSnakeBody.size() < n) {
    return;
  }
  mSnakeBody.erase(begin(mSnakeBody) + n, end(mSnakeBody));
}

void Snake::move() {
  for (int i = static_cast<int>(mSnakeBody.size()) - 1; i > 0; i--) {
    mSnakeBody[i].x = mSnakeBody[i - 1].x;
    mSnakeBody[i].y = mSnakeBody[i - 1].y;
  }
  switch (mdir) {
    case Direction::None:
      break;
    case Direction::Right:
      mSnakeBody[0].x += msize;
      break;
    case Direction::Up:
      mSnakeBody[0].y -= msize;
      break;
    case Direction::Down:
      mSnakeBody[0].y += msize;
      break;
    case Direction::Left:
      mSnakeBody[0].x -= msize;
      break;
  }
}

void Snake::checkCollision() {
  auto x = mSnakeBody[0].x;
  auto y = mSnakeBody[0].y;

  for (auto it = begin(mSnakeBody) + 1; it != end(mSnakeBody); ++it) {
    if (it->x < x + msize / 2 && it->x > x - msize / 2 && it->y > y - msize / 2 && it->y < y + msize / 2) {
      mlives--;
      cut(it - begin(mSnakeBody));
      if (mlives <= 0) {
        lose();
        reset();
      }
      break;
    }
  }
}
