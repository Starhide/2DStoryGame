#pragma once

#include <map>
#include <string>
#include <sol.hpp>

class Entity{
    private:
        std::string id;
        std::string type;
        std::map<std::string, sol::table*> components;

    public:
        ~Entity();

        void addComponent(std::string type, sol::table* c);

        sol::table* get(std::string id){
            return components[id];
        }

        void setID(const std::string& id){
            this->id = id;
        }

        void setType(const std::string& type){
            this->type = type;
        }

        std::string getID() const{
            return id;
        }

        std::string getType() const{
            return type;
        }
};