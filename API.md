### :dash: Navigation
#### Functions
<details><summary>:movie_camera: Render</summary>

  - [create_sprite()](#render.create_sprite)
  - [text()](#render.text)
  - [measure_text()](#render.measure_text)
  - [sprite()](#render.sprite)
  - [rectangle()](#render.rectangle)
  - [circle()](#render.circle)
  - [line()](#render.line)
  - [polygon()](#render.polygon)
  </details>
  
<details><summary>:computer: Window</summary>

  - [display()](#window.display)
  - [clear()](#window.clear)
  - [close()](#window.close)
  - [capture()](#window.capture)
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

  - [get_pressed()](#mouse.get_pressed)
  - [is_pressed()](#mouse.is_pressed)
  - [is_scrolling_up()](#mouse.is_scrolling_up)
  - [is_scrolling_down()](#mouse.is_scrolling_down)
  </details>
  
<details><summary>:video_game: Cursor</summary>

  - [get_pos()](#cursor.get_pos)
  - [set_pos()](#cursor.set_pos)
  - [in_bounds()](#cursor.in_bounds)
  - [in_window()](#cursor.in_window)
  </details>
  
<details><summary>:camera: View</summary>

  - [new()](#view.new)
  - [active()](#view.active)
  - [set_port()](#view.set_port)
  - [set_center()](#view.set_center)
  - [get_size()](#view.get_size)
  - [set_size()](#view.set_size)
  - [set_zoom()](#view.set_zoom)
  - [get_rotation()](#view.get_rotation)
  - [set_rotation()](#view.set_rotation)
  </details>
    
<details><summary>:file_folder: File</summary>

  - [read()](#file.read)
  - [write()](#file.write)
  - [download()](#file.download)
  - [create()](#file.create)
  - [remove()](#file.remove)
  - [exists()](#file.exists)
  - [line_count()](#file.line_count)
  - [clear()](#file.clear)
  - [rename()](#file.rename)
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
  
#### Objects
<details><summary>:musical_note: Sound</summary>

  - [new()](#sound.new)
  - [get_path()](#sound.get_path)
  - [play()](#sound.play)
  - [stop()](#sound.stop)
  - [set_volume()](#sound.set_volume)
  - [get_volume()](#sound.get_volume)
  - [set_loop()](#sound.set_loop)
  - [get_loop()](#sound.get_loop)
  </details>
  
<details><summary>:round_pushpin: Vector2</summary>

  - [new()](#vector2.new)
  </details>
  
<details><summary>:pencil2: Font</summary>

  - [new()](#font.new)
  - [get_family()](#font.get_family)
  </details>
  
<details><summary>:rainbow: Color</summary>

  - [new()](#color.new)
  - [unpack()](#color.unpack)
  - [to_hex()](#color.to_hex)
  </details>

#### <a name="View"></a> ```View```
```lua
local view_obj = ...

-- view address
print(view_obj)
```

#### <a name="Sprite"></a> ```Sprite```
```lua
local sprite = ...

-- sprite address
print(sprite)
```

---

### :movie_camera: Render

#### <a name="render.create_sprite"></a> ```create_sprite```
```lua
render.create_sprite(path: string, w: float, h: float[, t_x: size_t, t_y: size_t, t_w: size_t, t_h: size_t]): Sprite
```
| Name  | Type         | Description                                     |
| :---: | :---:        | :---:                                           |
| path  | ```string``` | Image location directory                        |
| w     | ```float```  | Width of image                                  |
| h     | ```float```  | Height of image                                 |
| t_x   | ```size_t``` | X coordinate of areas in the image, default = 0 |
| t_y   | ```size_t``` | Y coordinate of areas in the image, default = 0 |
| t_w   | ```size_t``` | Width of areas in the image, default = w        |
| t_h   | ```size_t``` | Height of areas in the image, default = h       |

Returns the [sprite](#Sprite).

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
render.measure_text(font: Font, text: string): Vector2
```
| Name      | Type         | Description                |
| :---:     | :---:        | :---:                      |
| font      | ```Font```   | Font for text              |
| text      | ```string``` | Text that will be measured |

Returns the measured [size](#vector2.new) of the text.

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

---

#### <a name="render.rectangle"></a> ```rectangle```
```lua
render.rectangle(x: float, y: float, w: float, h: float, color: Color[, rounding: float])
```
| Name     | Type        | Description                       |
| :---:    | :---:       | :---:                             |
| x        | ```float``` | X coordinate                      |
| y        | ```float``` | Y coordinate                      |
| w        | ```float``` | Width                             |
| h        | ```float``` | Height                            |
| color    | ```Color``` | Color for filling the rectangle   |
| rounding | ```float``` | Edge rounding factor, default = 0 |

Render rectangle on the screen.

---

#### <a name="render.circle"></a> ```circle```
```lua
render.circle(x: float, y: float, radius: float, color: Color[, thickness: float, outline_color: Color])
```
| Name          | Type        | Description                                 |
| :---:         | :---:       | :---:                                       |
| x             | ```float``` | X coordinate                                |
| y             | ```float``` | Y coordinate                                |
| radius        | ```float``` | Circle radius                               |
| color         | ```Color``` | Color for filling the circle                |
| thickness     | ```float``` | Thickness of outline line, default = 0      |
| outline_color | ```Color``` | Color for filling the circle, default = nil |

Render circle on the screen.

---

#### <a name="render.line"></a> ```line```
```lua
render.line(x1: float, y1: float, x2: float, y2: float, thickness: float, color: Color)
```
| Name      | Type        | Description          |
| :---:     | :---:       | :---:                |
| x1        | ```float``` | Initial X coordinate |
| y1        | ```float``` | Initial Y coordinate |
| x2        | ```float``` | Finite X coordinate  |
| y2        | ```float``` | Finite Y coordinate  |
| color     | ```Color``` | Color for line       |
| thickness | ```float``` | Thickness of line    |

Render line on the screen.

---

#### <a name="render.polygon"></a> ```polygon```
```lua
render.polygon(points: vector<array<float, 2>>, color: Color)
```
| Name   | Type                          | Description                                                 |
| :---:  | :---:                         | :---:                                                       |
| points | ```vector<array<float, 2>>``` | Table of coords pairs, example: { { x, y }, { x, y }, ... } |
| color  | ```Color```                   | Color for polygon                                           |

Render polygon on the screen.


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

#### <a name="window.capture"></a> ```capture```
```lua
window.capture(path: string)
```
| Name  | Type         | Description                           |
| :---: | :---:        | :---:                                 |
| path  | ```string``` | Screenshot output path with file name |

Takes a screenshot of the window and saves it.

---

#### <a name="window.get_size"></a> ```get_size```
```lua
window.get_size(): Vector2
```

Returns the window [size](#vector2.new.new).

---

#### <a name="window.set_size"></a> ```set_size```
```lua
window.set_size(width: size_t, height: size_t)
```
| Name   | Type         | Description       |
| :---:  | :---:        | :---:             |
| width  | ```size_t``` | New window width  |
| height | ```size_t``` | New window height |

Sets the window a new [size](#vector2.new).

---

#### <a name="window.get_pos"></a> ```get_pos```
```lua
window.get_pos(): Vector2
```

Returns the window [position](#vector2.new).

---

#### <a name="window.set_pos"></a> ```set_pos```
```lua
window.set_pos(x: int, y: int)
```
| Name  | Type      | Description           |
| :---: | :---:     | :---:                 |
| x     | ```int``` | New window x position |
| y     | ```int``` | New window y position |

Sets the window a new position.

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
#### :star: [ENUMS](https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Keyboard.php)
```lua
local key_id = key.Left
```

#### <a name="keyboard.get_pressed"></a> ```get_pressed```
```lua
keyboard.get_pressed([return_symbol]): SFML_enum / char
```
| Name          | Type       | Description                                        |
| :---:         | :---:      | :---:                                              |
| return_symbol | ```bool``` | If true then function return char, default = false |

Awaiting for pressing key and return [enum](https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Keyboard.php) / char.

---

#### <a name="keyboard.is_pressed"></a> ```is_pressed```
```lua
keyboard.is_pressed(key_code: SFML_enum): bool
```
| Name     | Type            | Description          |
| :---:    | :---:           | :---:                |
| key_code | ```SFML_enum``` | SFML Enum - key code |

Returns true if the key is pressed, else false.


### :mouse2: Mouse
#### :star: [ENUMS](https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Mouse.php#a4fb128be433f9aafe66bc0c605daaa90)
```lua
local button_id = button.W
```

#### <a name="mouse.get_pressed"></a> ```get_pressed```
```lua
mouse.get_pressed(): SFML_enum
```

Awaiting for pressing button and return [enum](https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Mouse.php#a4fb128be433f9aafe66bc0c605daaa90).

---

#### <a name="mouse.is_pressed"></a> ```is_pressed```
```lua
mouse.is_pressed(button_code: SFML_enum): bool
```
| Name        | Type            | Description             |
| :---:       | :---:           | :---:                   |
| button_code | ```SFML_enum``` | SFML Enum - button code |

Returns true if the button is pressed, else false.

---

#### <a name="mouse.is_scrolling_up"></a> ```is_scrolling_up```
```lua
mouse.is_scrolling_up(): bool
```

Returns true if scrolling up, else false.

---

#### <a name="mouse.is_scrolling_down"></a> ```is_scrolling_down```
```lua
mouse.is_scrolling_down(): bool
```

Returns true if scrolling down, else false.


### :video_game: Cursor
#### <a name="cursor.get_pos"></a> ```get_pos```
```lua
cursor.get_pos([regarding_window: bool]): Vector2
```
| Name             | Type       | Description                                                          |
| :---:            | :---:      | :---:                                                                |
| regarding_window | ```bool``` | Is true then function sets position regarding window, default = true |

Returns the cursor [position](#vector2.new).

---

#### <a name="cursor.set_pos"></a> ```set_pos```
```lua
cursor.set_pos(x: int, y: int[, regarding_window: bool])
```
| Name             | Type       | Description                                                            |
| :---:            | :---:      | :---:                                                                  |
| x                | ```int```  | New cursor x position                                                  |
| y                | ```int```  | New cursor y position                                                  |
| regarding_window | ```bool``` | Is true then function return position regarding window, default = true |

Sets the cursor a new position.

---

#### <a name="cursor.in_window"></a> ```in_window```
```lua
cursor.in_window(): bool
```

Returns true if cursor in window, else false.

---

#### <a name="cursor.in_bounds"></a> ```in_bounds```
```lua
cursor.in_bounds(x: float, y: float, w: float, h: float[, regarding_window: bool])
```
| Name             | Type         | Description                                                            |
| :---:            | :---:        | :---:                                                                  |
| x                | ```float```  | X position                                                             |
| y                | ```float```  | Y position                                                             |
| w                | ```float```  | Width                                                                  |
| h                | ```float```  | Height                                                                 |
| regarding_window | ```bool```   | Is true then function return position regarding window, default = true |

Returns true if cursor in bounds, else false.

### :camera: View

#### <a name="view.new"></a> ```new```
```lua
view.new([x: float, y: float, w: float, h: float]): View
```
| Name   | Type        | Description |
| :---:  | :---:       | :---:       |
| x      | ```float``` | X position  |
| y      | ```float``` | Y position  |
| w      | ```float``` | Width       |
| h      | ```float``` | Height      |

Returns the [view](#View).

---

#### <a name="view.active"></a> ```active```
```lua
view.active(view: View)
```
| Name  | Type       | Description |
| :---: | :---:      | :---:       |
| view  | ```View``` | View object |

Activates the [view](#View).

---


#### <a name="view.set_port"></a> ```set_port```
```lua
view.set_port(view: View, x: float, y: float, w: float, h: float)
```
| Name  | Type        | Description |
| :---: | :---:       | :---:       |
| view  | ```View```  | View object |
| x     | ```float``` | X position  |
| y     | ```float``` | Y position  |
| w     | ```float``` | Width       |
| h     | ```float``` | Height      |

Sets the [view](#View) a new view port.

---

#### <a name="view.set_center"></a> ```set_center```
```lua
view.set_center(view: View, x: float, y: float)
```
| Name  | Type        | Description |
| :---: | :---:       | :---:       |
| view  | ```View```  | View object |
| x     | ```float``` | X position  |
| y     | ```float``` | Y position  |

Sets the [view](#View) a new center position.

---

#### <a name="view.get_size"></a> ```get_size```
```lua
view.get_size(view: View): Vector2
```
| Name  | Type        | Description |
| :---: | :---:       | :---:       |
| view  | ```View```  | View object |

Returns [size](#vector2.new) of [view](#View).

---

#### <a name="view.set_size"></a> ```set_size```
```lua
view.set_size(view: View, w: float, h: float)
```
| Name  | Type        | Description |
| :---: | :---:       | :---:       |
| view  | ```View```  | View object |
| w     | ```float``` | Width       |
| h     | ```float``` | Height      |

Sets the [view](#View) a new size.

---

#### <a name="view.set_zoom"></a> ```set_zoom```
```lua
view.set_zoom(view: View, zoom_factor: float)
```
| Name        | Type        | Description |
| :---:       | :---:       | :---:       |
| view        | ```View```  | View object |
| zoom_factor | ```float``` | Zoom degree |

Zooms [view](#View).

---

#### <a name="view.get_rotation"></a> ```get_rotation```
```lua
view.get_rotation(view: View): float
```
| Name        | Type        | Description |
| :---:       | :---:       | :---:       |
| view        | ```View```  | View object |

Returns a [view](#View) rotation.

---

#### <a name="view.set_rotation"></a> ```set_rotation```
```lua
view.set_rotation(view: View, angle: float)
```
| Name  | Type        | Description              |
| :---: | :---:       | :---:                    |
| view  | ```View```  | View object              |
| angle | ```float``` | Rotation angle [0 - 360] |

Sets the [view](#View) a new rotation angle.


### :file_folder: File

#### <a name="file.read"></a> ```read```
```lua
file.read(path: string[, line_number: size_t]): table<string>
```
| Name        | Type         | Description                                          |
| :---:       | :---:        | :---:                                                |
| path        | ```string``` | Path to file                                         |
| line_number | ```size_t``` | Number of the line to be read, default read all file |

Reads the file and writes it to the string table.

---

#### <a name="file.write"></a> ```write```
```lua
file.write(path: string, content: table<string>[, is_rewrite: bool])
file.write(path: string, content: string[, is_rewrite: bool])
```
| Name       | Type                              | Description                                                                |
| :---:      | :---:                             | :---:                                                                      |
| path       | ```string```                      | Path to file                                                               |
| content    | ```table<string>``` / ```string```| Content that will be written to a file                                     |
| is_rewrite | ```bool```                        | If the value is true, file will be cleared before writing, default = false |

Writes the specified content to a file.

---

#### <a name="file.download"></a> ```download```
```lua
file.download(path: string, url: string)
```
| Name  | Type         | Description                               |
| :---: | :---:        | :---:                                     |
| path  | ```string``` | Path to file with its name and extension  |
| url   | ```string``` | The url where the file will be downloaded |

Downloads the file from the specified link to the specified path.

---

#### <a name="file.create"></a> ```create```
```lua
file.create(path: string)
```
| Name  | Type         | Description                          |
| :---: | :---:        | :---:                                |
| path  | ```string``` | Path to file or folder with its name |

Creates a file or folder at the specified path.

---

#### <a name="file.remove"></a> ```remove```
```lua
file.remove(path: string)
```
| Name  | Type         | Description                          |
| :---: | :---:        | :---:                                |
| path  | ```string``` | Path to file or folder with its name |

Deletes a file or folder at the specified path.

---

#### <a name="file.exists"></a> ```exists```
```lua
file.exists(path: string): bool
```
| Name  | Type         | Description                          |
| :---: | :---:        | :---:                                |
| path  | ```string``` | Path to file or folder with its name |

Returns true if the file is found, else false.

---

#### <a name="file.line_count"></a> ```line_count```
```lua
file.line_count(path: string): size_t
```
| Name  | Type         | Description                          |
| :---: | :---:        | :---:                                |
| path  | ```string``` | Path to file or folder with its name |

Returns the number of lines in the specified file.

---

#### <a name="file.clear"></a> ```clear```
```lua
file.clear(path: string)
```
| Name  | Type         | Description                          |
| :---: | :---:        | :---:                                |
| path  | ```string``` | Path to file or folder with its name |

Clears the specified file.

---

#### <a name="file.rename"></a> ```rename```
```lua
file.rename(path: string, new_name: string)
```
| Name     | Type         | Description                          |
| :---:    | :---:        | :---:                                |
| path     | ```string``` | Path to file or folder with its name |
| new_name | ```string``` | New name for the file                |

Renames the specified file to a new name.


### :heavy_division_sign: CMath

#### <a name="cmath.rand"></a> ```rand```
```lua
cmath.rand(min: int, max: int): int
```
| Name  | Type     | Description          |
| :---: | :---:    | :---:                |
| min   | ```int```| Minimum random value |
| max   | ```int```| Maximum random value |

Returns the random integer number [min, max].

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

Returns the linear interpolation.

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

Returns the clumped value.


### :mag: GlobalVars
#### <a name="globalvars.get_frametime"></a> ```get_frametime```
```lua
globalvars.get_frametime(): double
```

Returns the update frame time.


### :speech_balloon: Misc
#### <a name="print"></a> ```print```
```lua
print(text: any, ...)
```
| Name  | Type     | Description |
| :---: | :---:    | :---:       |
| text  | ```any```| Text        |

Printing text on screen.


### :musical_note: Sound
```lua
tostring(sound)   -- "{ path, volume%, loop }"
sound == sound    -- true
```

#### <a name="sound.new"></a> ```new```
```lua
Sound:new(path: string, volume: size_t[, is_repeat: bool]): Sound
```
| Name      | Type         | Description                                        |
| :---:     | :---:        | :---:                                              |
| path      | ```string``` | Path to sound file [WAV, OGG, FLAC]                |
| volume    | ```size_t``` | Volume of sound [0 - 100]                          |
| is_repeat | ```bool```   | If true then sound will be looped, default = false |

Returns the sound object.

---

#### <a name="sound.play"></a> ```play```
```lua
sound_object:play([is_reset: bool])
```
| Name     | Type        | Description                                                                      |
| :---:    | :---:       | :---:                                                                            |
| is_reset | ```bool```  | If true, the sound will be played every time from the beginning, default = false |

Plays [sound](#sound.new).

---

#### <a name="sound.stop"></a> ```stop```
```lua
sound_object:stop()
```

Stops [sound](#sound.new).

---

#### <a name="sound.get_path"></a> ```get_path```
```lua
sound_object:get_path(): string
```

Returns the [sound](#sound.new) file path.

---

#### <a name="sound.set_volume"></a> ```set_volume```
```lua
sound_object:set_volume(volume: size_t)
```
| Name   | Type         | Description               |
| :---:  | :---:        | :---:                     |
| volume | ```size_t``` | Volume of sound [0 - 100] |

Sets the [sound](#sound.new) a new volume.

---

#### <a name="sound.get_volume"></a> ```get_volume```
```lua
sound_object:get_volume(): size_t
```

Returns the [sound](#sound.new) volume.

---

#### <a name="sound.set_loop"></a> ```set_loop```
```lua
sound_object:set_loop(is_repeat: bool)
```
| Name      | Type        | Description                           |
| :---:     | :---:       | :---:                                 |
| is_repeat | ```bool```  | If true then the sound will be looped |

Sets the [sound](#sound.new) a new loop.

---

#### <a name="sound.get_loop"></a> ```get_loop```
```lua
sound_object:get_loop(): bool
```

Returns true if the sound is looped, else false.


### :round_pushpin: Vector2
```lua
vec.x, vec.y     -- x, y
vec[1], vec[2]   -- x, y
#vec             -- 2
tostring(vec)    -- "{ x, y }"
vec == vec       -- true
vec + vec        -- new vec
vec - vec        -- new vec
```

#### <a name="vector2.new"></a> ```new```
```lua
Vector2:new(x: double, y: double): Vector2
```
| Name  | Type         | Description  |
| :---: | :---:        | :---:        |
| x     | ```double``` | X coordinate |
| y     | ```double``` | Y coordinate |

Returns the vector2 object.


### :pencil2: Font
```lua
tostring(font)   -- "{ family, size }"
font == font     -- true
```

#### <a name="font.new"></a> ```new```
```lua
Font:new(name: string, size: size_t): Font
```
| Name  | Type         | Description                       |
| :---: | :---:        | :---:                             |
| name  | ```string``` | Name of font, with file extension |
| size  | ```size_t``` | Size of font                      |

Returns the font object.

---

#### <a name="font.get_family"></a> ```get_family```
```lua
font_object:get_family(): string
```

Returns the font family.


### :rainbow: Color
```lua
color.r, color.g, color.b, color.a       -- r, g, b, a
color[1], color[2], color[3], color[4]   -- r, g, b, a
#color                                   -- 4
tostring(color)                          -- "{ r, g, b, a }"
color == color                           -- true
```

#### <a name="color.new"></a> ```new```
```lua
Color:new(r: int, g: int, b: int[, a: int]): Color
Color:new(hex: string): Color
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

Returns the color object.

---

#### <a name="color.unpack"></a> ```unpack```
```lua
color_object:unpack(color: Color): int, int, int, int
```
| Name  | Type        | Description         |
| :---: | :---:       | :---:               |
| color | ```Color``` | Color for unpacking |

Returns the integer r, g, b, a values of [color](#color.new).

---

#### <a name="color.to_hex"></a> ```to_hex```
```lua
color_object:to_hex(color: Color): string
```
| Name  | Type        | Description              |
| :---: | :---:       | :---:                    |
| color | ```Color``` | Color for casting to hex |

Returns the hex string.
