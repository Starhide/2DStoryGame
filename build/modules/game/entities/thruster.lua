return function (data, parent)
    thruster = Entity.new({
		id=data.id,
		prefab="Thruster",
		parent = data.parent
		tags = {}
	})
	
	thruster.components.Transform = Transform.new(thruster, {
		position = data.Transform.position,
		rotation = data.Transform.rotation,
		scale	 = data.Transform.scale,
		origin 	 = {x = 7.5, y = 7}
	})
	
	thruster.components.Graphics = Graphics.new(thruster, {
		filename = "assets/thruster.png",
        sequences = {
            active = {0, 1},
            stop = {2}
		},
        scale = 2,
        rate = 0.1,
        startSequence = "stop",
        startIndex = 1,
        isRunning = true
	})
	
	thruster:AddComponent() = Input.new(thruster, {
		isListening = true,
		keyReleased = {},
		keyPressed = {}
	})
	
	thruster.components.Input:addKeyReleased(data.components.Input.key, function (e)
		print("Released!")
		e.components.Graphics:run("stop")
	end)
	
	thruster.components.Input:addKeyPressed(data.components.Input.key, function (e)
		print("Pressed!")
		e.components.Graphics:run("active")
	end)
	
	return thruster
end
