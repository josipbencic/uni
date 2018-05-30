#include "aux_states.h"
#include "game.h"
#include "playing_state.h"

#include <cassert>

#include <SFML/Graphics.hpp>

WelcomeState::WelcomeState(Game* game)
  : GameState(game) {
  if (!mFont.loadFromFile("Comfortaa-Bold.ttf")) {
    throw std::runtime_error("Cannot load fonts Comfortaa-Bold.ttf");
  }

  mTextTitle.setFont(mFont);
  mTextTitle.setString("Snake Game");
  mTextTitle.setFillColor(sf::Color::White);
  mTextAuthor.setFont(mFont);
  mTextAuthor.setString("by Josip Bencic");
  mTextAuthor.setFillColor(sf::Color::White);

  mTextPressAnyKey.setFont(mFont);
  mTextPressAnyKey.setString("Press any key to continue...");
  mTextPressAnyKey.setFillColor(sf::Color::White);

  {
    auto sz = mpGame->mWindow.getSize();
    mTextTitle.setPosition(
      (sz.x - mTextTitle.getLocalBounds().width) / 2.f,
      (sz.y + mTextTitle.getLocalBounds().height) / 3.f);
    mTextAuthor.setPosition(
      (sz.x - mTextAuthor.getLocalBounds().width) / 2.0f,
      1.5f * sz.y / 3.f - mTextAuthor.getLocalBounds().height / 2.f);
    mTextPressAnyKey.setCharacterSize(20);
    mTextPressAnyKey.setPosition(
      (sz.x - mTextPressAnyKey.getLocalBounds().width) * 2.f / 3.f,
      5.f * sz.y / 6.f + mTextPressAnyKey.getLocalBounds().height / 2.f);
  }
}

void WelcomeState::update(sf::Time dt) {
}

void WelcomeState::render() {
  mpGame->mWindow.draw(mTextAuthor);
  mpGame->mWindow.draw(mTextTitle);
  mpGame->mWindow.draw(mTextPressAnyKey);
}

void WelcomeState::handlePlayerInput(sf::Keyboard::Key code) {
  mpGame->changeState(GameState::Playing);
}


ExitingState::ExitingState(Game* game)
  : GameState(game), mTime{sf::seconds(4.f)} {
  if (!mFont.loadFromFile("Comfortaa-Bold.ttf")) {
    throw std::runtime_error("Cannot load fonts Comfortaa-Bold.ttf");
  }

  mTextTitle.setFont(mFont);
  mTextTitle.setString("Game Over 3");
  mTextTitle.setFillColor(sf::Color::White);
  {
    auto sz = mpGame->mWindow.getSize();
    mTextTitle.setPosition(
      (sz.x - mTextTitle.getLocalBounds().width) / 2.f,
      (sz.y + mTextTitle.getLocalBounds().height) / 2.f);
  }
}

void ExitingState::update(sf::Time dt) {
  mTime -= dt;
  if (mTime.asSeconds() < 0.0f) {
    mpGame->mWindow.close();
  } else if (mTime.asSeconds() < 1.f) {
    mTextTitle.setString("Game Over 0");
  } else if (mTime.asSeconds() < 2.f) {
    mTextTitle.setString("Game Over 1");
  } else if (mTime.asSeconds() < 3.f) {
    mTextTitle.setString("Game Over 2");
  }
}

void ExitingState::handlePlayerInput(sf::Keyboard::Key code) {
}

void ExitingState::render() {
  mpGame->mWindow.draw(mTextTitle);
}

WonState::WonState(Game* game)
  : GameState(game) {
  if (!mFont.loadFromFile("Comfortaa-Bold.ttf")) {
    throw std::runtime_error("Cannot load fonts Comfortaa-Bold.ttf");
  }

  mTextTitle.setFont(mFont);

  auto* playstate = dynamic_cast<PlayingState*>(mpGame->mpGameStates[GameState::Playing]);
  int lastScore = 0;
  if (playstate) {
    lastScore = playstate->lastScore();
  }
  mTextTitle.setString(
    "You won! The score = " +
    std::to_string(lastScore));
  mTextTitle.setFillColor(sf::Color::White);

  mTextPressAnyKey.setFont(mFont);
  mTextPressAnyKey.setString("Hit C to continue, X to exit");
  mTextPressAnyKey.setFillColor(sf::Color::White);

  {
    auto sz = mpGame->mWindow.getSize();
    mTextTitle.setPosition(
      (sz.x - mTextTitle.getLocalBounds().width) / 2.f,
      (sz.y + mTextTitle.getLocalBounds().height) / 2.f);
    mTextPressAnyKey.setCharacterSize(20);
    mTextPressAnyKey.setPosition(
      (sz.x - mTextPressAnyKey.getLocalBounds().width) * 2.f / 3.f,
      5.f * sz.y / 6.f + mTextPressAnyKey.getLocalBounds().height / 2.f);
  }
}

void WonState::update(sf::Time dt) {
  auto* playstate = dynamic_cast<PlayingState*>(mpGame->mpGameStates[GameState::Playing]);
  int lastScore = 0;
  if (playstate) {
    lastScore = playstate->lastScore();
  }
  mTextTitle.setString(
    "You Won! The score = " +
    std::to_string(lastScore));
}

void WonState::handlePlayerInput(sf::Keyboard::Key code) {
  switch (code) {
    case sf::Keyboard::C: {
      mpGame->changeState(GameState::Playing);
      {
        auto* playstate = dynamic_cast<PlayingState*>(mpGame->mpGameStates[GameState::Playing]);
        if (playstate) {
          playstate->reset(true);
        }
      }
      mpGame->changeState(GameState::Playing);
    } break;
    case sf::Keyboard::X:
      mpGame->changeState(GameState::Exiting);
      break;
    default:
      break;
  }
}

void WonState::render() {
  mpGame->mWindow.draw(mTextTitle);
  mpGame->mWindow.draw(mTextPressAnyKey);
}

LostState::LostState(Game* game)
  : GameState(game) {
  if (!mFont.loadFromFile("Comfortaa-Bold.ttf")) {
    throw std::runtime_error("Cannot load fonts Comfortaa-Bold.ttf");
  }

  mTextTitle.setFont(mFont);

  auto* playstate = dynamic_cast<PlayingState*>(mpGame->mpGameStates[GameState::Playing]);
  int lastScore = 0;
  if (playstate) {
    lastScore = playstate->lastScore();
  } else {
    assert(false);
  }
  mTextTitle.setString(
    "You lost! The score = " +
    std::to_string(lastScore));
  mTextTitle.setFillColor(sf::Color::White);

  mTextPressAnyKey.setFont(mFont);
  mTextPressAnyKey.setString("Hit C to continue, X to exit");
  mTextPressAnyKey.setFillColor(sf::Color::White);

  {
    auto sz = mpGame->mWindow.getSize();
    mTextTitle.setPosition(
      (sz.x - mTextTitle.getLocalBounds().width) / 2.f,
      (sz.y + mTextTitle.getLocalBounds().height) / 2.f);
    mTextPressAnyKey.setCharacterSize(20);
    mTextPressAnyKey.setPosition(
      (sz.x - mTextPressAnyKey.getLocalBounds().width) * 2.f / 3.f,
      5.f * sz.y / 6.f + mTextPressAnyKey.getLocalBounds().height / 2.f);
  }
}

void LostState::update(sf::Time dt) {
  auto* playstate = dynamic_cast<PlayingState*>(mpGame->mpGameStates[GameState::Playing]);
  int lastScore = 0;
  if (playstate) {
    lastScore = playstate->lastScore();
  }
  mTextTitle.setString(
    "You lost! The score = " +
    std::to_string(lastScore));
}

void LostState::handlePlayerInput(sf::Keyboard::Key code) {
  switch (code) {
    case sf::Keyboard::C:
      mpGame->changeState(GameState::Playing);
      {
        auto* playstate = dynamic_cast<PlayingState*>(mpGame->mpGameStates[GameState::Playing]);
        if (playstate) {
          playstate->reset(false);
        }
      }
      break;
    case sf::Keyboard::X:
      mpGame->changeState(GameState::Exiting);
      break;
    default:
      break;
  }
}

void LostState::render() {
  mpGame->mWindow.draw(mTextTitle);
  mpGame->mWindow.draw(mTextPressAnyKey);
}
