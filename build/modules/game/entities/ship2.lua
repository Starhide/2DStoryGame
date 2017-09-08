local ship = {}

ship.Transform = Transform.new()

ship.Physics = Physics.new()

ship.Graphics = Graphics.new("./images/Ship.png", 2, 0.2, "idle", 1, true,
    {
        idle = {0, 1, 2, 3, 2, 1}
    }
)

ship.Input = Input.new()
ship.Input:addKeyHeld("w", 
    function (e, dt)
        e:get("Physics"):setVelocity(0, -50*dt)
    end)

return ship
