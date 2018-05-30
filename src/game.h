#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "game_state.h"
#include <SFML/Graphics.hpp>
#include <array>

// Klasa koja predstavlja igru.
class Game {
  friend class WelcomeState;
  friend class ExitingState;
  // add more?

public:
  Game();
  void run();
  void changeState(GameState::State newState) {
    mpCurrentGameState = mpGameStates[newState];
  }
  // ostali dio sučelja
private:
  void processEvents();
  sf::RenderWindow mWindow;
  sf::Time mTimePerFrame;
  // trenutno stanje igre određeno je ovim pokazivačem.
  GameState* mpCurrentGameState;
  // Sva stanja igre. GameState::Count daje broj stanja.
  std::array<GameState*, GameState::Count> mpGameStates;
  // ostale privatne varijable
  // eventualne friend deklaracije
};

#endif // GAME-V1_H_INCLUDED
