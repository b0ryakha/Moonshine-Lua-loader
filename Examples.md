## Render red circle
```lua
local fill_color = Color:new(255, 0, 0)

while true do
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

while true do
    if mouse.is_pressed(button.Left) then
        sound:play()
    end
end
```

## Render text
```lua
local font = Font:new("arial.ttf", 20)
local color = Color:new(100, 100, 50)

while true do
    window.clear()
    render.text(500, 500, font, "Test text!", color)
    window.display()
end
```

## Render image
```lua
local sprite = Sprite:new("./img.png", 100, 100)
-- ./img.png = loader dir + img.png

while true do
    window.clear()
    render.sprite(sprite)
    window.display()
end
```
