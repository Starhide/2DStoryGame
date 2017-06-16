/*
 * main.cpp
 *
 *  Created on: May 13, 2017
 *      Author: blake
 */

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Lua/LuaHelper.h"

#include "Components/Input.h"
#include "Components/Sprite.h"
#include "Entity/Entity.h"
#include "Globals.h"
#include "TextureController.h"
#include "Entity/EntityLoader.h"

std::map<std::string, sf::Texture> textures::loadedTextures;
sf::Time globals::delta;
std::vector<Input *> globals::inputlisteners;

int main() {
    using namespace luabridge;
    using namespace el;

    sf::RenderWindow window(sf::VideoMode(800, 800), "C-Lu");
    sf::View worldView(sf::Vector2f(0, 0), sf::Vector2f(200, 200));
    window.setView(worldView);

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    luah::loadGetKeysFunction(L);  
    
    luah::loadScript(L, "lua/Test.lua");
    LuaRef entities = getGlobal(L, "entities");
    std::vector<Entity*> enits;
    Entity* e;

    auto it = Iterator(entities);
    while(!it.isNil()){
        LuaRef table = it.value();
        auto nw = createEntity(L, table);
        enits.push_back(nw);
        if(nw->getID() == "Player1"){
            e = nw;
        }
        ++it;
    }

    sf::Clock deltaClock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        globals::delta = deltaClock.restart();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            e->setPosition(e->getPosition().x,
                           e->getPosition().y -
                               100 * globals::delta.asSeconds());
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            e->setPosition(e->getPosition().x,
                           e->getPosition().y +
                               100 * globals::delta.asSeconds());
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            e->setPosition(e->getPosition().x -
                               100 * globals::delta.asSeconds(),
                           e->getPosition().y);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            e->setPosition(e->getPosition().x +
                               100 * globals::delta.asSeconds(),
                           e->getPosition().y);
        }

        window.clear();

        e->get<Sprite>()->draw(e, window);

        window.display();
    }

    lua_close(L);
    return 0;
}
