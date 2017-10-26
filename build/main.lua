function update(dt)
	for k,v in pairs(scene) do
		for a,x in pairs(v) do
			for i,c in pairs(x.components) do
				if c.update then
					c:update(dt)
				end
			end
		end
	end
	x,y = scene.world.ship.components.Transform:getPosition():unpack()
	window:setViewCenter("world", x, y)
	window:setView("world")
	mx,my = GetMousePosition(window)
	vx,vy = window:mapPixelToCoords(mx,my)
	
	scene.world.ship.components.Transform:rotateTowards(vx, vy)
	--for k,v in pairs(entities["world"]) do
	--	v.Graphics.draw(window)
	--end
	--for k,v in pairs(entities["gui"]) do
	--	v.Graphics.draw(window)
	--end
end

function render()
	for k,v in pairs(scene) do
		for a,x in pairs(v) do
			x.components.Graphics:draw(window)
		end
	end
	--shipInst.Graphics:draw(window)
	--block.Graphics:draw(window)
	--window.setView("gui")
	--for k,v in pairs(entities["gui"]) do
	--	v.Graphics.draw(window)
	--end
	--
	--window.setView("world")
	--for k,v in pairs(entities["world"]) do
	--	v.Graphics.draw(window)
	--end
end

function loadComponent(file)
	
end

--init game objects
Main = {
	Components = {},
	Entities = {gui = {}, world = {}}
}

AddRenderFunction(render)
AddUpdateFunction(update)
window:addView("world", 0, 0, 200, 200)
window:addView("gui", 0, 0, 200, 200)
window:setView("world")

--Load Components

Main.Components.Transform = require('modules/engine/components/Transform')
Main.Components.Physics = require('modules/engine/components/Physics')
Main.Components.Graphics = require('modules/engine/components/Graphics')
Main.Components.Input = require('modules/engine/components/Input')
require('modules/engine/Entity')

scene = assert(loadfile('modules/game/scene_ex.lua'))()