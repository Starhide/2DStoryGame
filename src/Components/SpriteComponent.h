#pragma once

#include "../Entity/Component.h"

#include <iostream>
#include <string>

namespace sf {
class Sprite;
class Color;
class RenderedWindow;
};

class Entity;

class SpriteComponent : public Component {
  private:
    sf::Sprite sprite;

  public:
    SpriteComponent(luabridge::LuaRef &componentTable);

    sf::Sprite *getSprite() { return &sprite; }

    void setSprite(const sf::Sprite &sprit) { this->sprite = sprit; }

    void draw(Entity *e, sf::RenderWindow &win);
};
