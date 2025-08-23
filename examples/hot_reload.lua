local win_size = window.get_size()
local lock_press = false

local color = Color:new("#d78b02") -- try change & press F5
local size = 50

local state = hotreload.get_state()
local x = state.x or (win_size.x - size) / 2
local y = state.y or (win_size.y - size) / 2
local dx = state.dx or 5
local dy = state.dy or 5

while window.is_open() do -- main loop
    x = x + dx
    y = y + dy
    if (x + size) > win_size.x or x < 0 then dx = -dx end
    if (y + size) > win_size.y or y < 0 then dy = -dy end

    if keyboard.is_pressed(keys.F5) then
        if not lock_press then
            hotreload.set_state({ x = x, y = y, dx = dx, dy = dy })
            hotreload.reload()
            lock_press = true
        end
    else
        lock_press = false
    end

    window.clear()
    render.rectangle(x, y, size, size, color)
    window.display()
end