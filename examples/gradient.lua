local top_left = Color:new("#d78b02")
local top_right = Color:new("#d64957")
local bottom_left = Color:new("#8d3e83")
local bottom_right = Color:new("#0e3f77")

while window.is_open() do -- main loop
    local win_size = window.get_size()

    window.clear()
    render.gradient(0, 0, win_size.x, win_size.y, top_left, top_right, bottom_left, bottom_right)
    window.display()
end