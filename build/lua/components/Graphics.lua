Graphics = {
    inst = nil,
    timer = nil,
    sprite = nil,
    sequences = {},
    scale = 1,
    size = 0,
    rate = 0.0,
    sequence = "null",
    index = 0,
    isRunning = false
}

function Graphics:new (inst, t)
   t = t or {}
   setmetatable(t, self)
   self.__index = self
   self.inst = inst
   self.timer = Clock.new()
   self.sprite = Sprite.new(t["filename"])
   self.sequences = t["sequences"] or {};
   self.scale = t["scale"] or 1;
   self.size = math.floor(self.sprite:getTextureWidth() / self.scale);
   self.rate = t["rate"] or 0;
   self.sequence = t["startSequence"] or "null";
   self.index = t["startIndex"] or 1;
   self.isRunning = t["isRunning"] or false;

   if self.isRunning then
    self:setTextureRect()
   end
   return t
end

function Graphics:drawUpdate(win)
    self.sprite:setPosition(self.inst:get("Transform"):getPositionXY())
    self.sprite:setScale(self.inst:get("Transform"):getScaleXY())
    self.sprite:setRotation(self.inst:get("Transform"):getRotation())
    self.sprite:draw(win)
end

function Graphics:frameUpdate() 
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

return Graphics
