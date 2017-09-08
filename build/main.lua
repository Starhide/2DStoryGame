function update(dt)
	for k,v in pairs(scene) do
		for a,x in pairs(v) do
			for i,c in pairs(x) do
				if type(c) == "table" and c.update then
					c:update(dt)
				end
			end
		end
	end
	x,y = scene.world.ship.Transform:getPosition():unpack()
	window:setViewCenter("world", x, y)
	window:setView("world")
	mx,my = GetMousePosition(window)
	vx,vy = window:mapPixelToCoords(mx,my)
	
	scene.world.ship.Transform:rotateTowards(vx, vy)
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
			x.Graphics:draw(window)
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

--init game objects
components = {}


entities = {gui = {}, world = {}}

AddRenderFunction(render)
AddUpdateFunction(update)
window:addView("world", 0, 0, 200, 200)
window:addView("gui", 0, 0, 200, 200)
window:setView("world")
require('modules/engine/components/Transform')
require('modules/engine/components/Physics')
require('modules/engine/components/Graphics')
require('modules/engine/components/Input')
require('modules/engine/Entity')

scene = assert(loadfile('modules/game/scene_ex.lua'))()