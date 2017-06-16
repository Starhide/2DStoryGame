#pragma once

#include <map>
#include <string>
#include <typeindex>
#include <SFML/Graphics/Transformable.hpp>

class Component;

class Instance : public sf::Transformable{
    private:
        Entity* type;
        std::map<std::type_index, Component*> components;

    public:
        ~Instance();

        void addComponent(std::type_index type, Component* c);

        template <typename T>
        T* get(){
            auto it = components.find(std::type_index(typeid(T)));
            if(it != components.end()){
                return dynamic_cast<T*>(it->second);
            }
            return nullptr;
        }

        void setType(const std::string& type){
            this->type = type;
        }

        std::string getType() const{
            return type;
        }
};