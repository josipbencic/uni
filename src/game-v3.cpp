#include "game-v3.h"

Game::Game() : mWindow(sf::VideoMode(800, 600), "Game-v3"), mSunSpeed(5.0f) {
  if (!mTextureSun.loadFromFile("SunRed.png")) {
    throw std::runtime_error("Cannot open file SunRed.png!");
  }
  if (!mTextureEarth.loadFromFile("planet1.png")) {
    throw std::runtime_error("Cannot open file planet1.png!");
  }
  if (!mTexturePlane.loadFromFile("Plane.png")) {
    throw std::runtime_error("Cannot open file Plane.png!");
  }
  mTimePerFrame = sf::seconds(1.f / 60.f);

  auto win_sz = mWindow.getSize();

  mSun.setTexture(mTextureSun);
  mSun.setScale(0.12, 0.12);
  auto sun_sz = mTextureSun.getSize();
  mSun.setPosition(win_sz.x / 2 - sun_sz.x * mSun.getScale().x / 2,
                   win_sz.y / 2 - sun_sz.y * mSun.getScale().y / 2);

  mEarth.setTexture(mTextureEarth);
  auto earth_sz = mTextureEarth.getSize();
  mEarth.setScale(0.12, 0.12);
  mEarth.setPosition(5 * win_sz.x / 6 - earth_sz.x * mEarth.getScale().x / 2,
                     win_sz.y / 2 - earth_sz.y * mEarth.getScale().y / 2);

  mPlane.setTexture(mTexturePlane);
  auto plane_sz = mTexturePlane.getSize();
  mPlane.setScale(0.12, 0.12);
  mPlane.setPosition(9 * win_sz.x / 12 - plane_sz.x * mPlane.getScale().x / 2,
                     win_sz.y / 2 - plane_sz.y * mPlane.getScale().y / 2);
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
void Game::update(sf::Time const& dt) {}

// iscrtavanje
void Game::render() {
  mWindow.clear();
  mWindow.draw(mSun);
  mWindow.draw(mEarth);
  mWindow.draw(mPlane);
  mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key code, bool isPressed) {}
