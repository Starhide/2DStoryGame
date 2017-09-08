return function (inst, data)
    ship = {
		"Transform" = Transform.new(inst, {
			position = data.Transform.position,
			rotation = data.Transform.rotation,
			scale	 = data.Transform.scale,
			origin 	 = {15.5, 15.5}
		}),
		"Physics" = Physics.new(inst, {
			mass = data.Physics.mass
		}),
		"Graphics" = Graphics.new(inst, {
			filename = "./images/Ship.png",
			sequences = {
				idle = {0, 1, 2, 3, 2, 1}
			},
			scale = 2,
			rate = 0.2,
			startSequence = "idle",
			startIndex = 1,
			isRunning = true
		}),
		"Input" = Input.new(inst, {
			isListening = true,
			keyHeld = {
				w = function (e, dt, keys)
					e:get("Physics"):setVelocity(0, -50*dt)
				end,
				a = function (e, dt)
					e:get("Physics"):setVelocity(-50*dt, 0)
				end,
				s = function (e, dt)
					e:get("Physics"):setVelocity(0, 50*dt)
				end,
				d = function (e, dt)
					e:get("Physics"):setVelocity(50*dt, 0)
				end,
			}
		})
	}
end
