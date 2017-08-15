EventHandler = {
    eventListeners = {}

}

function EventHandler.pushEvent(event)
    for funct in EventHandler.eventListeners[event.type] do
        funct(event)
    end
end

function EventHandler.addEventListener(type, funct)
    if not EventHandler.eventListeners[type] then
        EventHandler.eventListeners[type] = {}
    end
    table.insert(EventHandler.eventListeners[type], funct)
end