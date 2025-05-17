local fill_color = Color:new(255, 0, 0)

while window.is_open() do -- main loop
    window.clear()
    render.circle(500, 500, 20, fill_color)
    window.display()
end