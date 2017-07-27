entities = {
{
	id = "Player1",
	parent = nil,
	typename = "ghost",
	typefile = "entities/ghost.lua",
	components = {
		Transform = {
			position = {x = 0, y = 0},
    		rotation = 0,
    		scale = {x = 1, y = 1}
		}
	}
},
{
	id = "Player2",
	parent = "Player1",
	typename = "hat",
	typefile = "entities/hat.lua",
	components = {
		Transform = {
			position = {x = 0, y = -15},
    		rotation = 0,
    		scale = {x = 1, y = 1}
		}
	}
}
}
