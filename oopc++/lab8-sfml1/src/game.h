#ifndef GAME_V1_H_INCLUDED
#define GAME_V1_H_INCLUDED

#include <SFML/Graphics.hpp>

// Klasa koja predstavlja igru. Osim konstruktora ima samo
// jednu javnu metodu - run().
class Game {
 public:
  Game();
  void run();

 private:
  // Procesiraj događaje
  void processEvents();
  // konstruiraj novo stanje igre
  void update(sf::Time const& dt);
  // iscrtaj novo stanje
  void render();

 private:
  sf::RenderWindow mWindow;
  sf::Texture mTextureSun;
  sf::Texture mTextureEarth;
  sf::Texture mTexturePlane;
  sf::Sprite mSun;
  sf::Sprite mEarth;
  sf::Sprite mPlane;

  sf::Time mTimePerFrame;
  float mEarthSpeed;
  float mPlaneSpeed;
  float mEarthPhi;
  float mPlanePhi;
  float mEarthOrbitR;
  float mPlaneOrbitR;
  float mEarthSelfRotSpeed;

  bool mIsMovingUp = false;
  bool mIsMovingDown = false;
  bool mIsMovingLeft = false;
  bool mIsMovingRight = false;

  void handlePlayerInput(sf::Keyboard::Key code, bool isPressed);
};

#endif  // GAME-V1_H_INCLUDED
