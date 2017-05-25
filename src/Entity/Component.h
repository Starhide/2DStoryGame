#pragma once

#include <iostream>

namespace luabridge{
    class luaRef;
}

class Entity;

class Component {
    public:
        virtual ~Component() {};
};