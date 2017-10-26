return function (data, parent, name)
    block = Entity.new({
		id		= name,
		prefab	= "Block",
		parent 	= parent,
		tags 	= {}
	})
	block:AddComponent("Transform", {
		position = data.Transform.position,
		rotation = data.Transform.rotation,
		scale	 = data.Transform.scale,
		origin 	 = {x = 15.5, y = 15.5}
		})
	
	block:AddComponent("Graphics", {
		filename = "assets/block.png"
	})
	return block
end
