/*
 * main.cpp
 *
 *  Created on: May 13, 2017
 *      Author: blake
 */

#include <SFML/Graphics.hpp>
#include <iostream>

#include <sol.hpp>

#include "Entity/Entity.h"
#include "Globals.h"
#include "LuaSprite.h"
#include "TextureController.h"

#include "Entity/EntityLoader.h"

std::map<std::string, sf::Texture> textures::loadedTextures;
sf::Time globals::delta;

void initializeLuaState(sol::state &lua) {
    // clang-format off
    lua.new_usertype<sf::Clock>(
        "Clock", sol::constructors<sf::Clock()>(),
        "restart", &sf::Clock::restart,
        "getElapsedTime", &sf::Clock::getElapsedTime
        );

    lua.new_usertype<sf::Time>(
        "Time", sol::constructors<sf::Time()>(),
        "asSeconds", &sf::Time::asSeconds
        );

    lua.new_usertype<sf::Vector2f>(
        "Vector", sol::constructors<sf::Vector2f(), sf::Vector2f(float, float)>(),
        "x", &sf::Vector2f::x,
        "y", &sf::Vector2f::x
    );

    lua.new_usertype<LuaSprite>(
        "Sprite", sol::constructors<LuaSprite(std::string)>(), 
        "getPosition",      &LuaSprite::getPosition,
        "setPosition",      &LuaSprite::setPosition,
        "getScale",         &LuaSprite::getScale,
        "setScale",         &LuaSprite::setScale,
        "getRotation",      &LuaSprite::getRotation,
        "setRotation",      &LuaSprite::setRotation,
        "getTextureRect",   &LuaSprite::getTextureRect, 
        "setTextureRect",   &LuaSprite::setTextureRect, 
        "getTextureWidth",  &LuaSprite::getTextureWidth, 
        "getTextureHeight", &LuaSprite::getTextureHeight, 
        "getColor",         &LuaSprite::getColor,
        "setColor",         &LuaSprite::setColor, 
        "loadFromFile",     &LuaSprite::loadFromFile,
        "draw",             &LuaSprite::draw
        );

    lua.new_usertype<Entity>("Entity", 
        "id",   sol::property(&Entity::getID, &Entity::setID), 
        "type", sol::property(&Entity::getType, &Entity::setType), 
        "get",  &Entity::get
        );

    // Global Methods

    // clang-format on
}

void loadComponents(sol::state &lua,
                    std::map<std::string, sol::table> &components) {
    components["Transform"] = lua.script_file("lua/components/Transform.lua");
    components["Graphics"] = lua.script_file("lua/components/Graphics.lua");
}

int main() {
    using namespace el;

    //Initilaize window and view
    sf::RenderWindow window(sf::VideoMode(800, 800), "C-Lu");
    sf::View worldView(sf::Vector2f(0, 0), sf::Vector2f(200, 200));
    window.setView(worldView);

    //Initilize Lua
    sol::state lua;
    lua.open_libraries();
    initializeLuaState(lua);

    //Load Components
    std::map<std::string, sol::table> components;
    loadComponents(lua, components);

    //Load entity patterns
    std::map<std::string, sol::table> patterns;
    patterns["ghost"] = lua.script_file("lua/entities/ghost.lua");

    //Launch main.lua



    lua.script_file("lua/map.lua");
    sol::table entities = lua["entities"];
    std::vector<Entity *> enits;
    Entity *e;

    for (auto &kvp : entities) {
        sol::table initTable = kvp.second;
        auto nw = loadEntity(components, patterns["ghost"], initTable);
        enits.push_back(nw);
        if (nw->getID() == "Player1") {
            e = nw;
        }
    }

    sf::Clock deltaClock;
    sf::Clock fixedClock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        globals::delta = deltaClock.restart();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            e->get("Transform")["move"](e->get("Transform"), 0,
                                        -100 * globals::delta.asSeconds());
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            e->get("Transform")["move"](e->get("Transform"), 0,
                                        100 * globals::delta.asSeconds());
        }

        window.clear();
        e->get("Graphics")["drawUpdate"](e->get("Graphics"), &window);
        e->get("Graphics")["frameUpdate"](e->get("Graphics"));
        // window.draw(timer["getDrawable"](timer));
        // sol::function du = e->get("Graphics")->traverse_get<sol::function,
        // std::string>("drawUpdate");
        // du(window);

        window.display();

        if (fixedClock.getElapsedTime().asSeconds() > 0.05f) {

            // std::cout << timer["update"](timer) << std::endl;
            fixedClock.restart();
        }
    }

    return 0;
}
