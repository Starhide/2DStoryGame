#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <string>
#include <tuple>

class LuaSprite {
  private:
    sf::Sprite sprite;

  public:
    LuaSprite(std::string filename);
    void draw(sf::RenderWindow &win);
    void loadFromFile(std::string filename);

    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }

    std::tuple<float, float> getPosition() {
        return std::make_tuple(sprite.getPosition().x, sprite.getPosition().y);
    }

    void setScale(float x, float y) {
        sprite.setScale(x, y);
    }

    std::tuple<float, float> getScale() {
        return std::make_tuple(sprite.getScale().x, sprite.getScale().y);
    }

    void setOrigin(float x, float y) {
        sprite.setOrigin(x, y);
    }

    std::tuple<float, float> getOrigin() {
        return std::make_tuple(sprite.getOrigin().x, sprite.getOrigin().y);
    }

    float getRotation() {
        return sprite.getRotation();
    }

    void setRotation(float r) {
        sprite.setRotation(r);
    }

    std::tuple<int, int, int, int> getTextureRect() {
        return std::make_tuple(
            sprite.getTextureRect().left, sprite.getTextureRect().top,
            sprite.getTextureRect().width, sprite.getTextureRect().height);
    }

    void setTextureRect(int left, int top, int width, int height) {
        sprite.setTextureRect(sf::IntRect(left, top, width, height));
    }

    int getTextureWidth() {
        return sprite.getTexture()->getSize().x;
    }

    int getTextureHeight() {
        return sprite.getTexture()->getSize().y;
    }

    void setColor(int red, int green, int blue, int alpha) {
        sprite.setColor(sf::Color(red, green, blue, alpha));
    }

    std::tuple<int, int, int, int> getColor() {
        return std::make_tuple(sprite.getColor().r, sprite.getColor().g,
                               sprite.getColor().b, sprite.getColor().a);
    }

    sf::Sprite getSprite() {
        return sprite;
    }
};