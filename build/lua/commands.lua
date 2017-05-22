commands = {
    help = function (...) 
        print("Amazing!!!") 
    end,

    go = function (direction, ...)
        print("You can't go " .. direction)
    end

}


function call(command, ...)
    words = {}
    for word in string.gmatch(command, "%S+") do
        table.insert(words, word)
    end
    
    if commands[words[1]] then
        commands[words[1]](table.unpack(words, 2))
    end
end