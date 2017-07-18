-- Meta class
Graphics = {
    timer = nil,
    sprite = nil,
    sequences = {},
    scale = 1,
    size = 0,
    rate = 0.0,
    sequence = "null",
    index = 0,
    isRunning = false,
}

-- Base class method new

function Graphics:new (t)
   t = t or {}
   setmetatable(t, self)
   self.__index = self
   self.timer = Clock.new()
   self.sprite = Sprite.new(t["filename"])
   self.sequences = t["sequences"];
   self.scale = t["scale"];
   self.size = math.floor(self.sprite:getTextureWidth() / self.scale);
   self.rate = t["rate"];
   self.sequence = t["startSequence"];
   self.index = t["startIndex"];
   self.isRunning = t["isRunning"];
   self:setTextureRect()
   return t
end

-- Base class method printArea

function Graphics:drawUpdate(win)
    --sprite.setPosition(e.getPosition())
    --sprite.setRotation(e.getRotation())
    --sprite.setScale(e.getScale())
    Draw(self.sprite, win)
end

function Graphics:frameUpdate(e) 
    if (self.isRunning) then
        if (self.timer:getElapsedTime():asSeconds() > self.rate) then
            self.index = self.index + 1

            if (self.index > #self.sequences[self.sequence]) then
                self.index = 1
            end

            self:setTextureRect()

            self.timer:restart()
        end
    end
end

function Graphics:stop() 
    self.isRunning = false;
    self.index = 0;
    self:setTextureRect();
end

function Graphics:run(seq) 
    self.sequence = seq;
    self.isRunning = true;
end

function Graphics:setCurrent(seq, index) 
    self.sequence = seq;
    self.index = index;
    self:setTextureRect();
end

function Graphics:setTextureRect() 
    self.sprite:setTextureRect(math.fmod(self.sequences[self.sequence][self.index], self.scale) * self.size, (math.floor(self.sequences[self.sequence][self.index] / self.scale)) * self.size, self.size, self.size)
end

-- Creating an object
myshape = Graphics:new({
        filename = "./images/ghostSheet.png",
        scale = 2,
        rate = 0.25,
        startSequence = "idle",
        startIndex = 1,
        isRunning = true,
        sequences = {
            idle = {0, 1},
            angry = {2, 3}
        }
    })
