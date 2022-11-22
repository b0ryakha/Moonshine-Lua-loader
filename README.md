# Script Loader, with Custom API.


## :mag_right: API :mag:
## :movie_camera: Render
#### ```new_sprite```
```lua
render.new_sprite(path: string, w: float, h: float[, t_x: float, t_y: float, t_w: float, t_h: float]): Sprite
```
| Name  | Type        | Description                                     |
| :---: | :---:       | :---:                                           |
| path  | ```string```| Image location directory                        |
| w     | ```float``` | Width of image                                  |
| h     | ```float``` | Height of image                                 |
| t_x   | ```float``` | X coordinate of areas in the image, default = 0 |
| t_y   | ```float``` | Y coordinate of areas in the image, default = 0 |
| t_w   | ```float``` | Width of areas in the image, default = w        |
| t_h   | ```float``` | Height of areas in the image, default = h       |

Returns the Sprite struct or nil on failure.
#### ```load_font```
```lua
render.load_font(font_name: string, size: size_t): Font
```
| Name      | Type         | Description  |
| :---:     | :---:        | :---:        |
| font_name | ```string``` | Name of font |
| size      | ```size_t``` | Size of font |

Returns the Font struct or nil on failure.
#### ```text```
```lua
render.text(x: float, y: float, font: Font, text: string, color: Color)
```
| Name      | Type        | Description        |
| :---:     | :---:       | :---:              |
| x         | ```float``` | X coordinate       |
| y         | ```float``` | Y coordinate       |
| font      | ```Font```  | Font for text      |
| text      | ```string```| Text for render    |
| color     | ```Color``` | Color for text     |

Render text in the specified coordinates.
#### ```measure_text```
```lua
render.measure_text(font: Font, text: string): Measure
```
| Name      | Type         | Description                |
| :---:     | :---:        | :---:                      |
| font      | ```Font```   | Font for text              |
| text      | ```string``` | Text that will be measured |

Returns the measured size of the text.
#### ```sprite```
```lua
render.sprite(sprite: Sprite, x: float, y: float[, color: Color])
```
| Name      | Type        | Description        |
| :---:     | :---:       | :---:              |
| sprite    | ```Sprite```| Sprite for render  |
| x         | ```float``` | X coordinate       |
| y         | ```float``` | Y coordinate       |
| color     | ```Color``` | Color for sprite   |

Render sprite in the specified coordinates.


## :rainbow: Color
#### ```new```
```lua
color.new(r: int, g: int, b: int[, a: int]): Color
color.new(hex: string): Color
```
| Name  | Type         | Description                  |
| :---: | :---:        | :---:                        |
| r     | ```int```    | Red [0 - 255]                |
| g     | ```int```    | Green [0 - 255]              |
| b     | ```int```    | Blue [0 - 255]               |
| a     | ```int```    | Alpha [0 - 255], default 255 |

| Name  | Type         | Description                  |
| :---: | :---:        | :---:                        |
| hex   | ```string``` | Hex string                   |

Returns the Color struct or nil on failure.
#### ```unpack```
```lua
color.unpack(color: Color): int, int, int, int
```
| Name  | Type        | Description         |
| :---: | :---:       | :---:               |
| color | ```Color``` | Color for unpacking |

Returns the integer r, g, b, a values of color or nil on failure.
#### ```to_hex```
```lua
color.to_hex(color: Color): string
```
| Name  | Type        | Description              |
| :---: | :---:       | :---:                    |
| color | ```Color``` | Color for casting to hex |

Returns the hex str or nil on failure.


## :computer: Window
#### ```display```
```lua
window.display()
```

Display on screen what has been rendered to the window so far.
#### ```clear```
```lua
window.clear([color: Color])
```
| Name  | Type        | Description                               |
| :---: | :---:       | :---:                                     |
| color | ```Color``` | Color for screen filling, default = Black |

Clears the screen with a color.
#### ```close```
```lua
window.close()
```

Closes the window and destroy all the attached resources.

## :wrench: Keyboard
#### :star: [ENUMS](https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Mouse.php#a4fb128be433f9aafe66bc0c605daaa90)
```lua
button.Left
```


## :mouse2: Mouse
#### :star: [ENUMS](https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Keyboard.php)
```lua
key.W
```


## :video_game: Cursor


## :camera: View


## :musical_note: Sound


## :file_folder: File


## :heavy_division_sign: CMath
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
#### ```clamp```
```lua
cmath.clamp(number: float, lower: float, upper: float): float
```
| Name   | Type       | Description    |
| :---:  | :---:      | :---:          |
| number | ```float```| Value to clamp |
| lower  | ```float```| Lower bound    |
| upper  | ```float```| Upper bound    |

Returns the clumped value or nil on failure.

## :mag: GlobalVars


## :speech_balloon: Misc
#### ```print```
```lua
print(text: string, ...)
```
| Name  | Type     | Description |
| :---: | :---:    | :---:       |
| text  | ```any```| Text        |

Printing text on screen.
