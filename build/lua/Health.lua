local Health = Class(function(self, e)
    self.entity = e
    self.maxHealth = 100
    self.minHealth = 0
    self.currentHealth = self.maxHealth
end)

function Health:addHealth(delta)
    self.hp = self.hp + delta
    if self.hp > self.maxHP then
        self.hp = self.maxHP
    elseif self.hp < 0 then
        self.hp = 0
    end
end

function Health:setHealth(new_hp)
    self.hp = new_hp
end

function Health:getHealth()
    return self.hp
end

function Health:setMaxHealth(new_hp)
    self.maxHp = new_hp
end

function Health:getMaxHealth()
    return self.maxHp
end

return Health