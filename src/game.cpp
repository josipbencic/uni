#include "game.h"

// Implementacija Game klase

Game::Game() 
{
   // Ovdje alocirati sva stanja i postaviti pokazivač na trenutno stanje.   
}



// Primjer run - metode. Zavisni dijelovi koda se delegiraju GameState klasama
// kroz pokazivač mpCurrentGameState.
void Game::run(){
    sf::Clock clock;     
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while(mWindow.isOpen())
    {
       processEvents();
       timeSinceLastUpdate += clock.restart();
       while(timeSinceLastUpdate > mTimePerFrame)
       {
          timeSinceLastUpdate -= mTimePerFrame;
          processEvents();
          mpCurrentGameState->update(mTimePerFrame);
       }
       // rendering
       mWindow.clear();
       mpCurrentGameState->render();
       mWindow.display();
    }
}

// obrada događaja
void Game::processEvents(){
   // implementacija  
}
