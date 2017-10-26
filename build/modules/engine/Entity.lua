Entity = {}
Entity.__index = Entity

function Entity.new(init)
    local e = {}
    setmetatable(e, Entity)
    e.id = init.id
	e.prefab = init.prefab
	e.tags = init.tags
	e.parentID = init.parent
	e.components = {}
    return e
end

function Entity:AddComponent(name, ...)
	if self.components[name] then
		print("Component " .. name .. " already exists in " .. self.id)
		return
	end
	
	self.components[name] = Main.Components[name].new(self, ...)
end

function Entity:AddTag(tag)
	for i, t in ipairs(tags) do
		if t == tag then
			print(self.id .. " already has tag " .. tag)
			return
		end
	end
	
	tags[#tags+1] = tag
end

return Entity