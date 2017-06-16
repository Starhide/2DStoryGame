#pragma once

#include "../Entity/Component.h"

#include <map>
#include <string>

class Input : public Component {
  private:
    std::map<std::string, luabridge::LuaRef *> functions;

  public:
    Input(luabridge::LuaRef &componentTable);
    
    luabridge::LuaRef *getFunction(const std::string &key);

    void setAttributes(luabridge::LuaRef &table);

    // luabridge::LuaRef getFunction(const std::string &key) { return
    // &functions[key]; }

    // void setFunction(const std::string &key, const luabridge::LuaRef &funct);
};
