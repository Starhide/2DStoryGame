#pragma once

#include <string>
#include <vector>

#include <lua5.2/lauxlib.h>
#include <lua5.2/lua.hpp>
#include <lua5.2/lualib.h>

#include <LuaBridge.h>

namespace luah {
bool loadScript(lua_State *L, const std::string &filename);
void lua_gettostack(lua_State *L, const std::string &variableName);
void loadGetKeysFunction(lua_State *L);
std::vector<std::string> getTableKeys(lua_State *L, const std::string &name);
std::vector<std::string> getTableKeys(luabridge::LuaRef &table);
}