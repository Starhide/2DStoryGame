/*
 * main.cpp
 *
 *  Created on: May 13, 2017
 *      Author: Blake Bauer
 */

#include <SFML/Graphics.hpp>
#include <iostream>

#include <sol.hpp>
#include <json.hpp>

#include "Globals.h"
#include "LuaSprite.h"
#include "TextureController.h"
#include "WindowL.h"

using json = nlohmann::json;

std::map<std::string, sf::Texture> textures::loadedTextures;
std::map<std::string, std::vector<sol::function>> eventListeners;
std::vector<sol::function> draws;
std::vector<sol::function> updates;

void pushEvent(sol::table event) {
    for (auto funct : eventListeners[event["type"]]) {
        funct(event);
    }
}

void addEventListener(std::string type, sol::function funct) {
    if (eventListeners.count(type) == 0) {
        eventListeners[type] = std::vector<sol::function>();
    }
    eventListeners[type].push_back(funct);
}

void addRenderFunction(sol::function funct){
    draws.push_back(funct);
}

void addUpdateFunction(sol::function funct){
    updates.push_back(funct);
}

std::tuple<int, int> getMousePosition(WindowL& win){
    return std::make_tuple(sf::Mouse::getPosition(win.getWindow()).x, sf::Mouse::getPosition(win.getWindow()).y);
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
        "getOrigin",        &LuaSprite::getOrigin,
        "setOrigin",        &LuaSprite::setOrigin,
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
    {
        auto window_register = lua.create_simple_usertype<WindowL>(
            "Window",                       sol::constructors<WindowL(std::string, unsigned int, unsigned int)>(), 
            "draw",                         &WindowL::draw,
            "close",                        &WindowL::close,
            "getWindowSize",                &WindowL::getWindowSize,
            "setWindowSize",                &WindowL::setWindowSize,
            "setWindowTitle",               &WindowL::setWindowTitle,
            "setWindowIcon",                &WindowL::setWindowIcon,
            "setVSync",                     &WindowL::setVSync,
            "setCursorVisiblity",           &WindowL::setCursorVisiblity,
            "setMouseCursorGrabbed",        &WindowL::setMouseCursorGrabbed, 
            "setFrameLimit",                &WindowL::setFrameLimit,
            "setJoystickThreshold",         &WindowL::setJoystickThreshold,
            "setView",                      &WindowL::setView,
            //"getCurrentViewID",             &WindowL::getCurrentViewID,
            "mapPixelToCoords",             &WindowL::mapPixelToCoords,
            "mapPixelToCoordsThroughView",  &WindowL::mapPixelToCoordsThroughView,
            "mapCoordsToPixel",             &WindowL::mapCoordsToPixel,
            "mapCoordsToPixelThroughView",  &WindowL::mapCoordsToPixelThroughView,
            "getViewDimensions",            &WindowL::getViewDimensions,
            "getRenderSize",                &WindowL::getRenderSize,
            "addView",                      &WindowL::addView,
            "removeView",                   &WindowL::removeView,
            "getViewCenter",                &WindowL::getViewCenter,
            "setViewCenter",                &WindowL::setViewCenter,
            "getViewSize",                  &WindowL::getViewSize,
            "setViewSize",                  &WindowL::setViewSize,
            "getViewRotation",              &WindowL::getViewRotation,
            "setViewRotation",              &WindowL::setViewRotation,
            "moveView",                     &WindowL::moveView,
            "rotateView",                   &WindowL::rotateView,
            "zoomView",                     &WindowL::zoomView
        );
        window_register.set("viewContainsPoint", &WindowL::viewContainsPoint);
        lua.set_usertype("Window", window_register);
    }

    // Global Methods

    lua["IsKeyPressed"] = &sf::Keyboard::isKeyPressed;
    lua["GetMousePosition"] = &getMousePosition;
    lua["AddEventListener"] = &addEventListener;
    lua["AddRenderFunction"] = &addRenderFunction;
    lua["AddUpdateFunction"] = &addUpdateFunction;
    lua["PushEvent"] = &pushEvent;

    // clang-format on
}

int main() {
    // Load Config File


    // Initilaize window and view
    WindowL window("C-Lu", 800, 800);

    // Initilize Lua
    sol::state lua;
    lua.open_libraries();
    initializeLuaState(lua);
    lua["window"] = &window;

    lua.script_file("main.lua");

    sf::Clock deltaClock;
    sf::Time delta;

    while (window.getWindow().isOpen()) {
        sf::Event event;
        while (window.getWindow().pollEvent(event)) {
            // clang-format off
			sol::table e;
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                e = lua.create_table_with(
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
                e = lua.create_table_with(
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
                e = lua.create_table_with(
                    "type",     "TextEntered", 
                    "unicode",  event.text.unicode
                );
                pushEvent(e);
                break;
            }
            // clang-format on
        }

        delta = deltaClock.restart();

        for(auto& funct : updates){
            funct(delta.asSeconds());
        }

        window.getWindow().clear();

        for(auto& funct : draws){
            funct(window);
        }

        window.getWindow().display();
    }

    return 0;
}
