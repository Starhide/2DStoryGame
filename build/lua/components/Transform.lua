local Vector = require 'lua/lib/Vector'

Transform = {}
Transform.__index = Transform

function Transform.new (entity, init)
    local o = {}
    setmetatable(o, Transform)
    o.entity = entity
    o.position = Vector.fromLabeledTable(init.position or {x = 0, y = 0})
    o.scale = Vector.fromLabeledTable(init.scale or {x = 1, y = 1})
    o.origin = Vector.fromLabeledTable(init.origin or {x = 0, y = 0})
    o.rotation = 0
    return o
end

function Transform:load(data)
    o.position = Vector.fromLabeledTable(data.position)
    o.scale = Vector.fromLabeledTable(data.scale)
    o.origin = Vector.fromLabeledTable(data.origin)
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
    self.position = Vector(vec.position.x or self.position.x, 
                            vec.position.y or self.position.y)
end

function Transform:setPosition(x, y) 
    self.position = Vector(x or self.position.x, 
                            y or self.position.y)
end

function Transform:move(x, y)
    self.position = Vector(x, y) + self.position
end

function Transform:getOrigin()
    return self.origin
end

function Transform:setOrigin(vec)
    self.origin = Vector(vec.origin.x or self.origin.x, 
                            vec.origin.y or self.origin.y)
end

function Transform:setOrigin(x, y) 
    self.origin = Vector(x or self.origin.x, 
                            y or self.origin.y)
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
    self.scale = Vector(vec.scale.x or self.scale.x, 
                            vec.scale.y or self.scale.y)
end

function Transform:setScale(x, y)
    self.scale = Vector(x or self.scale.x, 
                            y or self.scale.y)
end

function Transform:scale(x, y)
    self.scale = Vector(x, y) + self.scale
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
end

function Transform:rotate(delta)
    self.rotation = self.rotation + delta
end

return Transform
