#pragma once

class Entity;

class EntityHandle {
public:
    void setPosition(float x, float y);
    float getPosX();
    float getPosY();

    float getDeltaTime();
private:
    Entity* e;
}