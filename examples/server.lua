network.bind(54000, 's')

while window.is_open() do
    network.send({ "word", 100, nil, true })
    
    -- client sends { "hi!" }
    local data = network.receive()
    if not data then return end

    print(data[1]) -- output: "hi!"
end