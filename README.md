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


### :mouse2: Mouse


### :video_game: Cursor


### :camera: View


### :musical_note: Sound


### :file_folder: File


### :heavy_division_sign: CMath


### :mag: GlobalVars


### :speech_balloon: Misc
#### ```print```
```lua
print(text: string)
```
| Name  | Type        | Description |
| :---: | :---:       | :---:       |
| text  | ```string```| Text        |

Printing text on screen.
