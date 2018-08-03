#include "playing_state.h"

#include "game.h"

PlayingState::PlayingState(Game* game)
  : GameState(game),
    mWorld({800, 600}),
    mSnake(mWorld.getBlockSize()),
    mLastScore(0) {
}

void PlayingState::update(sf::Time dt) {
  mSnake.update();
  mWorld.update(mSnake);
  mLastScore = mSnake.getScore();
  if (mSnake.hasLost() && mSnake.getScore() >= 100) {
    mpGame->changeState(GameState::Won);
  } else if (mSnake.hasLost()) {
    mpGame->changeState(GameState::Lost);
  }
}

void PlayingState::render() {
  mpGame->mWindow.draw(mWorld);
  mpGame->mWindow.draw(mSnake);
}

void PlayingState::handlePlayerInput(sf::Keyboard::Key code) {
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
    default:
      break;
  }
}
