### :exclamation: Disclaimer:
   - The [LuaJIT v2.1](https://luajit.org/luajit.html) compiler is used, as well as all its extensions, such as [FFI](https://luajit.org/ext_ffi.html), [BitOp](https://bitop.luajit.org/api.html) and etc.
   - The [Lua v5.1](https://www.lua.org/manual/5.1) is used.
   - The X, Y coordinate is the upper-left corner of any graphic object.
   - Arguments in square brackets are optional.

---

### :dash: Navigation:
#### Namespaces:
<details><summary>:movie_camera: Render</summary>

  - [text()](#render.text)
  - [sprite()](#render.sprite)
  - [measure_text()](#render.measure_text)
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
  - [is_bound()](#cursor.is_bound)
  - [in_window()](#cursor.in_window)
  </details>
    
<details><summary>:file_folder: File</summary>

  - [read()](#file.read)
  - [write()](#file.write)
  - [copy()](#file.copy)
  - [download()](#file.download)
  - [create()](#file.create)
  - [remove()](#file.remove)
  - [exists()](#file.exists)
  - [line_count()](#file.line_count)
  - [clear()](#file.clear)
  - [rename()](#file.rename)
  - [get_list()](#file.get_list)
  </details>
  
<details><summary>:heavy_division_sign: CMath</summary>

  - [rand_int()](#cmath.rand_int)
  - [rand_double()](#cmath.rand_double)
  - [lerp()](#cmath.lerp)
  - [clamp()](#cmath.clamp)
  - [round()](#cmath.round)
  </details>
  
<details><summary>:mag: GlobalVars</summary>

  - [get_executable_path()](#globalvars.get_executable_path)
  </details>
  
<details><summary>:speech_balloon: Misc</summary>

  - [print()](#print)
  </details>
  
<details><summary>:satellite: Network</summary>

  - [bind()](#network.bind)
  - [unbind()](#network.unbind)
  - [send()](#network.send)
  - [receive()](#network.receive)
  - [get_local_address()](#network.get_local_address)
  </details>
  
  
#### Objects:
<details><summary>:musical_note: Sound</summary>

  - [new()](#sound.new)
  - [copy()](#sound.copy)
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
  - [copy()](#vector2.copy)
  </details>
  
<details><summary>:pencil2: Font</summary>

  - [new()](#font.new)
  - [copy()](#font.copy)
  - [get_family()](#font.get_family)
  - [get_size()](#font.get_size)
  - [get_style()](#font.get_style)
  </details>
  
<details><summary>:rainbow: Color</summary>

  - [new()](#color.new)
  - [copy()](#color.copy)
  - [unpack()](#color.unpack)
  - [to_hex()](#color.to_hex)
  </details>
  
  <details><summary>:crystal_ball: Sprite</summary>

  - [new()](#sprite.new)
  - [copy()](#sprite.copy)
  - [set_color()](#sprite.set_color)
  - [get_color()](#sprite.get_color)
  - [set_pos()](#sprite.set_pos)
  - [get_pos()](#sprite.get_pos)
  - [set_rotation()](#sprite.set_rotation)
  - [get_rotation()](#sprite.get_rotation)
  - [set_scale()](#sprite.set_scale)
  - [get_scale()](#sprite.get_scale)
  - [set_origin()](#sprite.set_origin)
  - [get_origin()](#sprite.get_origin)
  - [set_size()](#sprite.set_size)
  - [get_size()](#sprite.get_size)
  - [scale()](#sprite.scale)
  - [rotate()](#sprite.rotate)
  - [move()](#sprite.move)
  </details>
  
  <details><summary>:camera: View</summary>

  - [new()](#view.new)
  - [copy()](#view.copy)
  - [active()](#view.active)
  - [set_port()](#view.set_port)
  - [set_center()](#view.set_center)
  - [get_size()](#view.get_size)
  - [set_size()](#view.set_size)
  - [set_zoom()](#view.set_zoom)
  - [get_rotation()](#view.get_rotation)
  - [set_rotation()](#view.set_rotation)
  </details>

---

### :movie_camera: Render

#### <a name="render.text"></a> ```text```
```lua
render.text(x: int, y: int, font: Font, text: string, color: Color)
```
| Name      | Type        | Description        |
| :---:     | :---:       | :---:              |
| x         | ```int```   | X coordinate       |
| y         | ```int```   | Y coordinate       |
| font      | ```Font```  | Font for text      |
| text      | ```string```| Text for render    |
| color     | ```Color``` | Color for text     |

Render text in the specified coordinates.

---

#### <a name="render.sprite"></a> ```sprite```
```lua
render.sprite(sprite: Sprite)
```
| Name   | Type         | Description   |
| :---:  | :---:        | :---:         |
| sprite | ```Sprite``` | Sprite object |

Render sprite.

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

#### <a name="render.rectangle"></a> ```rectangle```
```lua
render.rectangle(x: int, y: int, w: size_t, h: size_t, color: Color[, rounding: size_t])
```
| Name     | Type        | Description                                   |
| :---:    | :---:       | :---:                                         |
| x        | ```int```   | X coordinate                                  |
| y        | ```int```   | Y coordinate                                  |
| w        | ```size_t```| Width                                         |
| h        | ```size_t```| Height                                        |
| color    | ```Color``` | Color for filling the rectangle               |
| rounding | ```size_t```| Percentage of rounding [0 - 100], default = 0 |

Render rectangle on the screen.

---

#### <a name="render.circle"></a> ```circle```
```lua
render.circle(x: int, y: int, radius: size_t, color: Color[, thickness: float, outline_color: Color])
```
| Name          | Type        | Description                                 |
| :---:         | :---:       | :---:                                       |
| x             | ```int```   | X coordinate                                |
| y             | ```int```   | Y coordinate                                |
| radius        | ```size_t```| Circle radius                               |
| color         | ```Color``` | Color for filling the circle                |
| thickness     | ```float``` | Thickness of outline line, default = 0      |
| outline_color | ```Color``` | Color for filling the circle, default = nil |

Render circle on the screen.

---

#### <a name="render.line"></a> ```line```
```lua
render.line(x1: int, y1: int, x2: int, y2: int, thickness: float, color: Color)
```
| Name      | Type        | Description          |
| :---:     | :---:       | :---:                |
| x1        | ```int```   | Initial X coordinate |
| y1        | ```int```   | Initial Y coordinate |
| x2        | ```int```   | Finite X coordinate  |
| y2        | ```int```   | Finite Y coordinate  |
| thickness | ```float``` | Thickness of line    |
| color     | ```Color``` | Color for line       |

Render line on the screen.

---

#### <a name="render.polygon"></a> ```polygon```
```lua
render.polygon(points: vector<array<int, 2>>, color: Color)
```
| Name   | Type                          | Description                                                 |
| :---:  | :---:                         | :---:                                                       |
| points | ```vector<array<int, 2>>```   | Table of coords pairs, example: { { x, y }, { x, y }, ... } |
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
cursor.get_pos(): Vector2
```

Returns the cursor [position](#vector2.new).

---

#### <a name="cursor.in_window"></a> ```in_window```
```lua
cursor.in_window(): bool
```

Returns true if cursor in window, else false.

---

#### <a name="cursor.is_bound"></a> ```is_bound```
```lua
cursor.is_bound(x: size_t, y: size_t, w: size_t, h: size_t)
```
| Name             | Type          | Description                                                            |
| :---:            | :---:         | :---:                                                                  |
| x                | ```size_t```  | X position                                                             |
| y                | ```size_t```  | Y position                                                             |
| w                | ```size_t```  | Width                                                                  |
| h                | ```size_t```  | Height                                                                 |

Returns true if cursor in bounds, else false.


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

#### <a name="file.copy"></a> ```copy```
```lua
file.copy(path: string[, output_path: string])
```
| Name        | Type         | Description                        |
| :---:       | :---:        | :---:                              |
| path        | ```string``` | Path to file                       |
| output_path | ```string``` | Output file path, default = source |

Copies the file.

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

---

#### <a name="file.get_list"></a> ```get_list```
```lua
file.get_list(path: string): table<string>
```
| Name  | Type         | Description                  |
| :---: | :---:        | :---:                        |
| path  | ```string``` | Path to folder with its name |

Returns a list of names of all files in the specified folder.


### :heavy_division_sign: CMath

#### <a name="cmath.rand_int"></a> ```rand_int```
```lua
cmath.rand_int(min: int, max: int): int
```
| Name  | Type     | Description          |
| :---: | :---:    | :---:                |
| min   | ```int```| Minimum random value |
| max   | ```int```| Maximum random value |

Returns the random integer number [min, max].

---

#### <a name="cmath.rand_double"></a> ```rand_double```
```lua
cmath.rand_double(min: double, max: double): double
```
| Name  | Type        | Description          |
| :---: | :---:       | :---:                |
| min   | ```double```| Minimum random value |
| max   | ```double```| Maximum random value |

Returns the random point floating number [min, max].

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

---

#### <a name="cmath.round"></a> ```round```
```lua
cmath.round(number: float): size_t
```
| Name   | Type       | Description       |
| :---:  | :---:      | :---:             |
| number | ```float```| Value to rounding |

Returns the rounded value.


### :mag: GlobalVars
#### <a name="globalvars.get_executable_path"></a> ```get_executable_path```
```lua
globalvars.get_executable_path(): string
```

Returns the path of executable.


### :speech_balloon: Misc
#### <a name="print"></a> ```print```
```lua
print(text: any, ...)
```
| Name  | Type     | Description |
| :---: | :---:    | :---:       |
| text  | ```any```| Text        |

Printing text on screen.


### :satellite: Network
#### <a name="network.bind"></a> ```bind```
```lua
network.bind(port: int, socket_type: char)
```
| Name         | Type       | Description                                  |
| :---:        | :---:      | :---:                                        |
| port         | ```int```  | Valid port                                   |
| socket_type  | ```char``` | Socket type ('s' for server, 'c' for client) |

Binds a local socket to a port over UDP.

---

#### <a name="network.unbind"></a> ```unbind```
```lua
network.unbind()
```

Unbinds the socket from the port.

---

#### <a name="network.send"></a> ```send```
```lua
network.send([ip: string, port: int, ]packet: table)
```
| Name   | Type        | Description                                                    |
| :---:  | :---:       | :---:                                                          |
| ip     | ```string```| Recipient's IP address                                         |
| port   | ```int```   | Recipient's port                                               |
| packet | ```table``` | Data to send (table include only number, string, boolean, nil) |

Sends data to a specific address or to all binded clients.

---

#### <a name="network.receive"></a> ```receive```
```lua
network.receive(): table
```

Returns a table with the received data, nil on failure.

---

#### <a name="network.get_local_address"></a> ```get_local_address```
```lua
network.get_local_address(): string
```

Returns the local ip address.


### :musical_note: Sound
```lua
tostring(sound)   -- "{ path, volume%, loop }"
sound == sound    -- true
```

#### <a name="sound.new"></a> ```new```
```lua
Sound:new(path: string, volume: size_t[, is_repeat: bool]): Sound&
```
| Name      | Type         | Description                                        |
| :---:     | :---:        | :---:                                              |
| path      | ```string``` | Path to sound file [WAV, OGG, FLAC]                |
| volume    | ```size_t``` | Volume of sound [0 - 100]                          |
| is_repeat | ```bool```   | If true then sound will be looped, default = false |

Returns the sound reference.

---

#### <a name="sound.copy"></a> ```copy```
```lua
sound_object:copy(): Sound
```

Returns the sound copy.

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
vec * vec        -- new vec
vec / vec        -- new vec
vec + number     -- new vec
vec - number     -- new vec
vec * number     -- new vec
vec / number     -- new vec
```

#### <a name="vector2.new"></a> ```new```
```lua
Vector2:new(x: double, y: double): Vector2&
```
| Name  | Type         | Description  |
| :---: | :---:        | :---:        |
| x     | ```double``` | X coordinate |
| y     | ```double``` | Y coordinate |

Returns the vector2 reference.

---

#### <a name="vector2.copy"></a> ```copy```
```lua
vector2_object:copy(): Vector2
```

Returns the vector2 copy.


### :pencil2: Font
```lua
tostring(font)   -- "{ family, size, style }"
font == font     -- true
```

#### <a name="font.new"></a> ```new```
```lua
Font:new(name: string, size: size_t[, style: string]): Font&
```
| Name  | Type         | Description                                                                                                                     |
| :---: | :---:        | :---:                                                                                                                           |
| name  | ```string``` | Name of font, with file extension                                                                                               |
| size  | ```size_t``` | Size of font                                                                                                                    |
| style | ```string``` | Style of font, can store symbols: 'r' - Regular, 'b' - Bold, 'i' - Italic, 'l' - Underlined, 's' - StrikeThrough, default = "r" |

Returns the font reference.

---

#### <a name="font.copy"></a> ```copy```
```lua
font_object:copy(): Font
```

Returns the font copy.

---

#### <a name="font.get_family"></a> ```get_family```
```lua
font_object:get_family(): string
```

Returns the font family.

---

#### <a name="font.get_size"></a> ```get_size```
```lua
font_object:get_size(): size_t
```

Returns the font size.

---

#### <a name="font.get_style"></a> ```get_style```
```lua
font_object:get_style(): string
```

Returns the font style, example: "r".


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
Color:new(r: int, g: int, b: int[, a: int]): Color&
Color:new(hex: string): Color&
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

Returns the color reference.

---

#### <a name="color.copy"></a> ```copy```
```lua
color_object:copy(): Color
```

Returns the color copy.

---

#### <a name="color.unpack"></a> ```unpack```
```lua
color_object:unpack(color: Color): size_t, size_t, size_t, size_t
```
| Name  | Type        | Description         |
| :---: | :---:       | :---:               |
| color | ```Color``` | Color for unpacking |

Returns the unsigned integer r, g, b, a values of [color](#color.new).

---

#### <a name="color.to_hex"></a> ```to_hex```
```lua
color_object:to_hex(color: Color): string
```
| Name  | Type        | Description              |
| :---: | :---:       | :---:                    |
| color | ```Color``` | Color for casting to hex |

Returns the hex string.


### :crystal_ball: Sprite
```lua
tostring(sprite)   -- "{ path, x: x, y: y }"
sprite == sprite   -- true
```

#### <a name="sprite.new"></a> ```new```
```lua
Sprite:new(path: string, w: int, h: int[, t_x: size_t, t_y: size_t, t_w: size_t, t_h: size_t]): Sprite&
```
| Name  | Type         | Description                                     |
| :---: | :---:        | :---:                                           |
| path  | ```string``` | Image location directory                        |
| w     | ```int```    | Width of image                                  |
| h     | ```int```    | Height of image                                 |
| t_x   | ```size_t``` | X coordinate of areas in the image, default = 0 |
| t_y   | ```size_t``` | Y coordinate of areas in the image, default = 0 |
| t_w   | ```size_t``` | Width of areas in the image, default = w        |
| t_h   | ```size_t``` | Height of areas in the image, default = h       |

Returns the sprite reference.

---

#### <a name="sprite.copy"></a> ```copy```
```lua
sprite_object:copy(): Sprite
```

Returns the sprite copy.

---

#### <a name="sprite.set_color"></a> ```set_color```
```lua
sprite_object:set_color(color: Color)
```
| Name  | Type        | Description          |
| :---: | :---:       | :---:                |
| color | ```Сolor``` | New color for sprite |

Sets a new color for the sprite.

---

#### <a name="sprite.get_color"></a> ```get_color```
```lua
sprite_object:get_color(): Color
```

Returns the color of the sprite.

---

#### <a name="sprite.set_pos"></a> ```set_pos```
```lua
sprite_object:set_pos(x: size_t, y: size_t)
```
| Name  | Type         | Description                 |
| :---: | :---:        | :---:                       |
| x     | ```size_t``` | New x coordinate for sprite |
| y     | ```size_t``` | New y coordinate for sprite |

Sets a new position for the sprite.

---

#### <a name="sprite.get_pos"></a> ```get_pos```
```lua
sprite_object:get_pos(): Vector2
```

Returns the position of the sprite.

---

#### <a name="sprite.set_rotation"></a> ```set_rotation```
```lua
sprite_object:set_rotation(angle: double)
```
| Name  | Type         | Description                   |
| :---: | :---:        | :---:                         |
| angle | ```double``` | New rotation angle for sprite |

Sets a new rotation angle for the sprite.

---

#### <a name="sprite.get_rotation"></a> ```get_rotation```
```lua
sprite_object:get_rotation(): double
```

Returns the rotation angle of the sprite.

---

#### <a name="sprite.set_scale"></a> ```set_scale```
```lua
sprite_object:set_scale(x_factor: double, y_factor: double)
```
| Name     | Type         | Description                   |
| :---:    | :---:        | :---:                         |
| x_factor | ```double``` | New x scale factor for sprite |
| y_factor | ```double``` | New y scale factor for sprite |

Sets a new scale for the sprite.

---

#### <a name="sprite.get_scale"></a> ```get_scale```
```lua
sprite_object:get_scale(): Vector2
```

Returns the scale of the sprite.

---

#### <a name="sprite.set_origin"></a> ```set_origin```
```lua
sprite_object:set_origin(x: double, y: double)
```
| Name  | Type         | Description             |
| :---: | :---:        | :---:                   |
| x     | ```double``` | New x origin for sprite |
| y     | ```double``` | New y origin for sprite |

Sets a new origin for the sprite.

---

#### <a name="sprite.get_origin"></a> ```get_origin```
```lua
sprite_object:get_origin(): Vector2
```

Returns the origin of the sprite.

---

#### <a name="sprite.set_size"></a> ```set_size```
```lua
sprite_object:set_size(w: int, h: int)
```
| Name  | Type      | Description                  |
| :---: | :---:     | :---:                        |
| w     | ```int``` | New width for sprite         |
| h     | ```int``` | New heigth origin for sprite |

Sets a new size for the sprite.

---

#### <a name="sprite.get_size"></a> ```get_size```
```lua
sprite_object:get_size(): Vector2
```

Returns the size of the sprite.

---

#### <a name="sprite.scale"></a> ```scale```
```lua
sprite_object:scale(x_factor: double, y_factor: double)
```
| Name     | Type         | Description               |
| :---:    | :---:        | :---:                     |
| x_factor | ```double``` | X scale factor for sprite |
| y_factor | ```double``` | Y scale factor for sprite |

Scales the sprite.

---

#### <a name="sprite.rotate"></a> ```rotate```
```lua
sprite_object:rotate(angle: double)
```
| Name  | Type         | Description                |
| :---: | :---:        | :---:                      |
| angle | ```double``` | Rotations angle for sprite |

Rotates the sprite.

---

#### <a name="sprite.move"></a> ```move```
```lua
sprite_object:move(x_offset: double, y_offset: double)
```
| Name     | Type         | Description                       |
| :---:    | :---:        | :---:                             |
| x_offset | ```double``` | X offset of coordinate for sprite |
| y_offset | ```double``` | Y offset of coordinate for sprite |

Moves the sprite.


### :camera: View
```lua
tostring(view)   -- "{ x: x, y: y, w: w, h: h }"
view == view     -- true
```

#### <a name="view.new"></a> ```new```
```lua
View:new([x: size_t, y: size_t, w: size_t, h: size_t]): View&
```
| Name   | Type        | Description             |
| :---:  | :---:       | :---:                   |
| x      | ```size_t```| X position, default = 0 |
| y      | ```size_t```| Y position, default = 0 |
| w      | ```size_t```| Width, default = 0      |
| h      | ```size_t```| Height, default = 0     |

Returns the view reference.

---

#### <a name="view.copy"></a> ```copy```
```lua
view_object:view(): View
```

Returns the view copy.

---

#### <a name="view.active"></a> ```active```
```lua
view_object:active()
```

Activates the view.

---


#### <a name="view.set_port"></a> ```set_port```
```lua
view_object:set_port(x: size_t, y: size_t, w: size_t, h: size_t)
```
| Name  | Type        | Description |
| :---: | :---:       | :---:       |
| x     | ```size_t```| X position  |
| y     | ```size_t```| Y position  |
| w     | ```size_t```| Width       |
| h     | ```size_t```| Height      |

Sets the view a new view port.

---

#### <a name="view.set_center"></a> ```set_center```
```lua
view_object:set_center(x: size_t, y: size_t)
```
| Name  | Type        | Description |
| :---: | :---:       | :---:       |
| x     | ```size_t```| X position  |
| y     | ```size_t```| Y position  |

Sets the view a new center position.

---

#### <a name="view.get_size"></a> ```get_size```
```lua
view_object:get_size(): Vector2
```

Returns [size](#vector2.new) of view.

---

#### <a name="view.set_size"></a> ```set_size```
```lua
view_object:set_size(w: size_t, h: size_t)
```
| Name  | Type         | Description |
| :---: | :---:        | :---:       |
| w     | ```size_t``` | Width       |
| h     | ```size_t``` | Height      |

Sets the view a new size.

---

#### <a name="view.set_zoom"></a> ```set_zoom```
```lua
view_object:set_zoom(zoom_factor: float)
```
| Name        | Type        | Description |
| :---:       | :---:       | :---:       |
| zoom_factor | ```float``` | Zoom degree |

Zooms view.

---

#### <a name="view.get_rotation"></a> ```get_rotation```
```lua
view_object:get_rotation(): float
```

Returns a view rotation.

---

#### <a name="view.set_rotation"></a> ```set_rotation```
```lua
view_object:set_rotation(angle: float)
```
| Name  | Type        | Description              |
| :---: | :---:       | :---:                    |
| angle | ```float``` | Rotation angle [0 - 360] |

Sets the view a new rotation angle.
