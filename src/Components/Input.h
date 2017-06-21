#pragma once

#include "../Entity/Component.h"

#include <map>
#include <string>

class Input : public Component {
  private:
    std::map<std::string, sol::function *> functions;

  public:
    Input(sol::table &componentTable);
    
    sol::function *getFunction(const std::string &key);

    void setAttributes(sol::table &table);
};
