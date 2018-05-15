#include "game-v1.h"

Game::Game() : mWindow(sf::VideoMode(800,600), "Game-v1"){
   if (!mTexture.loadFromFile("cb.bmp"))
        throw std::runtime_error("Cannot open file cb.bmp!");

   mSprite.setTexture(mTexture);
}

// game-loop je sada u metodi run()
void Game::run(){
   while(mWindow.isOpen())
   {
     processEvents();
     update();
     render();
   }
}

// obrada događaja
void Game::processEvents(){
      sf::Event event;
      while(mWindow.pollEvent(event)){
        if(event.type == sf::Event::Closed)
            mWindow.close();
      }
}

// Za sada se stanje ne mijenja. Uvijek iscrtavamo isto.
void Game::update(){
}

// iscrtavanje
void Game::render(){
    mWindow.clear();
    mWindow.draw(mSprite);
    mWindow.display();
}
