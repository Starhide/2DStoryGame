return {
    Transform = {

    },
    Graphics = {
        filename = "./images/ghostSheet.png",
        sequences = {
            idle = {0, 1},
            angry = {2, 3}
        },
        scale = 2,
        rate = 0.1,
        startSequence = "idle",
        startIndex = 1,
        isRunning = true
    },
    Input = {
        isListening = true,
        keyHeld = {
            w = function (e, dt, keys)
                e:get("Transform"):move(0, -50*dt)
            end,
            a = function (e, dt)
                e:get("Transform"):move(-50*dt, 0)
            end,
            s = function (e, dt)
                e:get("Transform"):move(0, 50*dt)
            end,
            d = function (e, dt)
                e:get("Transform"):move(50*dt, 0)
            end,
        }
    }
}
