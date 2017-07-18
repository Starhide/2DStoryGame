/*
 * main.cpp
 *
 *  Created on: May 13, 2017
 *      Author: blake
 */

#include <SFML/Graphics.hpp>
#include <iostream>

#include <sol.hpp>
 
#include "TextureController.h" 
#include "Components/Input.h"
#include "Components/Graphics.h"
#include "LuaSprite.h"
#include "Entity/Entity.h"
#include "Globals.h"

std::map<std::string, sf::Texture> textures::loadedTextures;
sf::Time globals::delta;
std::vector<Input *> globals::inputlisteners;

void draw(LuaSprite& spr, sf::RenderWindow& win){
    win.draw(spr.getSprite());
}

void initializeLuaState(sol::state &lua){
    //User Types
    lua.new_usertype<sf::Clock>("Clock",
        sol::constructors<sf::Clock()>(),
        "restart", &sf::Clock::restart,
        "getElapsedTime", &sf::Clock::getElapsedTime
    );

    lua.new_usertype<sf::Time>("Time",
        sol::constructors<sf::Time()>(),
        "asSeconds", &sf::Time::asSeconds
    );

    lua.new_usertype<LuaSprite>("Sprite",
        sol::constructors<LuaSprite(std::string)>(),
        "posX", sol::property(&LuaSprite::getPosX, &LuaSprite::setPosX),
        "posY", sol::property(&LuaSprite::getPosY, &LuaSprite::setPosY),
        "scaleX", sol::property(&LuaSprite::getScaleX, &LuaSprite::setScaleX),
        "scaleY", sol::property(&LuaSprite::getScaleY, &LuaSprite::setScaleY),
        "originX", sol::property(&LuaSprite::getOriginX, &LuaSprite::setOriginX),
        "originY", sol::property(&LuaSprite::getOriginY, &LuaSprite::setOriginY),
        "rotation", sol::property(&LuaSprite::getRotation, &LuaSprite::setRotation),
        "getTextureRect", &LuaSprite::getTextureRect,
        "setTextureRect", &LuaSprite::setTextureRect,
        "getTextureWidth", &LuaSprite::getTextureWidth, 
        "getTextureHeight", &LuaSprite::getTextureHeight,
        "getColor", &LuaSprite::getColor,
        "setColor", &LuaSprite::setColor,
        "loadFromFile", &LuaSprite::loadFromFile
    ); 
 
    lua.new_usertype<Entity>("Entity",
        "id", sol::property(&Entity::getID, &Entity::setID),
        "type", sol::property(&Entity::getType, &Entity::setType),
        "get", &Entity::get
    );

    //Global Methods
    lua["Draw"] = draw;
}

int main() {
    //using namespace el;
 
    sf::RenderWindow window(sf::VideoMode(800, 800), "C-Lu");
    sf::View worldView(sf::Vector2f(0, 0), sf::Vector2f(200, 200));
    window.setView(worldView);

    sol::state lua;
    lua.open_libraries();
    initializeLuaState(lua);
    
    lua.script_file("lua/test.lua");

    sol::table timer = lua["myshape"];

    /*lua.script_file("lua/Test.lua");
    sol::table entities = lua["entities"];
    std::vector<Entity*> enits;
    Entity* e;

    for(auto &kvp : entities){
        sol::table initTable = kvp.second;
        auto nw = createEntity(lua, initTable);
        enits.push_back(nw);
        if(nw->getID() == "Player1"){
            e = nw;
        }
    }*/

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

        /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            e->setPosition(e->getPosition().x,
                           e->getPosition().y -
                               100 * globals::delta.asSeconds());
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            e->setPosition(e->getPosition().x,
                           e->getPosition().y +
                               100 * globals::delta.asSeconds());
        }*/

        window.clear();

        //e->get<Graphics>()->drawUpdate(e, window);
        //window.draw(timer["getDrawable"](timer));
        timer["drawUpdate"](timer, &window);
        timer["frameUpdate"](timer);

        window.display();

        if(fixedClock.getElapsedTime().asSeconds() > 0.05f){
            
            //std::cout << timer["update"](timer) << std::endl;
            fixedClock.restart();
        }
    }

    return 0;
}
