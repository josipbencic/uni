#ifndef PLAYING_STATE_H
#define PLAYING_STATE_H

#include "game_state.h"
#include "snake.h"
#include "world.h"


class Game;

// Naša glavna state-klasa. Veći dio koda iz
// prethodne Game klase završit će ovdje s manjim izmjenama.
class PlayingState : public GameState {
public:
  PlayingState(Game* game);

  virtual ~PlayingState() {
  }

  virtual void update(sf::Time dt);

  virtual void handlePlayerInput(sf::Keyboard::Key code);

  virtual void render();

  void reset(bool won) {
    if (won) {
      mSnake.setSpeed(mSnake.getSpeed() * 1.25f);
    }
    mSnake.reset();
  }

  int lastScore() const {
    return mLastScore;
  }

private:
  World mWorld;
  Snake mSnake;
  int mLastScore;
};


#endif // PLAYING_STATE_H
