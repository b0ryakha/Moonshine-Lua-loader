## Render red circle
```lua
local fill_color = Color:new(255, 0, 0)

while true do -- main loop
    window.clear()
    render.circle(500, 500, 20, fill_color)
    window.display()
end
```

## Play sound on click
```lua
local sound = Sound:new("./bell.wav", 20)
-- ./bell.wav = loader dir + bell.wav

while true do -- main loop
    if mouse.is_pressed(button.Left) then
        sound:play()
    end
end
```

## Render text
```lua
local font = Font:new("Arial.TTF", 20)
local color = Color:new(100, 100, 50)

while true do -- main loop
    window.clear()
    render.text(500, 500, font, "Test text!", color)
    window.display()
end
```

## Render image
```lua
local sprite = Sprite:new("./img.png", 100, 100)
-- ./img.png = loader dir + img.png

while true do -- main loop
    window.clear()
    render.sprite(sprite)
    window.display()
end
```

## Server
```lua
network.bind(54000, 's')

while true do
    network.send({ "word", 100, nil, true })
    
    -- client sends { "hi!" }
    local data = network.receive()
    if not data then return end

    print(data[1]) -- output: "hi!"
end
```

## Client
```lua
local server_ip = network.get_local_address() -- local ip
local server_port = 54000

local unique_port = 53002
network.bind(unique_port, 'c')

while true do
    -- server sends { "word", 100, nil, true }
    local data = network.receive()
    if not data then return end
    
    network.send(server_ip, server_port, { "hi!" })

    print(data[1], data[2], data[3], data[4]) -- output: "word", 100, nil, true
end
```
