#pragma once

namespace luabridge{
    class luaRef;
}

class Entity;

class Component {
    public:
        virtual ~Component() {};
        Component(Entity* par) : parent(par){};
    protected:
        const Entity* parent;
};