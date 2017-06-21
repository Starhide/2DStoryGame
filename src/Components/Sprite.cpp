#include <SFML/Graphics.hpp>
#include <iostream>

#include "../Entity/Entity.h"
#include "../TextureController.h"
#include "Sprite.h"

Sprite::Sprite(sol::table &componentTable) {
    this->sprite = sf::Sprite();

    sol::object filenameRef = componentTable["filename"];
    if (filenameRef.valid()) {
        std::string file = filenameRef.as<std::string>();
        sf::Texture *text = textures::loadTexture(file);
        if (!(text == nullptr)) {
            this->sprite.setTexture(*text);
        } else {
            std::cout << "@! " << file << " failed to load in Sprite Component."
                      << std::endl;
        }
    } else {
        std::cout << "@! Filename is not a string in Sprite Component."
                  << std::endl;
    }
}

void Sprite::draw(Entity *e, sf::RenderWindow &win) {
    sprite.setPosition(e->getPosition());
    sprite.setRotation(e->getRotation());
    sprite.setScale(e->getScale());
    win.draw(sprite);
}

void Sprite::setAttributes(sol::table &table){
    
}
