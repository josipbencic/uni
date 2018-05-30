#ifndef SCENE_GRAPH_IS_INCLUDED
#define SCENE_GRAPH_IS_INCLUDED

#include <list>
#include <memory>

#include <SFML/Graphics.hpp>

class SceneNode : public sf::Transformable, public sf::Drawable {
public:
  using Ptr = std::unique_ptr<SceneNode>;

  SceneNode(std::string name = std::string("Node"));

  virtual ~SceneNode();

  void addComponent(Ptr pnode);
  void removeComponent(std::string const& name);

  void update(sf::Time dt);

  std::string getName() const {
    return mName;
  }

private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
  }


private:
  SceneNode* mParent;
  std::list<Ptr> mChildren;
  std::string mName;
};


// BackgrNode služi za crtanje background-a. On se ne miče
// niti ne centriramo njegov Sprite.
class BackgrNode : public SceneNode {
public:
  BackgrNode();

private:
  virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
  sf::Texture mSpriteTex;
  sf::Sprite mSprite;
};


// SpriteNode služi za crtanje aviona.
class PlaneNode : public SceneNode {
public:
  PlaneNode(std::string name);

  void setVelocity(sf::Vector2f v) {
    mVelocity = v;
  }

  void setVelocity(float vx, float vy) {
    mVelocity.x = vx;
    mVelocity.y = vy;
  }

  sf::Vector2f getVelocity() const {
    return mVelocity;
  }

private:
  virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
  sf::Sprite mSprite;
  sf::Texture mSpriteTex;
  sf::Vector2f mVelocity;
};

#endif
