#include <lua5.2/lauxlib.h>
#include <lua5.2/lua.hpp>
#include <lua5.2/lualib.h>
#include <LuaBridge.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "SpriteComponent.h"
#include "../Entity/Entity.h"

SpriteComponent::SpriteComponent(Entity* parent, luabridge::LuaRef& componentTable): Component(parent){
    using namespace luabridge;
    auto filenameRef = componentTable["filename"];
    if(filenameRef.isString()){
        std::string file = filenameRef.cast<std::string>();
        sf::Texture texture;
        if(texture.loadFromFile(file.c_str())){
            sprite = sf::Sprite(texture);
        } else {
            std::cout << "Could not load " << file << " in SpriteComponent of entity " << parent->getType();
        }
    } else {
        std::cout << "filename is not a string in SpriteComponent of entity " << parent->getType();
    }
}

void SpriteComponent::draw(sf::RenderWindow& win){
            sprite.setPosition(parent->getPosition());
            sprite.setRotation(parent->getRotation());
            sprite.setScale(parent->getScale());
           win.draw(sprite);
}
