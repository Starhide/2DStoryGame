return function (data, parent, name)
    ship = Entity.new({
		id		= name,
		prefab	= "Ship",
		parent 	= parent,
		tags 	= {}
	})
	
	ship:AddComponent("Transform", {
		position = data.Transform.position,
		rotation = data.Transform.rotation,
		scale	 = data.Transform.scale,
		origin 	 = {x = 15.5, y = 15.5}
	})
	
	ship:AddComponent("Physics", {
		mass = data.Physics.mass
	})
	
	ship:AddComponent("Graphics", {
		filename = "assets/Ship.png",
		sequences = {
			idle = {0, 1, 2, 3, 2, 1}
		},
		scale = 2,
		rate = 0.2,
		startSequence = "idle",
		startIndex = 1,
		isRunning = true
	})
	
	ship:AddComponent("Input", {
		isListening = true,
		keyHeld = {
			w = function (e, dt, keys)
				e.components.Physics:setVelocity(0, -50*dt)
			end,
			a = function (e, dt)
				e.components.Physics:setVelocity(-50*dt, 0)
			end,
			s = function (e, dt)
				e.components.Physics:setVelocity(0, 50*dt)
			end,
			d = function (e, dt)
				e.components.Physics:setVelocity(50*dt, 0)
			end,
		}
	})
	return ship
end
