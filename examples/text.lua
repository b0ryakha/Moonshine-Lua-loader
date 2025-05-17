local font = Font:new("Arial.TTF", 20)
local color = Color:new(100, 100, 50)

while window.is_open() do -- main loop
    window.clear()
    render.text(500, 500, font, "Test text!", color)
    window.display()
end