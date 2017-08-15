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
std::map<std::string, Entity *> entities;
std::map<std::string, std::vector<sol::function>> eventListeners;
std::vector<sol::table *> draws;
std::vector<sol::table *> updates;

void pushEvent(sol::table event) {
    for (auto funct : eventListeners[event.type]) {
        funct(event);
    }
}

void addEventListener(std::string type, sol::function funct) {
    if (!eventListeners[type]) {
        eventListeners[type] = std::vector<sol::function>();
    }
    eventListeners[type].push_back(funct);
}

Entity *getEntity(std::string id) {
    return entities[id];
}

Entity *loadEntity(sol::state &lua,
                   std::map<std::string, sol::table> &components,
                   sol::table &pattern, sol::table &init) {

    auto e = new Entity();
    e->setID(init["id"]);

    if (init["parent"]) {
        e->setParent(getEntity(init["parent"]));
    } else {
        e->setParent(nullptr);
    }

    // sol::table t = pattern;
    sol::table comps = init["components"];

    /*for (auto &kvp : comps) {
        for (auto &kvp2 : kvp.second.as<sol::table>()) {
            t[kvp.first][kvp2.first] = kvp2.second;
        }
    }*/

    for (auto &kvp : pattern) {
        if (!comps[kvp.first]) {
            comps.set(kvp.first, lua.create_table());
        }
        for (auto &kvp2 : kvp.second.as<sol::table>()) {
            if (!(comps[kvp.first][kvp2.first])) {
                comps[kvp.first][kvp2.first] = kvp2.second;
            }
        }
    }

    std::string key;

    for (auto &kvp : comps) {
        key = kvp.first.as<std::string>();
        sol::table comp = components[key]["new"](*e, kvp.second);
        e->addComponent(key, comp);
        if (comp["draw"]) {
            draws.push_back(&(e->get(key)));
        }
        if (comp["update"]) {
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

    lua.new_usertype<sf::Transform>(
        "Matrix",   sol::constructors<sf::Transform(float,float,float,float,float,float,float,float,float), 
                                        sf::Transform(sf::Transform)>(),
        "combine", &sf::Transform::combine
    );

    lua.new_usertype<LuaSprite>(
        "Sprite",           sol::constructors<LuaSprite(std::string)>(), 
        "getPosition",      &LuaSprite::getPosition,
        "setPosition",      &LuaSprite::setPosition,
        "getScale",         &LuaSprite::getScale,
        "setScale",         &LuaSprite::setScale,
        "getOrigin",         &LuaSprite::getOrigin,
        "setOrigin",         &LuaSprite::setOrigin,
        "getRotation",      &LuaSprite::getRotation,
        "setRotation",      &LuaSprite::setRotation,
        "getTextureRect",   &LuaSprite::getTextureRect, 
        "setTextureRect",   &LuaSprite::setTextureRect, 
        "getTextureWidth",  &LuaSprite::getTextureWidth, 
        "getTextureHeight", &LuaSprite::getTextureHeight, 
        "getColor",         &LuaSprite::getColor,
        "setColor",         &LuaSprite::setColor, 
        "loadFromFile",     &LuaSprite::loadFromFile,
        "draw",             sol::overload(&LuaSprite::draw, &LuaSprite::drawWithTransform) 
        );

    lua.new_usertype<Entity>("Entity", 
        "id",   sol::property(&Entity::getID, &Entity::setID), 
        "type", sol::property(&Entity::getType, &Entity::setType), 
        "get",  &Entity::get,
        "parent", sol::property(&Entity::getParent, &Entity::setParent)
        );

    // Global Methods

    lua["isKeyPressed"] = &sf::Keyboard::isKeyPressed;
    lua["addEventListener"] = &addEventListener;
    lua["pushEvent"] = &pushEvent;

    // clang-format on
}

void loadComponents(sol::state &lua,
                    std::map<std::string, sol::table> &components) {
    sol::table comps = lua.script_file("lua/components.lua");

    for (auto &kvp : comps) {
        components[kvp.first.as<std::string>()] =
            lua.script_file(kvp.second.as<std::string>());
    }
}

int main() {
    // using namespace el;

    // Initilaize window and view
    sf::RenderWindow window(sf::VideoMode(800, 800), "C-Lu");
    sf::View worldView(sf::Vector2f(0, 0), sf::Vector2f(200, 200));
    window.setView(worldView);

    // Initilize Lua
    sol::state lua;
    lua.open_libraries();
    initializeLuaState(lua);

    // Load Components
    std::map<std::string, sol::table> components;
    loadComponents(lua, components);

    // Load entity patterns
    std::map<std::string, sol::table> patterns;

    // Launch main.lua

    lua.script_file("lua/map.lua");
    sol::table ents = lua["entities"];
    Entity *e;

    for (auto &kvp : ents) {
        sol::table initTable = kvp.second;
        if (!patterns[initTable["typename"]]) {
            patterns[initTable["typename"]] =
                lua.script_file(initTable["typefile"]);
        }
        auto nw = loadEntity(lua, components, patterns[initTable["typename"]],
                             initTable);
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
            // clang-format off
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                sol::table e = lua.create_table_with(
                    "type",     "KeyPressed", 
                    "code",     event.key.code, 
                    "control",  event.key.control, 
                    "alt",      event.key.alt, 
                    "shift",    event.key.shift, 
                    "system",   event.key.system
                );
                pushEvent(e);
                
                break;
            case sf::Event::KeyReleased:
                sol::table e = lua.create_table_with(
                    "type",     "KeyReleased", 
                    "code",     event.key.code, 
                    "control",  event.key.control, 
                    "alt",      event.key.alt, 
                    "shift",    event.key.shift, 
                    "system",   event.key.system
                );
                pushEvent(e);
                // clang-format on
                break;
            case sf::Event::TextEntered:
                sol::table e = lua.create_table_with(
                    "type",     "TextEntered", 
                    "unicode",  event.text.unicode
                );
                pushEvent(e);
                break;
            }
            // clang-format on
        }

        delta = deltaClock.restart();

        if (sf::Joystick::isConnected(0)) {
            float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
            float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
            e->get("Transform")["move"](e->get("Transform"),
                                        x * delta.asSeconds(),
                                        y * delta.asSeconds());
        }

        // Physics
        for (auto table : updates) {
            (*table)["update"](*table, delta.asSeconds());
        }

        window.clear();

        // Draw everything
        for (auto table : draws) {
            (*table)["draw"](*table, &window);
        }

        window.display();

        if (fixedClock.getElapsedTime().asSeconds() > 0.05f) {
            // Possibly remove
            fixedClock.restart();
        }
    }

    return 0;
}
