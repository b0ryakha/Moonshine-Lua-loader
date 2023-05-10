## Render red circle
```lua
local fill_color = Color:new(255, 0, 0)

while true do   -- main loop
    window.clear()
    render.circle(500, 500, 20, fill_color)
    window.display()
end
```

## Printing
```lua
print("hello", 145, nil, true)  -- output: hello   145   nil   true
window.display()
```

## Play sound on click
```lua
local sound = Sound:new("./bell.wav", 20)
-- ./bell.wav = loader dir + bell.wav

while true do   -- main loop
    if mouse.is_pressed(button.Left) then
        sound:play()
    end
end
```

## Render text
```lua
local font = Font:new("arial.ttf", 20)
local color = Color:new(100, 100, 50)

while true do   -- main loop
    window.clear()
    render.text(500, 500, font, "Test text!", color)
    window.display()
end
```

## Render image
```lua
local sprite = Sprite:new("./img.png", 100, 100)
-- ./img.png = loader dir + img.png

while true do   -- main loop
    window.clear()
    render.sprite(sprite)
    window.display()
end
```

## Set interval function
```lua
local cache = {}
local set_interval = function(func, ticks)
    if not cache[tostring(func)] then
        cache[tostring(func)] = { handle = func, cur_tick = 0, ticks = ticks }
        func()
    end

    for _, data in pairs(cache) do
        data.cur_tick = data.cur_tick + 1

        if data.cur_tick >= data.ticks then
            data.cur_tick = 0
            data.handle()
        end
    end
end

while true do
    window.clear()

    set_interval(function()
        print("first")
    end, 1000)
    
    set_interval(function()
        print("second")
    end, 500)

    window.display()
end
```

## Server
```lua
while true do
    network.listen()

    if network.client_ready() then
        network.send("word", 100, nil, true)
    end
end
```

## Client
```lua
-- server sends { "word", 100, nil, true }

while true do
    local data = network.receive()
    if not data then return end

    print(data[1], data[2], data[3], data[4])  -- output: "word", 100, nil, true
    window.display()
end
```
