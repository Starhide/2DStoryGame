#pragma once

#include "../Entity/Component.h"

#include <map>
#include <string>

class InputComponent : public Component {
  private:
    std::map<std::string, luabridge::LuaRef*> functions;

  public:
    InputComponent(luabridge::LuaRef &componentTable);
    luabridge::LuaRef* getFunction(const std::string &key);

    //luabridge::LuaRef getFunction(const std::string &key) { return &functions[key]; }

    //void setFunction(const std::string &key, const luabridge::LuaRef &funct);
};
