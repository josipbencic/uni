#include "game-v1.h"

Game::Game() : mWindow(sf::VideoMode(800, 600), "Game-v1"), mSpeed(5.0f) {
  if (!mTexture.loadFromFile("cb.bmp"))
    throw std::runtime_error("Cannot open file cb.bmp!");

  mSprite.setTexture(mTexture);
}

// game-loop je sada u metodi run()
void Game::run() {
  sf::Clock clock;  // defaultni konstruktor starta sat
  // vrijeme od zadnjeg poziva funkciji update()
  sf::Time timeSinceLastUpdate = sf::Time::Zero;

  while (mWindow.isOpen()) {
    processEvents();
    // stavi clock na nulu i vrati protekli interval
    timeSinceLastUpdate += clock.restart();
    // updatiraj eventualno više puta ako je iscrtavanje bilo sporo
    while (timeSinceLastUpdate > mTimePerFrame) {
      timeSinceLastUpdate -= mTimePerFrame;
      processEvents();
      update(mTimePerFrame);
    }
    render();
  }
}

// obrada događaja
void Game::processEvents() {
  sf::Event event;
  while (mWindow.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed: {
        mWindow.close();
        break;
      }
      case sf::Event::KeyPressed: {
        handlePlayerInput(event.key.code, true);
        break;
      }
      case sf::Event::KeyReleased: {
        handlePlayerInput(event.key.code, false);
        break;
      }
    }
  }
}

// Za sada se stanje ne mijenja. Uvijek iscrtavamo isto.
void Game::update(sf::Time const& dt) {
  sf::Vector2f movement(0.f, 0.f);  // brzina
  if (mIsMovingUp) movement.y -= mSpeed;
  if (mIsMovingDown) movement.y += mSpeed;
  if (mIsMovingLeft) movement.x -= mSpeed;
  if (mIsMovingRight) movement.x += mSpeed;

  mSprite.move(movement * dt.asSeconds());
}

// iscrtavanje
void Game::render() {
  mWindow.clear();
  mWindow.draw(mSprite);
  mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key code, bool isPressed) {
  if (code == sf::Keyboard::Up) mIsMovingUp = isPressed;
  if (code == sf::Keyboard::Down) mIsMovingDown = isPressed;
  if (code == sf::Keyboard::Left) mIsMovingLeft = isPressed;
  if (code == sf::Keyboard::Right) mIsMovingRight = isPressed;
}
