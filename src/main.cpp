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

using namespace std;
using namespace luabridge;

int gamestate;

void loop()
{
    lua_State *L = luaL_newstate();
    luaL_dofile(L, "lua/commands.lua");
    luaL_openlibs(L);
    lua_pcall(L, 0, 0, 0);
    LuaRef command = getGlobal(L, "call");

    while (gamestate > 0)
    {
        string input;
        getline(cin, input);
        if (input.find("exit") != string::npos)
        {
            gamestate = 0;
        }
        else if (input.find("reload") != string::npos)
        {
            luaL_dofile(L, "lua/commands.lua");
        }
        else
        {
            double result{0};
            command(input);
        }
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "C-Lu");
    sf::View worldView(sf::Vector2f(0, 0), sf::Vector2f(200, 200));
    window.setView(worldView);
    sf::Texture ghost;
    if(!ghost.loadFromFile("./images/Ghost.png")){
        cout << "NOOOOO!";
    }

    sf::Sprite ghostS;
    ghostS.setTexture(ghost);
    ghostS.setPosition(-8,-8);
    ghostS.setScale(0.5f, 0.5f);
    
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(ghostS);
        window.display();

    }


    //gamestate = 1;
    //loop();
    return 0;
}
