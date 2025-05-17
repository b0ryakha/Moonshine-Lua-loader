local sprite = Sprite:new("./img.png", 100, 100)
-- ./img.png = loader dir + img.png

while window.is_open() do -- main loop
    window.clear()
    render.sprite(sprite)
    window.display()
end