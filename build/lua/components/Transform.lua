local Vector = require "lua/lib/Vector"

Transform = {}
Transform.__index = Transform

function Transform.new(entity, init)
    local o = {}
    setmetatable(o, Transform)
    o.entity = entity
    o.position = Vector(init.position or 0, 0)
    o.scale = Vector(init.scale or 1, 1)
    o.origin = Vector(init.origin or 0, 0)
    o.rotation = init.rotation or 0

    o.matrix = nil
    o.needsUpdate = true
    return o
end

function Transform:load(data)
    o.position = Vector(data.position)
    o.scale = Vector(data.scale)
    o.origin = Vector(data.origin)
    o.position = data.rotation
end

function Transform:getPosition()
    if self.entity.parent then
        return self.entity.parent:get("Transform"):getPosition() + self.position
    end
    return self.position
end

function Transform:getLocalPosition()
    return self.position
end

function Transform:setPosition(vec)
    self.position = Vector(vec.position.x or self.position.x, vec.position.y or self.position.y)
    self.needsUpdate = true
end

function Transform:setPosition(x, y)
    self.position = Vector(x or self.position.x, y or self.position.y)
    self.needsUpdate = true
end

function Transform:move(x, y)
    self.position = Vector(x, y) + self.position
    self.needsUpdate = true
end

function Transform:getOrigin()
    return self.origin
end

function Transform:setOrigin(vec)
    self.origin = Vector(vec.origin.x or self.origin.x, vec.origin.y or self.origin.y)
    self.needsUpdate = true
end

function Transform:setOrigin(x, y)
    self.origin = Vector(x or self.origin.x, y or self.origin.y)
    self.needsUpdate = true
end

function Transform:getScale()
    if self.entity.parent then
        return self.entity.parent:get("Transform"):getScale() * self.scale
    end
    return self.scale
end

function Transform:getLocalScale()
    return self.scale
end

function Transform:setScale(vec)
    self.scale = Vector(vec.scale.x or self.scale.x, vec.scale.y or self.scale.y)
    self.needsUpdate = true
end

function Transform:setScale(x, y)
    self.scale = Vector(x or self.scale.x, y or self.scale.y)
    self.needsUpdate = true
end

function Transform:scale(x, y)
    self.scale = Vector(x, y) + self.scale
    self.needsUpdate = true
end

function Transform:getRotation()
    if self.entity.parent then
        return self.entity.parent:get("Transform"):getRotation() + self.rotation
    end
    return self.rotation
end

function Transform:getLocalRotation()
    return self.rotation
end

function Transform:setRotation(rotate)
    self.rotation = rotate
    self.needsUpdate = true
end

function Transform:rotate(delta) 
    self.rotation = self.rotation + delta
    self.needsUpdate = true
end

function Transform:getMatrix()
    if self.entity.parent then
        return Matrix.new(self.entity.parent:get("Transform"):getMatrix()):combine(self:getLocalMatrix())
    end

    return self:getLocalMatrix()
end

function Transform:getLocalMatrix()
    if self.needsUpdate then
        local cosine = math.cos(self.rotation)
        local sine = math.sin(self.rotation)
        local sxc = self.scale.x * cosine
        local syc = self.scale.y * cosine
        local sxs = self.scale.x * sine
        local sys = self.scale.y * sine
        local tx = -self.origin.x * sxc - self.origin.y * sys + self.position.x
        local ty = self.origin.x * sxs - self.origin.y * syc + self.position.y

        self.matrix = Matrix.new(sxc, sys, tx, -sxs, syc, ty, 0.0, 0.0, 1.0)
        self.needsUpdate = false
    end

    return self.matrix
end

return Transform
