#pragma once

#include <iostream>
#include <sol.hpp>

class Entity;

class Component {
    public:
        virtual ~Component() {};

        virtual void setAttributes(sol::table &table) = 0;
};