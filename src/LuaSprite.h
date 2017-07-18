#pragma once

#include <string>
#include <tuple>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class LuaSprite {
  private:
    sf::Sprite sprite;

  public:
    LuaSprite(std::string filename);

    float getPosX() { return sprite.getPosition().x; }

    float getPosY() { return sprite.getPosition().y; }

    void setPosX(float x) { sprite.setPosition(x, sprite.getPosition().y); }

    void setPosY(float y) { sprite.setPosition(sprite.getPosition().x, y); }

    void setPosition(float x, float y) { sprite.setPosition(x, y); }

    float getScaleX() { return sprite.getScale().x; }

    float getScaleY() { return sprite.getScale().y; }

    void setScaleX(float x) { sprite.setScale(x, sprite.getScale().y); }

    void setScaleY(float y) { sprite.setScale(sprite.getScale().x, y); }

    void setScale(float x, float y) { sprite.setScale(x, y); }

    float getOriginX() { return sprite.getOrigin().x; }

    float getOriginY() { return sprite.getOrigin().y; }

    void setOriginX(float x) { sprite.setOrigin(x, sprite.getOrigin().y); }

    void setOriginY(float y) { sprite.setOrigin(sprite.getOrigin().x, y); }

    void setOrigin(float x, float y) { sprite.setOrigin(x, y); }

    float getRotation() { return sprite.getRotation(); }

    void setRotation(float r) { sprite.setRotation(r); }

    std::tuple<int, int, int, int> getTextureRect() {
        return std::make_tuple(
            sprite.getTextureRect().left, sprite.getTextureRect().top,
            sprite.getTextureRect().width, sprite.getTextureRect().height);
    }

    void setTextureRect(int left, int top, int width, int height) {
        sprite.setTextureRect(sf::IntRect(left, top, width, height));
    }

    int getTextureWidth() { return sprite.getTexture()->getSize().x; }

    int getTextureHeight() { return sprite.getTexture()->getSize().y; }

    void setColor(int red, int green, int blue, int alpha) {
        sprite.setColor(sf::Color(red, green, blue, alpha));
    }

    std::tuple<int, int, int, int> getColor() {
        return std::make_tuple(sprite.getColor().r, sprite.getColor().g,
                               sprite.getColor().b, sprite.getColor().a);
    }

    void loadFromFile(std::string filename);

    sf::Sprite getSprite() { return sprite; }
};