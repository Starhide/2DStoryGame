#pragma once

#include "../Entity/Component.h"
#include "../Entity/Entity.h"
#include "../TextureController.h"

#include <iostream>
#include <string>
#include <cmath>

namespace sf {
class Sprite;
class Color;
class RenderedWindow;
};

class Graphics : public Component {
  private:
    sf::Clock timer;
    sf::Sprite sprite;
    std::map<std::string, std::vector<int>> sequences;
    int scale;
    int size;
    float rate;
    std::string sequence;
    unsigned int index;
    bool isRunning;

    inline void setTextureRect() {
        sprite.setTextureRect(
            sf::IntRect((sequences[sequence][index] % scale) * size,
                        (floor(sequences[sequence][index] / scale)) * size,
                        size, size));
    }

  public:
    Graphics(sol::table &componentTable);
    void setAttributes(sol::table &table);

    sf::Sprite *getSprite() { return &sprite; }

    void setSprite(const sf::Sprite &sprit) { this->sprite = sprit; }

    void drawUpdate(Entity *e, sf::RenderWindow &win);

    void fixedUpdate(Entity *e);

    void stop();

    void run(std::string seq);

    void setCurrent(std::string seq, int index);
};
