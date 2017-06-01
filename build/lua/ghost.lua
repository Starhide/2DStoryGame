ghost = {
    SpriteComponent = {
        filename = "./images/Ghost.png"
    },
    InputComponent = {
        key_forward = function()
            print("Hi")
        end,
        key_exit = function()
            print("Never!!")
        end
    }
}