## Render red circle
```lua
local fill_color = color.new(255, 0, 0)

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
