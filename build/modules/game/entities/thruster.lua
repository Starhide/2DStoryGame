return function (data, parent, n)
    thruster = Entity.new({
		id		= n,
		prefab	= "Thruster",
		parent 	= parent,
		tags 	= {}
	})
	
	thruster:AddComponent("Transform", {
		position = data.Transform.position,
		rotation = data.Transform.rotation,
		scale	 = data.Transform.scale,
		origin 	 = {x = 7.5, y = 7}
	})
	
	thruster:AddComponent("Graphics", {
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
	
	thruster:AddComponent("Input", {
		isListening = true,
		keyReleased = {},
		keyPressed = {}
	})
	
	thruster.components.Input:addKeyReleased(data.Input.key, function (e)
		print("Released!")
		e.components.Graphics:run("stop")
	end)
	
	thruster.components.Input:addKeyPressed(data.Input.key, function (e)
		print("Pressed!")
		e.components.Graphics:run("active")
	end)
	
	return thruster
end
