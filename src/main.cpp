/*
 * main.cpp
 *
 *  Created on: May 13, 2017
 *      Author: blake
 */

// main.cpp

#include <iostream>

#include <lua5.2/lauxlib.h>
#include <lua5.2/lua.hpp>
#include <lua5.2/lualib.h>
#include <LuaBridge.h>

using namespace std;
using namespace luabridge;

int gamestate;

struct Player
{
};

void addItem()
{
}

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
    gamestate = 1;
    loop();
    return 0;
}
