local Vector = require 'lua/lib/vector'

Transform = {
    position = {x = 0, y = 0},
    origin = {x = 0, y = 0},
    scale = {x = 1, y = 1},
    rotation = 0
}

function Transform:new (inst, t)
   t = t or {}
   setmetatable(t, self)
   self.__index = self
   self.position =  {x = t.position.x or 0, y = t.position.y or 0}
   self.scale = {x = t.scale.x or 1, y = t.scale.y or 1}
   self.origin = {x = t.origin.x or 1, y = t.origin.y or 1}
   self.rotation = t.rotation or 0
   return t
end

function Transform:getPosition()
    return self.position
end

function Transform:getPositionXY()
    return self.position.x, self.position.y
end

function Transform:setPosition(vec)
    self.position.x = vec.position.x or self.position.x
    self.position.y = vec.position.y or self.position.y
end

function Transform:setPosition(x, y) 
    self.position.x = x or self.position.x
    self.position.y = y or self.position.y
end

function Transform:move(x, y)
    self.position.x = x + self.position.x
    self.position.y = y + self.position.y
end

function Transform:getOrigin()
    return self.origin
end

function Transform:getOriginXY()
    return self.origin.x, self.origin.y
end

function Transform:setOrigin(vec)
    self.origin.x = vec.origin.x or self.origin.x
    self.origin.y = vec.origin.y or self.origin.y
end

function Transform:setOrigin(x, y) 
    self.origin.x = x or self.origin.x
    self.origin.y = y or self.origin.y
end

function Transform:getScale()
    return self.scale
end

function Transform:getScaleXY()
    return self.scale.x, self.scale.y
end

function Transform:setScale(vec)
    self.scale.x = t.scale.x or self.scale.x
    self.scale.y = t.scale.y or self.scale.y
end

function Transform:setScale(x, y)
    self.scale.x = x or self.scale.x
    self.scale.y = y or self.scale.y
end

function Transform:scale(x, y)
    self.scale.x = x + self.scale.x
    self.scale.y = y + self.scale.y
end

function Transform:getRotation()
    return self.rotation
end

function Transform:setRotation(rotate)
    self.rotation = rotate
end

function Transform:rotate(delta)
    self.rotation = self.rotation + delta
end

return Transform
