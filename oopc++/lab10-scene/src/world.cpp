#include "world.h"

#include <SFML/Graphics.hpp>

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(mBackground, states);
  target.draw(mEagle, states);
}

void World::update(sf::Time const& dt) {
  mEagle.update(dt);
  mEagle.move(mEagle.getVelocity());
  handlePlayerMovement();
}

void World::deletePlane(sf::Keyboard::Key key) {
  switch (key) {
    case sf::Keyboard::Key::H:
      mEagle.removeComponent("Raptor1");
      break;
    case sf::Keyboard::Key::J:
      mEagle.removeComponent("Raptor2");
      break;
    case sf::Keyboard::Key::K:
      mEagle.removeComponent("Raptor3");
      break;
    case sf::Keyboard::Key::L:
      mEagle.removeComponent("Raptor4");
      break;
    default:
      break;
  }
}

World::World(sf::Vector2i sz)
  : mEagle{"Eagle"}, mBackground{}, mLastMousePos(sf::Mouse::getPosition()) {

  std::unique_ptr<SceneNode> h{new PlaneNode{"Raptor1"}};
  std::unique_ptr<SceneNode> j{new PlaneNode{"Raptor2"}};
  std::unique_ptr<SceneNode> k{new PlaneNode{"Raptor3"}};
  std::unique_ptr<SceneNode> l{new PlaneNode{"Raptor4"}};

  sf::Vector2f L = {-80, 60.f};
  sf::Vector2f R = {80, 60.f};
  h->setPosition(L);
  l->setPosition(R);
  j->addComponent(std::move(h));
  k->addComponent(std::move(l));

  j->setPosition(L);
  k->setPosition(R);
  mEagle.addComponent(std::move(j));
  mEagle.addComponent(std::move(k));
  mEagle.setPosition({sz.x / 2.f, sz.y / 2.f});
}

void World::handlePlayerMovement() {
  auto curPos = sf::Mouse::getPosition();
  if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    mEagle.setVelocity(0.f, 0.f);
    mLastMousePos = curPos;
    return;
  }

  auto moveDir = curPos - mLastMousePos;
  sf::Vector2f velocity{static_cast<float>(moveDir.x), static_cast<float>(moveDir.y)};
  mEagle.setVelocity(2.f * velocity);
  mLastMousePos = curPos;
}
