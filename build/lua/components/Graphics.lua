local Graphics = Class(function(self, e, t)
    self.entity = e
    self.timer = Clock.new()
    self.sprite = LoadTexture(t["filename"])
    self.sequences = t["sequences"];
    self.scale = t["scale"];
    self.size = sprite.getTexture().getSize().x / scale;
    self.rate = t["rate"];
    self.sequence = t["currentSequence"];
    self.index = t["currentIndex"];
    self.isRunning = t["isRunning"];
end)

function Graphics:drawUpdate(e, win)
    sprite.setPosition(e.getPosition())
    sprite.setRotation(e.getRotation())
    sprite.setScale(e.getScale())
    win.draw(sprite)
end

function Graphics:fixedUpdate(e) 
    if (isRunning) then
        if (timer.getElapsedTime().asSeconds() > rate) then
            index = index + 1

            if (index >= sequences[sequence].size()) then
                index = 0
            end

            setTextureRect()

            timer.restart()
        end
    end
end

function Graphics:stop() 
    isRunning = false;
    index = 0;
    setTextureRect();
end

function Graphics:run(seq) 
    sequence = seq;
    isRunning = true;
end

function Graphics:setCurrent(seq, index) 
    self.sequence = seq;
    self.index = index;
    setTextureRect();
end

function setTextureRect() 
    self.sprite.textureRect = IntRect.new((sequences[sequence][index] % scale) * size,
                        (floor(sequences[sequence][index] / scale)) * size,
                        size, size)
end

return Graphics