ghost = {
    Graphics = {
        filename = "./images/ghostSheet.png",
        sequences = {
            idle = {0, 1},
            angry = {2, 3}
        },
        scale = 2,
        rate = 0.1,
        startSequence = "angry";
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
