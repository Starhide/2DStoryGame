#include <iostream>

#include "Entity.h"
#include "Component.h"

//TODO change to allow multiple of one type
void Entity::addComponent(std::string type, sol::table c){
    components[type] = c;
} 