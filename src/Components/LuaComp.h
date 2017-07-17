#pragma once

#include "../Entity/Component.h"

#include <string>

class LuaComp : public Component {
  private:
    std::string type;
    sol::table* lua_component;

  public:
    LuaComp(std::string type, sol::table &table);

    void setAttributes(sol::table &table);

    sol::function get(std::string funct);
};
