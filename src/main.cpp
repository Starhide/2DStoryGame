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

//#include "Entity/EntityLoader.h"

std::map<std::string, sf::Texture> textures::loadedTextures;
std::map<std::string, Entity*> entities;
std::vector<sol::table*> draws;
std::vector<sol::table*> updates;

Entity* getEntity(std::string id){
    return entities[id];
}

Entity* loadEntity(std::map<std::string, sol::table> &components,
                   sol::table &pattern, sol::table &init) {

    auto e = new Entity();
    e->setID(init["id"]);

    if(init["parent"]){
        e->setParent(getEntity(init["parent"]));
    } else {
        e->setParent(nullptr);
    }

    sol::table t = pattern;
    sol::table comps = init["components"];

    for (auto &kvp : comps) {
        for (auto &kvp2 : kvp.second.as<sol::table>()) {
            t[kvp.first][kvp2.first] = kvp2.second;
        }
    }

    std::string key;

    for (auto &kvp : t) {
        key = kvp.first.as<std::string>();
        sol::table comp = components[key]["new"](*e, kvp.second);
        e->addComponent(key, comp);
        if(comp["draw"]){
            draws.push_back(&(e->get(key)));
        }
        if(comp["update"]){
            updates.push_back(&(e->get(key)));
        }
        
        std::cout << "Added " << key << " to " << e->getID() << std::endl;
    }

    return e;
}

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
        "Sprite",           sol::constructors<LuaSprite(std::string)>(), 
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
        "get",  &Entity::get,
        "parent", sol::property(&Entity::getParent, &Entity::setParent)
        );

    // Global Methods

    lua["isKeyPressed"] = &sf::Keyboard::isKeyPressed;

    // clang-format on
}

void loadComponents(sol::state &lua,
                    std::map<std::string, sol::table> &components) {
    components["Transform"] = lua.script_file("lua/components/Transform.lua");
    components["Graphics"] = lua.script_file("lua/components/Graphics.lua");
    components["Input"] = lua.script_file("lua/components/Input.lua");
}

int main() {
    //using namespace el;

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
    patterns["hat"] = lua.script_file("lua/entities/hat.lua");

    //Launch main.lua



    lua.script_file("lua/map.lua");
    sol::table ents = lua["entities"];
    Entity *e;

    for (auto &kvp : ents) {
        sol::table initTable = kvp.second;
        auto nw = loadEntity(components, patterns[initTable["typename"]], initTable);
        entities[nw->getID()] = nw;
        if (nw->getID() == "Player1") { 
            e = nw;
        }
    }

    sf::Clock deltaClock;
    sf::Clock fixedClock;
    sf::Time delta;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        delta = deltaClock.restart();

        if(sf::Joystick::isConnected(0)){
            float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
            float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);    
            e->get("Transform")["move"](e->get("Transform"), x * delta.asSeconds(), y * delta.asSeconds());
        }

        //Physics
        for(auto table : updates){
            (*table)["update"](*table, delta.asSeconds());
        }

        window.clear();

        //Draw everything
        for(auto table : draws){
            (*table)["draw"](*table, &window);
        }
        
        window.display();

        if (fixedClock.getElapsedTime().asSeconds() > 0.05f) {
            //Possibly remove
            fixedClock.restart();
        }
    }

    return 0;
}
