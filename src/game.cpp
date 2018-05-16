#include "game.h"

#include <cmath>

const double PI = 3.14159265358979323;

#include <iostream>
using namespace std;

Game::Game()
    : mWindow(sf::VideoMode(800, 600), "Game"),
      mEarthSpeed(1 / 60.0f * PI),
      mPlaneSpeed(PI),
      mEarthPhi(0.0f),
      mPlanePhi(0.0f),
      mEarthOrbitR(250.0f),
      mPlaneOrbitR(49.0f),
      mEarthSelfRotSpeed(360.0f / 5.f)  // circle / sec
{
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
  auto sun_sz = mTextureSun.getSize();
  mSun.setOrigin(sun_sz.x / 2, sun_sz.y / 2);
  mSun.setScale(0.12, 0.12);
  mSun.setPosition(win_sz.x / 2, win_sz.y / 2);

  auto sunPos = mSun.getPosition();
  mEarth.setTexture(mTextureEarth);
  auto earth_sz = mTextureEarth.getSize();
  mEarth.setOrigin(earth_sz.x / 2, earth_sz.y / 2);
  mEarth.setScale(0.12, 0.12);

  auto earthPos = mEarth.getPosition();
  mPlane.setTexture(mTexturePlane);
  auto plane_sz = mTexturePlane.getSize();
  mPlane.setOrigin(plane_sz.x / 2, plane_sz.y / 2);
  mPlane.setScale(0.12, 0.12);
  mPlane.setRotation(90.f);
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
  mEarthPhi += dt.asSeconds() * mEarthSpeed;
  mPlanePhi += dt.asSeconds() * mPlaneSpeed;

  auto sunPos = mSun.getPosition();
  mEarth.setPosition(sunPos.x + mEarthOrbitR * std::cos(mEarthPhi),
                     sunPos.y + mEarthOrbitR * std::sin(mEarthPhi));

  auto earthPos = mEarth.getPosition();
  mPlane.setPosition(earthPos.x + mPlaneOrbitR * std::cos(mPlanePhi),
                     earthPos.y + mPlaneOrbitR * std::sin(mPlanePhi));

  mEarth.rotate(mEarthSelfRotSpeed * dt.asSeconds());
  mPlane.rotate(mPlaneSpeed * dt.asSeconds() * 180.f / PI);
}

// iscrtavanje
void Game::render() {
  mWindow.clear();
  mWindow.draw(mSun);
  mWindow.draw(mEarth);
  mWindow.draw(mPlane);
  mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key code, bool isPressed) {}
