return function (data)
    block = {}
	block.Transform = Transform.new(block, {
		position = data.Transform.position,
		rotation = data.Transform.rotation,
		scale	 = data.Transform.scale,
		origin 	 = {x = 15.5, y = 15.5}
	})
	
	block.Graphics = Graphics.new(block, {
		filename = "assets/block.png"
	})
	return block
end
