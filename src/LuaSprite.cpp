#include "LuaSprite.h"
#include "TextureController.h"
#include <cmath>


LuaSprite::LuaSprite(std::string filename){
    sf::Texture* text = textures::loadTexture(filename);
    this->sprite = sf::Sprite(*text);
} 

void LuaSprite::loadFromFile(std::string filename){
    sf::Texture* text = textures::loadTexture(filename);
    this->sprite = sf::Sprite(*text);
}   

void LuaSprite::draw(sf::RenderWindow &win) { 
    win.draw(this->sprite); 
}

void LuaSprite::drawWithTransform(sf::RenderWindow &win, sf::Transform &transform) {
    win.draw(this->sprite, transform); 
}

