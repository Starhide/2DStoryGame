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
#include "Entity/Entity.h"
#include "Globals.h"

#include "Entity/EntityLoader.h"

std::map<std::string, sf::Texture> textures::loadedTextures;
sf::Time globals::delta;
std::vector<Input *> globals::inputlisteners;

int main() {
    using namespace el;
 
    sf::RenderWindow window(sf::VideoMode(800, 800), "C-Lu");
    sf::View worldView(sf::Vector2f(0, 0), sf::Vector2f(200, 200));
    window.setView(worldView);

    sol::state lua;

    lua.script_file("lua/Test.lua");
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

        e->get<Graphics>()->drawUpdate(e, window);

        window.display();

        if(fixedClock.getElapsedTime().asSeconds() > 0.05f){
            e->get<Graphics>()->fixedUpdate(e);
            fixedClock.restart();
        }
    }

    return 0;
}
