local sound = Sound:new("./bell.wav", 20)
-- ./bell.wav = loader dir + bell.wav

while window.is_open() do -- main loop
    if mouse.is_pressed(buttons.Left) then
        sound:play()
    end
end