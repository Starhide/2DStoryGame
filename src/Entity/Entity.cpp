#include <iostream>

#include "Entity.h"
#include "Component.h"

Entity::~Entity(){
    /*for(auto& c : components){
        delete c.second;
    }*/  
} 

//TODO change to allow multiple of one type
void Entity::addComponent(std::string type, sol::table c){
    components[type] = c;
}