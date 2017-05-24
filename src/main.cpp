/*
 * main.cpp
 *
 *  Created on: May 13, 2017
 *      Author: blake
 */

// main.cpp

#include <iostream>
#include <SFML/Graphics.hpp>
#include <lua5.2/lauxlib.h>
#include <lua5.2/lua.hpp>
#include <lua5.2/lualib.h>
#include <LuaBridge.h>

#include "Lua/LuaHelper.h"
#include "Entity/Entity.h"
#include "Components/SpriteComponent.h"

using namespace std;
using namespace luabridge;
using namespace luah;

int gamestate;

template <typename T>
void addComponent(Entity* e, luabridge::LuaRef& componentTable) {
    e->addComponent(std::type_index(typeid(T)), new T(e, componentTable));
}

Entity* loadEntity(lua_State* L, const std::string& type) {
    auto e = new Entity();
    e->setType(type);
    auto v = luah::getTableKeys(L, type);
    LuaRef entityTable = getGlobal(L, type.c_str());
    for (auto& componentName : v) {
        if (componentName == "SpriteComponent") {
            LuaRef valueTable = entityTable[componentName];
            addComponent<SpriteComponent>(e, valueTable);
        }
 
        std::cout << "Added " << componentName << " to " << type << std::endl;
    }
    return e;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "C-Lu");
    sf::View worldView(sf::Vector2f(0, 0), sf::Vector2f(200, 200));
    window.setView(worldView);

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    luah::loadScript(L, "lua/ghost.lua");
    luah::loadGetKeysFunction(L);

    auto e = loadEntity(L, "ghost"); //Seg fault
    auto spc = e->get<SpriteComponent>();

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        spc->draw(window);
        window.display();
    }
    
    lua_close(L);
    return 0;
}
