local Vector = require 'modules/engine/lib/Vector'

Physics = {}
Physics.__index = Physics

function Physics.new (entity, init)
    local o = {}
    setmetatable(o, Physics)
    o.entity = entity
    o.mass = init.mass
    o.velocity = Vector(init.velocity or 0, 0)
    o.acceleration = Vector(init.acceleration or 0, 0)
    o.angVelocity = init.angVelocity or 0
    o.angAcceleration = init.angAcceleration or 0

    return o
end

function Physics:update(dt) 
    trans = self.entity.components.Transform
    if not (self.velocity == Vector(0,0)) then
        trans:move((self.velocity*dt):unpack())
    end
    if not (self.acceleration == Vector(0,0)) then
        self.velocity = self.velocity + self.acceleration * dt
    end

    if not (self.angVelocity == 0) then
        trans:rotate(self.angVelocity * dt)
    end
    if not (self.angAcceleration == 0) then
        self.angVelocity = self.angVelocity + self.angAcceleration * dt
    end
end

function Physics:getGlobalVelocity()
    if self.entity.parent and self.entity.parent.components.Physics then
		return self.entity.parent.components.Physics:getGlobalVelocity() + self.velocity
    end
    return self.velocity
end

function Physics:getLocalVelocity()
    return self.velocity
end

function Physics:setVelocity(x, y)
    self.velocity = Vector(x, y) + self.velocity
end

function Physics:getGlobalAcceleration()
    if self.entity.parent and self.entity.parent.components.Physics then
        return self.entity.parent.components.Physics:getGlobalAcceleration() + self.acceleration
    end
    return self.acceleration
end

function Physics:getLocalAcceleration()
    return self.acceleration
end

function Physics:setAcceleration(x, y)
    self.acceleration = Vector(x, y) + self.acceleration
end

function Physics:getGlobalAngVel()
    if self.entity.parent and self.entity.parent.components.Physics then
        return self.entity.parent.components.Physics:getGlobalAngVel() + self.angVelocity
    end
    return self.angVelocity
end

function Physics:getLocalAngVel()
    return self.angVelocity
end

function Physics:setAngVel(x)
    self.angVelocity = x + self.angVelocity
end

function Physics:getGlobalAngAccel()
    if self.entity.parent and self.entity.parent.components.Physics then
        return self.entity.parent.components.Physics:getGlobalAngAccel() + self.angAcceleration
    end
    return self.angAcceleration
end

function Physics:getLocalAngAccel()
    return self.angAcceleration
end

function Physics:setAngAccel(x)
    self.angAcceleration = x + self.angAcceleration
end

return Physics