return {
    Transform = {
			origin = {x = 7.5, y = 7}
    },
    Input = {
        isListening = true
    },
    Graphics = {
        filename = "./images/thruster.png",
        sequences = {
            active = {0, 1},
            stop = {2}
        },
        scale = 2,
        rate = 0.1,
        startSequence = "stop",
        startIndex = 1,
        isRunning = true
    }
}