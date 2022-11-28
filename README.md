# Script Loader, with Custom API.


## :mag_right: API :mag:
### :dash: Navigation:
<details><summary>:movie_camera: Render</summary>

  - [load_sprite()](#render.load_sprite)
  - [load_font()](#render.load_font)
  - [text()](#render.text)
  - [measure_text()](#render.measure_text)
  - [sprite()](#render.sprite)
  </details>

<details><summary>:rainbow: Color</summary>

  - [new()](#color.new)
  - [unpack()](#color.unpack)
  - [to_hex()](#color.to_hex)
  </details>
  
<details><summary>:computer: Window</summary>

  - [display()](#window.display)
  - [clear()](#window.clear)
  - [close()](#window.close)
  - [get_size()](#window.get_size)
  - [set_size()](#window.set_size)
  - [get_pos()](#window.get_pos)
  - [set_pos()](#window.set_pos)
  - [set_title()](#window.set_title)
  - [set_vsync()](#window.set_vsync)
  - [set_frame_limit()](#window.set_frame_limit)
  - [sleep()](#window.sleep)
  - [await()](#window.await)
  - [set_icon()](#window.set_icon)
  </details>
  
<details><summary>:wrench: Keyboard</summary>

  - [get_pressed()](#keyboard.get_pressed)
  - [is_pressed()](#keyboard.is_pressed)
  </details>
  
<details><summary>:mouse: Mouse</summary>

  </details>
  
<details><summary>:video_game: Cursor</summary>

  </details>
  
<details><summary>:camera: View</summary>

  </details>
  
<details><summary>:musical_note: Sound</summary>

  </details>
  
<details><summary>:file_folder: File</summary>

  </details>
  
<details><summary>:heavy_division_sign: CMath</summary>

  - [rand()](#cmath.rand)
  - [lerp()](#cmath.lerp)
  - [clamp()](#cmath.clamp)
  </details>
  
<details><summary>:mag: GlobalVars</summary>

  - [get_frametime()](#globalvars.get_frametime)
  </details>
  
<details><summary>:speech_balloon: Misc</summary>

  - [print()](#print)
  </details>

---

### :paperclip: Objects:

#### <a name="Size"></a> ```Size```
```lua
local size = ...

-- width, height
print(size.w, size.h)
```

#### <a name="Pos"></a> ```Pos```
```lua
local position = ...

-- x, y coords
print(pos.x, pos.y)
```

#### <a name="Sprite"></a> ```Sprite```
```lua
local sprite = ...

-- sprite address
print(sprite)
```

#### <a name="Color"></a> ```Color```
```lua
local color = ...

-- red, green, blue, alpha values of color
print(color.r, color.g, color.b, color.a)
```

#### <a name="Font"></a> ```Font```
```lua
local font = ...

-- font address
print(font)
```

---


### :triangular_ruler: Functions:

### :movie_camera: Render

#### <a name="render.load_sprite"></a> ```load_sprite```
```lua
render.load_sprite(path: string, w: float, h: float[, t_x: float, t_y: float, t_w: size_t, t_h: size_t]): Sprite
```
| Name  | Type         | Description                                     |
| :---: | :---:        | :---:                                           |
| path  | ```string``` | Image location directory                        |
| w     | ```float```  | Width of image                                  |
| h     | ```float```  | Height of image                                 |
| t_x   | ```float```  | X coordinate of areas in the image, default = 0 |
| t_y   | ```float```  | Y coordinate of areas in the image, default = 0 |
| t_w   | ```size_t``` | Width of areas in the image, default = w        |
| t_h   | ```size_t``` | Height of areas in the image, default = h       |

Returns the [sprite](#Sprite) or nil on failure.

---

#### <a name="render.load_font"></a> ```load_font```
```lua
render.load_font(font_name: string, size: size_t): Font
```
| Name      | Type         | Description  |
| :---:     | :---:        | :---:        |
| font_name | ```string``` | Name of font |
| size      | ```size_t``` | Size of font |

Returns the [font](#Font) struct or nil on failure.

---

#### <a name="render.text"></a> ```text```
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

---

#### <a name="render.measure_text"></a> ```measure_text```
```lua
render.measure_text(font: Font, text: string): Size
```
| Name      | Type         | Description                |
| :---:     | :---:        | :---:                      |
| font      | ```Font```   | Font for text              |
| text      | ```string``` | Text that will be measured |

Returns the measured [size](#Size) of the text.

---

#### <a name="render.sprite"></a> ```sprite```
```lua
render.sprite(sprite: Sprite, x: float, y: float[, color: Color])
```
| Name      | Type        | Description                     |
| :---:     | :---:       | :---:                           |
| sprite    | ```Sprite```| Sprite for render               |
| x         | ```float``` | X coordinate                    |
| y         | ```float``` | Y coordinate                    |
| color     | ```Color``` | Color for sprite, default = nil |

Render [sprite](#Sprite) in the specified coordinates.


### :rainbow: Color

#### <a name="color.new"></a> ```new```
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

Returns the [color](#Color) struct or nil on failure.

---

#### <a name="color.unpack"></a> ```unpack```
```lua
color.unpack(color: Color): int, int, int, int
```
| Name  | Type        | Description         |
| :---: | :---:       | :---:               |
| color | ```Color``` | Color for unpacking |

Returns the integer r, g, b, a values of [color](#Color) or nil on failure.

---

#### <a name="color.to_hex"></a> ```to_hex```
```lua
color.to_hex(color: Color): string
```
| Name  | Type        | Description              |
| :---: | :---:       | :---:                    |
| color | ```Color``` | Color for casting to hex |

Returns the hex str or nil on failure.


### :computer: Window

#### <a name="window.display"></a> ```display```
```lua
window.display()
```

Display on screen what has been rendered to the window so far.

---

#### <a name="window.clear"></a> ```clear```
```lua
window.clear([color: Color])
```
| Name  | Type        | Description                               |
| :---: | :---:       | :---:                                     |
| color | ```Color``` | Color for screen filling, default = Black |

Clears the screen with a [color](#Color).

---

#### <a name="window.close"></a> ```close```
```lua
window.close()
```

Closes the window and destroy all the attached resources.

---

#### <a name="window.get_size"></a> ```get_size```
```lua
window.get_size(): Size
```

Returns the window [size](#Size) or nil on failure.

---

#### <a name="window.set_size"></a> ```set_size```
```lua
window.set_size(width: size_t, height: size_t)
```
| Name   | Type         | Description       |
| :---:  | :---:        | :---:             |
| width  | ```size_t``` | New window width  |
| height | ```size_t``` | New window height |

Sets the window a new [size](#Size).

---

#### <a name="window.get_pos"></a> ```get_pos```
```lua
window.get_pos(): Pos
```

Returns the window [pos](#Pos).

---

#### <a name="window.set_pos"></a> ```set_pos```
```lua
window.set_pos(x: int, y: int)
```
| Name  | Type      | Description           |
| :---: | :---:     | :---:                 |
| x     | ```int``` | New window x position |
| y     | ```int``` | New window y position |

Sets the window a new [pos](#Pos).

---

#### <a name="window.set_title"></a> ```set_title```
```lua
window.set_title(title: string)
```
| Name  | Type         | Description      |
| :---: | :---:        | :---:            |
| title | ```string``` | New window title |

Sets the window a new title.

---

#### <a name="window.set_vsync"></a> ```set_vsync```
```lua
window.set_vsync(state: bool)
```
| Name  | Type       | Description                               |
| :---: | :---:      | :---:                                     |
| state | ```bool``` | Enable / disable vertical synchronization |

Enables or disables the window's vsync.

---

#### <a name="window.set_frame_limit"></a> ```set_frame_limit```
```lua
window.set_frame_limit(fps_max: size_t)
```
| Name    | Type         | Description       |
| :---:   | :---:        | :---:             |
| fps_max | ```size_t``` | Frames per second |

Sets the window frame limit.

---

#### <a name="window.sleep"></a> ```sleep```
```lua
window.sleep(milliseconds: size_t)
```
| Name         | Type         | Description                    |
| :---:        | :---:        | :---:                          |
| milliseconds | ```size_t``` | Time for delay in milliseconds |

Freezes the process for the specified time.

---

#### <a name="window.await"></a> ```await```
```lua
window.await()
```

Freezes the process until any key is pressed.

---

#### <a name="window.set_icon"></a> ```set_icon```
```lua
window.set_icon(icon: Sprite)
```
| Name | Type         | Description     |
| :---:| :---:        | :---:           |
| icon | ```Sprite``` | Icon for window |

Sets a new icon for window.


### <a name="Keyboard"></a> :wrench: Keyboard
#### :star: [ENUMS](https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Mouse.php#a4fb128be433f9aafe66bc0c605daaa90)
```lua
local button_id = button.Left
```

#### <a name="keyboard.get_pressed"></a> ```get_pressed```
```lua
keyboard.get_pressed([is_key_code: bool]): string / size_t
```
| Name        | Type       | Description                             |
| :---:       | :---:      | :---:                                   |
| is_key_code | ```bool``` | Return a key code flag, default = false |

Awaiting for pressing key and return his key code / symbol or nil on failure.

---

#### <a name="keyboard.is_pressed"></a> ```is_pressed```
```lua
keyboard.is_pressed(key_code: SFML_enum): bool
```
| Name     | Type            | Description          |
| :---:    | :---:           | :---:                |
| key_code | ```SFML_enum``` | SFML Enum - key code |

Returns true if the key is pressed, else false or nil on failure.


### :mouse2: Mouse
#### :star: [ENUMS](https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Keyboard.php)
```lua
local key_id = key.W
```


### :video_game: Cursor


### :camera: View


### :musical_note: Sound


### :file_folder: File


### :heavy_division_sign: CMath

#### <a name="cmath.rand"></a> ```rand```
```lua
cmath.rand(min: int, max: int): int
```
| Name  | Type     | Description          |
| :---: | :---:    | :---:                |
| min   | ```int```| Minimum random value |
| max   | ```int```| Maximum random value |

Returns the random integer number [min, max] or nil on failure.

---

#### <a name="cmath.lerp"></a> ```lerp```
```lua
cmath.lerp(start: float, end: float, time: float): float
```
| Name  | Type       | Description |
| :---: | :---:      | :---:       |
| start | ```float```| Start value |
| end   | ```float```| End value   |
| time  | ```float```| Step value  |

Returns the linear interpolation or nil on failure.

---

#### <a name="cmath.clamp"></a> ```clamp```
```lua
cmath.clamp(number: float, lower: float, upper: float): float
```
| Name   | Type       | Description    |
| :---:  | :---:      | :---:          |
| number | ```float```| Value to clamp |
| lower  | ```float```| Lower bound    |
| upper  | ```float```| Upper bound    |

Returns the clumped value or nil on failure.


### :mag: GlobalVars
#### <a name="globalvars.get_frametime"></a> ```get_frametime```
```lua
globalvars.get_frametime(): double
```

Returns the update frame time.


### :speech_balloon: Misc
#### <a name="print"></a> ```print```
```lua
print(text: string, ...)
```
| Name  | Type     | Description |
| :---: | :---:    | :---:       |
| text  | ```any```| Text        |

Printing text on screen.
