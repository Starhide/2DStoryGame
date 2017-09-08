entities = {
{
	id = "Player1",
	parent = nil,
	typename = "ship",
	typefile = "lua/entities/ship.lua",
	components = {
		Transform = {
			position = {x = 0, y = 0},
    		rotation = 0,
    		scale = {x = 1, y = 1},
			origin = {x = 15.5, y = 15.5}
		}
	}
},
{
	id = "Down1",
	parent = "Player1",
	typename = "thruster",
	typefile = "lua/entities/thruster.lua",
	components = {
		Transform = {
			position = {x = -5, y = -12.5}
		},
		Input = {
			keyReleased = {
				s = function (e)
					e:get("Graphics"):run("stop")
				end
			},
			keyPressed = {
				s = function (e)
					e:get("Graphics"):run("active")
				end
			}
		}
	}
},
{
	id = "Down2",
	parent = "Player1",
	typename = "thruster",
	typefile = "lua/entities/thruster.lua",
	components = {
		Transform = {
			position = {x = 5, y = -12.5}
		},
		Input = {
			keyReleased = {
				s = function (e)
					e:get("Graphics"):run("stop")
				end
			},
			keyPressed = {
				s = function (e)
					e:get("Graphics"):run("active")
				end
			}
		}
	}
},
{
	id = "Left",
	parent = "Player1",
	typename = "thruster",
	typefile = "lua/entities/thruster.lua",
	components = {
		Transform = {
			position = {x = 13.5, y = 0},
			rotation = 90,
		},
		Input = {
			keyReleased = {
				a = function (e)
					e:get("Graphics"):run("stop")
				end
			},
			keyPressed = {
				a = function (e)
					e:get("Graphics"):run("active")
				end
			}
		}
	}
},
{
	id = "Right",
	parent = "Player1",
	typename = "thruster",
	typefile = "lua/entities/thruster.lua",
	components = {
		Transform = {
			position = {x = -12.5, y = 1},
			rotation = -90
		},
		Input = {
			keyReleased = {
				d = function (e)
					e:get("Graphics"):run("stop")
				end
			},
			keyPressed = {
				d = function (e)
					e:get("Graphics"):run("active")
				end
			}
		}
	}
},
{
	id = "Up",
	parent = "Player1",
	typename = "thruster",
	typefile = "lua/entities/thruster.lua",
	components = {
		Transform = {
			position = {x = 1, y = 13.5},
			rotation = 180
		},
		Input = {
			keyReleased = {
				w = function (e)
					e:get("Graphics"):run("stop")
				end
			},
			keyPressed = {
				w = function (e)
					e:get("Graphics"):run("active")
				end
			}
		}
	}
}
}
