local scene = {}

json = require "modules/engine/lib/json"

local f = io.open("modules/game/scene_ex.json")
local s = f:read("*a")
f:close()
local js = json.decode(s)

for v,l in pairs(js) do
	scene[v] = {}
	for n,e in pairs(l) do
		local block = assert(loadfile(e["typefile"]))()
		local blockInst = block(e["components"], e.parent, n)
		scene[v][n] = blockInst
	end
end

return scene