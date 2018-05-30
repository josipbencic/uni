#include "game.h"

void Game::update(sf::Time const& dt) {
  mWorld.update(dt);
}

void Game::render() {
  mWindow.clear();
  mWindow.draw(mWorld);
  mWindow.display();
}

Game::Game()
  : mWindow(sf::VideoMode(800, 600), "Scene"),
    mWorld({800, 600}),
    mTimePerFrame(sf::seconds(1.f / 60.f)) {
}

void Game::run() {
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;

  while (mWindow.isOpen()) {
    processEvents();
    timeSinceLastUpdate += clock.restart();

    while (timeSinceLastUpdate > mTimePerFrame) {
      timeSinceLastUpdate -= mTimePerFrame;
      processEvents();
      update(mTimePerFrame);
    }

    render();
  }
}

void Game::processEvents() {
  sf::Event event;
  while (mWindow.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed:
        mWindow.close();
        break;
      case sf::Event::KeyPressed:
        handleKeyPressed(event.key.code);
        break;
    }
  }
}

void Game::handleKeyPressed(sf::Keyboard::Key key) {
  mWorld.deletePlane(key);
}
