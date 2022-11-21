# Script Loader, with Custom API.


## :mag_right: API :mag:
### :movie_camera: Render
#### ```new_sprite```
```lua
render.new_sprite(path: string, w: float, h: float): Sprite
```
| Name  | Type        | Description              |
| :---: | :---:       | :---:                    |
| path  | ```string```| Image location directory |
| w     | ```float``` | Weight of image          |
| h     | ```float``` | Height of image          |

Returns the Sprite struct or nil on failure.
#### ```text```
```lua
render.text(x: float, y: float, text: string, font_name: string, size: size_t, color: Color)
```
| Name      | Type        | Description        |
| :---:     | :---:       | :---:              |
| x         | ```float``` | X coordinate       |
| y         | ```float``` | Y coordinate       |
| text      | ```string```| Text for render    |
| font_name | ```string```| Font name for text |
| size      | ```size_t```| Size for text      |
| color     | ```Color``` | Color for text     |

Render text in the specified coordinates or return nil on failure.
#### ```measure_text```
```lua
render.measure_text(font_name: string, size: size_t, text: string): Measure
```
| Name      | Type         | Description                |
| :---:     | :---:        | :---:                      |
| font_name | ```string``` | Font name                  |
| size      | ```size_t``` | Size of text               |
| text      | ```string``` | Text that will be measured |

Returns the measured size of the text.


### :rainbow: Color
#### ```new```
```lua
color.new(r: int, g: int, b: int[, a: int]): Color
```
| Name  | Type      | Description                  |
| :---: | :---:     | :---:                        |
| r     | ```int``` | Red [0 - 255]                |
| g     | ```int``` | Green [0 - 255]              |
| b     | ```int``` | Blue [0 - 255]               |
| a     | ```int``` | Alpha [0 - 255], default 255 |

Returns the Color struct or nil on failure.

### :computer: Window
#### ```refresh```
```lua
window.refresh()
```

Refreshes the screen.
#### ```clear```
```lua
window.clear()
```

Clears the screen.
#### ```close```
```lua
window.close()
```

Closes the screen.

### :wrench: Keyboard
#### :star: [ENUMS](https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Mouse.php#a4fb128be433f9aafe66bc0c605daaa90)
```lua
button.Left
```


### :mouse2: Mouse
#### :star: [ENUMS](https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Keyboard.php)
```lua
key.W
```


### :video_game: Cursor


### :camera: View


### :musical_note: Sound


### :file_folder: File


### :heavy_division_sign: CMath
#### ```rand```
```lua
cmath.rand(min: int, max: int): int
```
| Name  | Type     | Description          |
| :---: | :---:    | :---:                |
| min   | ```int```| Minimum random value |
| max   | ```int```| Maximum random value |

Returns the random integer number [min, max] or nil on failure.
#### ```lerp```
```lua
cmath.lerp(start: float, end: float, time: float): float
```
| Name  | Type       | Description |
| :---: | :---:      | :---:       |
| start | ```float```| Start value |
| end   | ```float```| End value   |
| time  | ```float```| Step value  |

Returns the linear interpolation or nil on failure.

### :mag: GlobalVars


### :speech_balloon: Misc
#### ```print```
```lua
print(text: string, ...)
```
| Name  | Type     | Description |
| :---: | :---:    | :---:       |
| text  | ```any```| Text        |

Printing text on screen.
