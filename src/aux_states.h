#ifndef AUX_STATES_H
#define AUX_STATES_H

#include "game_state.h"

// Sva pomoćna stanja (osim PlayingState). Njihove implementacije
// su prilično slične pa ih možemo grupirati u jedan file. 

class WelcomeState : public GameState{
public:
private:
};

class ExitingState : public GameState{
public:
private:
};

class WonState : public GameState{
public:
private:
};

class LostState : public GameState{
public:
private:
};

#endif // AUX_STATES_H
