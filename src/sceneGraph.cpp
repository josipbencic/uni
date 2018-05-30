#include "sceneGraph.h"

SceneNode::SceneNode(std::string name)
  : mName(name), mParent(nullptr) {
}

SceneNode::~SceneNode() {
}

void SceneNode::addComponent(Ptr pnode) {
  pnode->mParent = this;
  mChildren.push_back(std::move(pnode));
}

void SceneNode::removeComponent(std::string const& name) {
  auto it = std::find_if(begin(mChildren), end(mChildren), [&name](Ptr const& x) -> bool {
    return x->getName() == name;
  });

  if (it == std::end(mChildren)) {
    for (auto& jt : mChildren) {
      jt->removeComponent(name);
    }
    return;
  }

  for (auto& x : (*it)->mChildren) {
    x->mParent = this;
  }
  mChildren.splice(std::end(mChildren), (*it)->mChildren);
  auto jt = it;
  ++it;

  mChildren.erase(jt, it);
}

void SceneNode::update(sf::Time dt) {
  for (auto& child : mChildren) {
    child->update(dt);
  }
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  drawCurrent(target, states);

  for (auto& child : mChildren) {
    child->draw(target, states);
  }
}

BackgrNode::BackgrNode()
  : SceneNode("Background") {

  if (!mSpriteTex.loadFromFile("Textures/Desert.png")) {
    throw std::runtime_error("Cannot open file Textures/Desert.png!");
  }
  mSprite.setTexture(mSpriteTex);
  mSprite.setScale({1.25f, 1.25f});
}

void BackgrNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(mSprite, states);
}

PlaneNode::PlaneNode(std::string name)
  : SceneNode(name) {
  if (name != "Eagle") {
    if (!mSpriteTex.loadFromFile("Textures/Eagle.png")) {
      throw std::runtime_error("Cannot open file Textures/Eagle.png!");
    }
  } else {
    if (!mSpriteTex.loadFromFile("Textures/Raptor.png")) {
      throw std::runtime_error("Cannot open file Textures/Raptor.png!");
    }
  }
  auto sz = mSpriteTex.getSize();
  mSprite.setTexture(mSpriteTex);
  mSprite.setOrigin({sz.x / 2.f, sz.y / 2.f});
}

void PlaneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(mSprite, states);
}
