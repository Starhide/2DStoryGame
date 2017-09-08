require 'modules/engine/lib/Keys'

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
        AddEventListener("KeyReleased", function(...) o:KeyReleased(...) end)
	end
	
    return o
end

function Input:addKeyReleased(key, funct)
	self.keyReleased[stringToKey(key)] = funct
	self.keys[stringToKey(key)] = false
end

function Input:addKeyPressed(key, funct)
	self.keyPressed[stringToKey(key)] = funct
	self.keys[stringToKey(key)] = false
end

function Input:addKeyheld(key, funct)
	self.keyHeld[stringToKey(key)] = funct
	self.keys[stringToKey(key)] = false
end

function Input:KeyReleased(event)
    for k, f in pairs(self.keyReleased) do
        if event.code == k then
            f(self.entity)
		end
	end
end

function Input:update(dt)
    if self.isListening then
        for key, funct in pairs(self.keyHeld) do
            if IsKeyPressed(key) and self.keys[key] then
                funct(self.entity, dt)
			end
		end
		
        for key, funct in pairs(self.keyPressed) do
            if IsKeyPressed(key) and not self.keys[key] then
                funct(self.entity)
			end
		end
		
        for key, v in pairs(self.keys) do
            if IsKeyPressed(key) and not v then
                self.keys[key] = true
			elseif not IsKeyPressed(key) and v then
                self.keys[key] = false
			end
		end
	end
end

return Input
