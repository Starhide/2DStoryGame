/*
 * main.cpp
 *
 *  Created on: May 13, 2017
 *      Author: blake
 */

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Lua/LuaHelper.h"

#include "Components/InputComponent.h"
#include "Components/SpriteComponent.h"
#include "Entity/Entity.h"
#include "TextureController.h"
#include "Globals.h"

std::map<std::string, sf::Texture> textures::loadedTextures;
sf::Time globals::delta;
std::vector<InputComponent*> globals::inputlisteners;

template <typename T>
void addComponent(Entity *e, luabridge::LuaRef &componentTable) {
    e->addComponent(std::type_index(typeid(T)), new T(componentTable));
}

Entity *loadEntity(lua_State *L, const std::string &type) {
    using namespace luabridge;
    auto e = new Entity();
    e->setType(type);
    auto v = luah::getTableKeys(L, type);
    LuaRef entityTable = getGlobal(L, type.c_str());
    for (auto &componentName : v) {
        if (componentName == "SpriteComponent") {
            LuaRef valueTable = entityTable["SpriteComponent"];
            addComponent<SpriteComponent>(e, valueTable);
        } else if (componentName == "InputComponent") {
            LuaRef valueTable = entityTable["InputComponent"];
            addComponent<InputComponent>(e, valueTable);
            globals::inputlisteners.push_back(e->get<InputComponent>());
        }

        std::cout << "Added " << componentName << " to " << type << std::endl;
    }
    return e;
}

int main() {
    // loadedTextures = std::map<std::string, sf::Texture*>();
    using namespace luabridge;
    sf::RenderWindow window(sf::VideoMode(800, 800), "C-Lu");
    sf::View worldView(sf::Vector2f(0, 0), sf::Vector2f(200, 200));
    window.setView(worldView);

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    luah::loadScript(L, "lua/ghost.lua");
    luah::loadGetKeysFunction(L);

    auto e = loadEntity(L, "ghost");
    auto spc = e->get<SpriteComponent>();

    e->setPosition(-50, -10);

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
                           e->getPosition().y - 100 * globals::delta.asSeconds());
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            e->setPosition(e->getPosition().x,
                           e->getPosition().y + 100 * globals::delta.asSeconds());
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            e->setPosition(e->getPosition().x - 100 * globals::delta.asSeconds(),
                           e->getPosition().y);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            e->setPosition(e->getPosition().x + 100 * globals::delta.asSeconds(),
                           e->getPosition().y);
        }

        window.clear();

        spc->draw(e, window);

        window.display();
    }

    lua_close(L);
    return 0;
}
