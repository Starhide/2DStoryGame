#include "EntityHandler.h"

#include "Entity.h"
#include "../Globals.h"

void EntityHandle::setPosition(float x, float y) {
    this->e->setPosition(x, y);
}

float EntityHandle::getPosX() {
    return this->e->getPosition.x;
}

float EntityHandle::getPosY() {
    return this->e->getPosition.y;
}

float EntityHandle::getDeltaTime() {
    return globals::delta.asSeconds();
}