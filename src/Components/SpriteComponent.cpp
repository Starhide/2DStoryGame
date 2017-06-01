#include <SFML/Graphics.hpp>
#include <iostream>

#include "../Lua/LuaHelper.h"

#include "../Entity/Entity.h"
#include "../TextureController.h"
#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(luabridge::LuaRef &componentTable) {
    using namespace luabridge;
    this->sprite = sf::Sprite();

    LuaRef filenameRef = componentTable["filename"];
    if (filenameRef.isString()) {
        std::string file = filenameRef.cast<std::string>();
        sf::Texture *text = textures::loadTexture(file);
        if (!(text == nullptr)) {
            this->sprite.setTexture(*text);
        } else {
            std::cout << "@! " << file << " failed to load in SpriteComponent."
                      << std::endl;
        }
    } else {
        std::cout << "@! Filename is not a string in SpriteComponent."
                  << std::endl;
    }
}

void SpriteComponent::draw(Entity *e, sf::RenderWindow &win) {
    sprite.setPosition(e->getPosition());
    sprite.setRotation(e->getRotation());
    sprite.setScale(e->getScale());
    win.draw(sprite);
}
