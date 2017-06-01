#pragma once

#include "../Entity/Component.h"
#include <string>

class Entity;

class PlayerController : public Component {
  private:
    float movementSpeed;
    LuaRef onMove;

  public:
    PlayerController(luabridge::LuaRef &componentTable);

    void updateTick(Entity *e);

    void setMovementSpeed(const float *newMoveSpeed) {
        this->movementSpeed = newMoveSpeed;
    }

    float getMovementSpeed() const { return this->movementSpeed; }
};