keys = {
    unknown = -1,
    a = 0,
    b = 1, 
    c = 2, 
    d = 3, 
    e = 4, 
    f = 5, 
    g = 6, 
    h = 7, 
    i = 8, 
    j = 9, 
    k = 10,
    l = 11,
    m = 12,
    n = 13,
    o = 14,
    p = 15,
    q = 16,
    r = 17,
    s = 18,
    t = 19,
    u = 20,
    v = 21,
    w = 22,
    x = 23,
    y = 24,
    z = 25,
    num0 = 26,        
    num1 = 27,        
    num2 = 28,        
    num3 = 29,        
    num4 = 30,        
    num5 = 31,        
    num6 = 32,        
    num7 = 33,        
    num8 = 34,        
    num9 = 35,        
    escape      = 36,      
    lcontrol    = 37,    
    lshift      = 38,      
    lalt        = 39,        
    lsystem     = 40,
    rcontrol    = 41,
    rshift      = 42,
    ralt        = 43,
    rsystem     = 44,
    menu        = 45,
    lbracket    = 46,
    rbracket    = 47,
    semicolon   = 48,
    comma       = 49,
    period      = 50,
    quote       = 51,
    slash       = 52,
    backslash   = 53,
    tilde       = 54,
    equal       = 55,
    dash        = 56,
    space       = 57,
    enter       = 58,
    backspace   = 59,
    tab         = 60,
    pageup      = 61,
    pagedown    = 62,
    ["end"]     = 63,
    home        = 64,
    insert      = 65,
    delete      = 66,
    add         = 67,
    subtract    = 68,
    multiply    = 69,
    divide      = 70,
    left        = 71,
    right       = 72,
    up          = 73,
    down        = 74,
    numpad0     = 75,
    numpad1     = 76,
    numpad2     = 77,
    numpad3     = 78,
    numpad4     = 79,
    numpad5     = 80,
    numpad6     = 81,
    numpad7     = 82,
    numpad8     = 83,
    numpad9     = 84,
    f1          = 85,
    f2          = 86,
    f3          = 87,
    f4          = 88,
    f5          = 89,
    f6          = 90,
    f7          = 91,
    f8          = 92,
    f9          = 93,
    f10         = 94,
    f11         = 95,
    f12         = 96,
    f13         = 97,
    f14         = 98,
    f15         = 99,
    pause       = 100
}

function stringToKey(word)
    word = word:lower()
    return keys[word]
end