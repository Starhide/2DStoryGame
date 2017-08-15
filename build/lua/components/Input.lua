require 'lua/lib/Keys'

Input = {}
Input.__index = Input

function Input.new (entity, init)
    local o = {
        keyHeld = {},
        keyPressed = {},
        keyReleased = {},
        keys = {}
    }
    setmetatable(o, Input)
    o.entity = entity
    o.isListening = init.isListening

    if init.keyHeld then
        for k,v in pairs(init.keyHeld) do
            o.keyHeld[stringToKey(k)] = v
            o.keys[stringToKey(k)] = false
        end
    end

    if init.keyPressed then
        for k,v in pairs(init.keyPressed) do
            o.keyPressed[stringToKey(k)] = v
            o.keys[stringToKey(k)] = false
        end
    end

    if init.keyReleased then
        for k,v in pairs(init.keyReleased) do
            o.keyReleased[stringToKey(k)] = v
            o.keys[stringToKey(k)] = false
        end
    end

    return o
end

function Input:update(dt)
    if self.isListening then
        for key, funct in pairs(self.keyHeld) do
            if isKeyPressed(key) and self.keys[key] then
                funct(self.entity, dt)
            end
        end

        for key, funct in pairs(self.keyPressed) do
            if isKeyPressed(key) and not self.keys[key] then
                funct(self.entity)
            end
        end

        for key, funct in pairs(self.keyReleased) do
            if not isKeyPressed(key) and self.keys[key] then
                funct(self.entity)
            end
        end

        for key, v in pairs(self.keys) do
            if isKeyPressed(key) and not v then
                self.keys[key] = true
            elseif not isKeyPressed(key) and v then
                self.keys[key] = false
            end
        end
    end
end

return Input
