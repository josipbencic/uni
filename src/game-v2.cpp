#include "game-v2.h"

Game::Game()
  : mWindow(sf::VideoMode(800, 600), "Game-v2")
  , mSpeed(100.0f) {
  if (!mTexture.loadFromFile("cb.bmp"))
    throw std::runtime_error("Cannot open file cb.bmp!");

  mTimePerFrame = sf::seconds(1.f/60.f);

  mSprite.setTexture(mTexture);
  mSprite.setTextureRect({50, 20, 70, 60});
  mSprite.move(15, 15);
  mCircle.setRadius(50.f);
  mCircle.setOutlineThickness(5.f);
  mCircle.setFillColor(sf::Color(255.f, 0.f, 255.f));
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
  mCircle.move(movement * dt.asSeconds());
}

// iscrtavanje
void Game::render() {
  mWindow.clear();
  mWindow.draw(mCircle);
  mWindow.draw(mSprite);
  mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key code, bool isPressed) {
  if (code == sf::Keyboard::Up) mIsMovingUp = isPressed;
  if (code == sf::Keyboard::Down) mIsMovingDown = isPressed;
  if (code == sf::Keyboard::Left) mIsMovingLeft = isPressed;
  if (code == sf::Keyboard::Right) mIsMovingRight = isPressed;
}
