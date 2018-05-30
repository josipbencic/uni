#ifndef AUX_STATES_H
#define AUX_STATES_H

#include "game_state.h"

// Sva pomoćna stanja (osim PlayingState). Njihove implementacije
// su prilično slične pa ih možemo grupirati u jedan file.

class WelcomeState : public GameState {
public:
  WelcomeState(Game* game);

  virtual ~WelcomeState() {
  }

  virtual void update(sf::Time dt);

  virtual void handlePlayerInput(sf::Keyboard::Key code);

  virtual void render();

private:
  sf::Font mFont;
  sf::Text mTextTitle;
  sf::Text mTextAuthor;
  sf::Text mTextPressAnyKey;
};

class ExitingState : public GameState {
public:
  ExitingState(Game* game);

  virtual ~ExitingState() {
  }

  virtual void update(sf::Time dt);

  virtual void handlePlayerInput(sf::Keyboard::Key code);

  virtual void render();

private:
  sf::Font mFont;
  sf::Text mTextTitle;
  sf::Time mTime;
};

class WonState : public GameState {
public:
private:
};

class LostState : public GameState {
public:
private:
};

#endif // AUX_STATES_H
