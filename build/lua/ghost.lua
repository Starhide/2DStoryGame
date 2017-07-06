ghost = {
    Graphics = {
        filename = "./images/ghostSheet.png",
        sequences = {
            idle = {0, 0, 1},
            angry = {1, 0, 1}
        },
        size = 32,
        rate = 0.05,
        startSequence = "idle";
        startIndex = 0;
        isRunning = true;
    },
    Input = {
        key_forward = function()
            print("Hi")
        end,
        key_exit = function()
            print("Never!!")
        end
    }
}
