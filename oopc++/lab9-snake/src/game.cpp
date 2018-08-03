#include "game.h"

Game::Game()
  : mWindow(sf::VideoMode(800, 600), "Snake"),
    mWorld({800, 600}),
    mSnake(mWorld.getBlockSize()),
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

void Game::update(sf::Time dt) {
  mSnake.update();
  mWorld.update(mSnake);
}

void Game::handlePlayerInput(sf::Keyboard::Key code) {
  switch (code) {
    case sf::Keyboard::Down: {
      if (mSnake.getDirection() != Direction::Up) {
        mSnake.setDirection(Direction::Down);
      }
      break;
    }
    case sf::Keyboard::Up: {
      if (mSnake.getDirection() != Direction::Down) {
        mSnake.setDirection(Direction::Up);
      }
      break;
    }
    case sf::Keyboard::Left: {
      if (mSnake.getDirection() != Direction::Right) {
        mSnake.setDirection(Direction::Left);
      }
      break;
    }
    case sf::Keyboard::Right: {
      if (mSnake.getDirection() != Direction::Left) {
        mSnake.setDirection(Direction::Right);
      }
      break;
    }
  }
}

void Game::render() {
  mWindow.clear();
  mWindow.draw(mWorld);
  mWindow.draw(mSnake);
  mWindow.display();
}

void Game::processEvents() {
  sf::Event event;
  while (mWindow.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed: {
        mWindow.close();
        break;
      }
      case sf::Event::KeyPressed: {
        handlePlayerInput(event.key.code);
        break;
      }
    }
  }
}
