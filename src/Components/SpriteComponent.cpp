#include <lua5.2/lauxlib.h>
#include <lua5.2/lua.hpp>
#include <lua5.2/lualib.h>
#include <LuaBridge.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "SpriteComponent.h"
#include "../Entity/Entity.h"
#include "../TextureController.h"

SpriteComponent::SpriteComponent(luabridge::LuaRef& componentTable){
    using namespace luabridge;
    this->sprite = sf::Sprite();

    LuaRef filenameRef = componentTable["filename"];
    if(filenameRef.isString()){
        std::string file = filenameRef.cast<std::string>();
        sf::Texture* text = textures::loadTexture(file);
        this->sprite.setTexture(*text);
    } else {
        std::cout << "filename is not a string in SpriteComponent." << std::endl;
    }
}

void SpriteComponent::draw(Entity *e, sf::RenderWindow& win){
       sprite.setPosition(e->getPosition());
       sprite.setRotation(e->getRotation());
       sprite.setScale(e->getScale());
       win.draw(sprite);
}
