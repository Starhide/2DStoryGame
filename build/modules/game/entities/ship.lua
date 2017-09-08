return function (data)
    ship = {}
	ship.Transform = Transform.new(ship, {
		position = data.Transform.position,
		rotation = data.Transform.rotation,
		scale	 = data.Transform.scale,
		origin 	 = {x = 15.5, y = 15.5}
	})
	
	ship.Physics = Physics.new(ship, {
		mass = data.Physics.mass
	})
	
	ship.Graphics = Graphics.new(ship, {
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
	
	ship.Input = Input.new(ship, {
		isListening = true,
		keyHeld = {
			w = function (e, dt, keys)
				e.Physics:setVelocity(0, -50*dt)
			end,
			a = function (e, dt)
				e.Physics:setVelocity(-50*dt, 0)
			end,
			s = function (e, dt)
				e.Physics:setVelocity(0, 50*dt)
			end,
			d = function (e, dt)
				e.Physics:setVelocity(50*dt, 0)
			end,
		}
	})
	return ship
end
