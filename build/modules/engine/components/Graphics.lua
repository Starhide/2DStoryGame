Graphics = {}
Graphics.__index = Graphics

function Graphics.new (inst, t)
   local o = {}
   setmetatable(o, Graphics)
   o.inst = inst
   o.timer = Clock.new()
   o.sprite = Sprite.new(t["filename"])
   o.sequences = t["sequences"] or {};
   o.scale = t["scale"] or 1;
   o.size = math.floor(o.sprite:getTextureWidth() / o.scale);
   o.rate = t["rate"] or 0;
   o.sequence = t["startSequence"] or "null";
   o.index = t["startIndex"] or 1;
   o.isRunning = t["isRunning"] or false;

   if o.isRunning then
    o:setTextureRect()
   end
   return o
end

function Graphics:draw(win)
	self.sprite:setPosition(self.inst.components.Transform:getPosition():unpack())
	self.sprite:setScale(self.inst.components.Transform:getScale():unpack())
	--print(self.inst.Transform:getOrigin().x)
	self.sprite:setOrigin(self.inst.components.Transform:getOrigin():unpack())
	self.sprite:setRotation(self.inst.components.Transform:getRotation())
    --self.sprite:draw(win, self.inst:get("Transform"):getMatrix())
    win:draw(self.sprite)
end

function Graphics:update(dt) 
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
