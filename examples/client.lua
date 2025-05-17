local server_ip = network.get_local_address() -- local ip
local server_port = 54000

local unique_port = 53002
network.bind(unique_port, 'c')

while window.is_open() do
    -- server sends { "word", 100, nil, true }
    local data = network.receive()
    if not data then return end
    
    network.send(server_ip, server_port, { "hi!" })

    print(data[1], data[2], data[3], data[4]) -- output: "word", 100, nil, true
end