#include "LuaSprite.h"
#include "TextureController.h"


LuaSprite::LuaSprite(std::string filename){
    sf::Texture* text = textures::loadTexture(filename);
    this->sprite = sf::Sprite(*text);
}

void LuaSprite::loadFromFile(std::string filename){
    sf::Texture* text = textures::loadTexture(filename);
    this->sprite = sf::Sprite(*text);
}