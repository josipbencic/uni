#include "aux_states.h"
#include "game.h"

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
      (sz.y + mTextTitle.getLocalBounds().height) / 2.f);
    mTextAuthor.setPosition(
      (sz.x - mTextAuthor.getLocalBounds().width) / 2.0f,
      4 * sz.y / 6.f - mTextAuthor.getLocalBounds().height / 2.f);
    mTextPressAnyKey.setPosition(
      (sz.x - mTextPressAnyKey.getLocalBounds().width) / 2.f,
      sz.y / 6.f + mTextPressAnyKey.getLocalBounds().height / 2.f);
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
  mpGame->changeState(GameState::Exiting);
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
