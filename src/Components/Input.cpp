#include "Input.h"

#include <iostream>

Input::Input(sol::table &componentTable) {
    // functions = std::map<std::string, luabridge::LuaRef>();
    /*auto v = luah::getTableKeys(componentTable);

    for (auto &key : v) {
        componentTable[key]();
        luabridge::LuaRef funct = componentTable[key];
        this->functions[key] = &funct;
        std::cout << key << std::endl;
    }*/
}

sol::function *Input::getFunction(const std::string &key) {
    if (functions.count(key)) {
        return this->functions[key];
    }
    return nullptr;
}

void Input::setAttributes(sol::table &table){

}