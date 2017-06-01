#pragma once

#include <iostream>

namespace luabridge{
    class LuaRef;
}

class Entity;

class Component {
    public:
        virtual ~Component() {};
};