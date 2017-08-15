Event = {}
Event.__index = Event

function Event.__tostring(e)
    return e.type + ' ' + e
end

function Event.new(e)
    if not e.type then
        print("An event needs a type")
        return nil
    end
    setmetatable(e, Event)
    return e
end

return Event
