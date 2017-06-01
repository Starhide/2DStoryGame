#include "InputComponent.h"

#include <iostream>

#include "../Lua/LuaHelper.h"

InputComponent::InputComponent(luabridge::LuaRef &componentTable) {
    //functions = std::map<std::string, luabridge::LuaRef>();
    auto v = luah::getTableKeys(componentTable);

    for (auto &key : v) {
        componentTable[key]();
        luabridge::LuaRef funct = componentTable[key];
        this->functions[key] = &funct;
        std::cout << key << std::endl;
    }
}

luabridge::LuaRef* InputComponent::getFunction(const std::string &key) {
    if(functions.count(key)){
      return this->functions[key];
    }
    return nullptr; 
}