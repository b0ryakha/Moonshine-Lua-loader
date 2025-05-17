local fill_color = Color:new(0, 255, 0)
local is_fullscreen = false

while window.is_open() do -- main loop
    if keyboard.is_pressed(key.F11) then
        if is_fullscreen then
            window.set_style(style.Default)
        else
            window.set_style(style.Fullscreen)
        end

        is_fullscreen = not is_fullscreen
    end

    window.clear()
    render.rectangle(500, 200, 250, 260, fill_color)
    window.display()
end