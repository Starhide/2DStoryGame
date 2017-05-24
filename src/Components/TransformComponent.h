#pragma once

#include <string>
#include "../Entity/Component.h"

namespace sf{
    template <typename T>
    class Vector2;
    typedef Vector2<float> Vector2f;
};

class TransformComponent : public Component{
    private:
        sf::Vector2f position;
        float angle;

    public:
        TransformComponent(Entity* parent): Component(parent){ };

        void setPosition(float x, float y){
            position.x = x;
            position.y = y;
        }

        void setPosition(sf::Vector2f pos){
            position = pos;
        }

        sf::Vector2f getPosition(){
            return position;
        }

        void setAngle(float ang){
            angle = ang;
        }

        float getAngle(){
            return angle;
        }
};