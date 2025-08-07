### :exclamation: Disclaimer:
   - The [LuaJIT v2.1](https://luajit.org/luajit.html) compiler is used, as well as all its extensions, such as [FFI](https://luajit.org/ext_ffi.html), [BitOp](https://bitop.luajit.org/api.html) and etc.
   - The [Lua v5.1](https://www.lua.org/manual/5.1) is used.
   - The X, Y coordinate is the upper-left corner of any graphic object.
   - Arguments in square brackets are optional.
   - Be careful with passing objects to function, most likely you expected to get a copy of it, use the copy() method.

---

### :dash: Navigation:
#### Namespaces:
<details><summary>:movie_camera: Render</summary>

  - [text()](#render.text)
  - [sprite()](#render.sprite)
  - [measure_text()](#render.measure_text)
  - [rectangle()](#render.rectangle)
  - [outline_rectangle()](#render.outline_rectangle)
  - [gradient_rectangle()](#render.gradient_rectangle)
  - [circle()](#render.circle)
  - [line()](#render.line)
  - [polygon()](#render.polygon)
  </details>
  
<details><summary>:computer: Window</summary>

  - [is_open()](#window.is_open)
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
  - [set_style()](#window.set_style)
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
  - [change_type()](#cursor.change_type)
  </details>
    
<details><summary>:file_folder: File</summary>

  - [read()](#file.read)
  - [write()](#file.write)
  - [copy()](#file.copy)
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
  - [get_os_name()](#globalvars.get_os_name)
  - [get_args()](#globalvars.get_args)
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
  - [is_play()](#sound.is_play)
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
  - [get_glyph()](#font.get_glyph)
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
render.text(x: integer, y: integer, font: Font, text: string, color: Color)
```
| Name      | Type        | Description        |
| :---:     | :---:       | :---:              |
| x         | ```integer```   | X coordinate       |
| y         | ```integer```   | Y coordinate       |
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
render.rectangle(x: integer, y: integer, w: integer, h: integer, color: Color[, rounding: integer])
```
| Name     | Type        | Description                                   |
| :---:    | :---:       | :---:                                         |
| x        | ```integer```   | X coordinate                                  |
| y        | ```integer```   | Y coordinate                                  |
| w        | ```integer```| Width                                         |
| h        | ```integer```| Height                                        |
| color    | ```Color``` | Color for filling the rectangle               |
| rounding | ```integer```| Percentage of rounding [0 - 100], default = 0 |

Render rectangle on the screen.

---

#### <a name="render.outline_rectangle"></a> ```outline_rectangle```
```lua
render.outline_rectangle(x: integer, y: integer, w: integer, h: integer, thickness: number, color: Color[, rounding: integer])
```
| Name      | Type        | Description                                   |
| :---:     | :---:       | :---:                                         |
| x         | ```integer```   | X coordinate                                  |
| y         | ```integer```   | Y coordinate                                  |
| w         | ```integer```| Width                                         |
| h         | ```integer```| Height                                        |
| thickness | ```number``` | Thickness of outline line                     |
| color     | ```Color``` | Color for outline line                        |
| rounding  | ```integer```| Percentage of rounding [0 - 100], default = 0 |

Render rectangle consisting of 4 contour lines, empty inside.

---

#### <a name="render.gradient"></a> ```gradient```
```lua
render.gradient(x: integer, y: integer, w: integer, h: integer, top_left: Color, top_right: Color, bottom_left: Color, bottom_right: Color)
```
| Name         | Type        | Description                                   |
| :---:        | :---:       | :---:                                         |
| x            | ```integer```   | X coordinate                                  |
| y            | ```integer```   | Y coordinate                                  |
| w            | ```integer```| Width                                         |
| h            | ```integer```| Height                                        |
| top_left     | ```Color``` | Color of the top left rectangle position      |
| top_right    | ```Color``` | Color of the top right rectangle position     |
| bottom_left  | ```Color``` | Color of the bottom left rectangle position   |
| bottom_right | ```Color``` | Color of the bottom right rectangle position  |

Render gradient rectangle on the screen.

---

#### <a name="render.circle"></a> ```circle```
```lua
render.circle(x: integer, y: integer, radius: integer, color: Color[, thickness: number, outline_color: Color])
```
| Name          | Type        | Description                                 |
| :---:         | :---:       | :---:                                       |
| x             | ```integer```   | X coordinate                                |
| y             | ```integer```   | Y coordinate                                |
| radius        | ```integer```| Circle radius                               |
| color         | ```Color``` | Color for filling the circle                |
| thickness     | ```number``` | Thickness of outline line, default = 0      |
| outline_color | ```Color``` | Color for filling the circle, default = nil |

Render circle on the screen.

---

#### <a name="render.line"></a> ```line```
```lua
render.line(x1: integer, y1: integer, x2: integer, y2: integer, thickness: number, color: Color)
```
| Name      | Type        | Description          |
| :---:     | :---:       | :---:                |
| x1        | ```integer```   | Initial X coordinate |
| y1        | ```integer```   | Initial Y coordinate |
| x2        | ```integer```   | Finite X coordinate  |
| y2        | ```integer```   | Finite Y coordinate  |
| thickness | ```number``` | Thickness of line    |
| color     | ```Color``` | Color for line       |

Render line on the screen.

---

#### <a name="render.polygon"></a> ```polygon```
```lua
render.polygon(points: table<array<integer, 2>>, color: Color)
```
| Name   | Type                           | Description                                                 |
| :---:  | :---:                          | :---:                                                       |
| points | ```table<array<integer, 2>>``` | Table of coords pairs, example: { { x, y }, { x, y }, ... } |
| color  | ```Color```                    | Color for polygon                                           |

Render polygon on the screen.


### :computer: Window
#### :star: styles
```lua
local default = styles.Default
local fullscreen = styles.Fullscreen
```

#### <a name="window.is_open"></a> ```is_open```
```lua
window.is_open(): boolean
```

Returns true if the window is open, else false.
It is recommended to use as condition in loop for the correct termination.

---

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
window.capture(path: string[, x: integer, y: integer, w: integer, h: integer])
```
| Name  | Type         | Description                           |
| :---: | :---:        | :---:                                 |
| path  | ```string``` | Screenshot output path with file name |
| x     | ```integer``` | X coordinate, default = 0             |
| y     | ```integer``` | Y coordinate, default = 0             |
| w     | ```integer``` | Width, default = window width         |
| h     | ```integer``` | Height, default = window height       |

Takes a screenshot of the window and saves it (make sure the screen has not been updated by window.display).

---

#### <a name="window.get_size"></a> ```get_size```
```lua
window.get_size(): Vector2
```

Returns the window [size](#vector2.new.new).

---

#### <a name="window.set_size"></a> ```set_size```
```lua
window.set_size(width: integer, height: integer)
```
| Name   | Type         | Description       |
| :---:  | :---:        | :---:             |
| width  | ```integer``` | New window width  |
| height | ```integer``` | New window height |

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
window.set_pos(x: integer, y: integer)
```
| Name  | Type      | Description           |
| :---: | :---:     | :---:                 |
| x     | ```integer``` | New window x position |
| y     | ```integer``` | New window y position |

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
window.set_vsync(state: boolean)
```
| Name  | Type       | Description                               |
| :---: | :---:      | :---:                                     |
| state | ```boolean``` | Enable / disable vertical synchronization |

Enables or disables the window's vsync, enabled by default.

---

#### <a name="window.set_frame_limit"></a> ```set_frame_limit```
```lua
window.set_frame_limit(fps_max: integer)
```
| Name    | Type         | Description       |
| :---:   | :---:        | :---:             |
| fps_max | ```integer``` | Frames per second |

Sets the window frame limit.

---

#### <a name="window.sleep"></a> ```sleep```
```lua
window.sleep(milliseconds: integer)
```
| Name         | Type         | Description                    |
| :---:        | :---:        | :---:                          |
| milliseconds | ```integer``` | Time for delay in milliseconds |

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

---

#### <a name="window.set_style"></a> ```set_style```
```lua
window.set_style(style_code: styles)
```
| Name       | Type         | Description              |
| :---:      | :---:        | :---:                    |
| style_code | ```styles``` | style from 'styles' enum |

Sets the window a new style.


### <a name="Keyboard"></a> :wrench: Keyboard
#### :star: [keys](https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Keyboard.php)
```lua
local key_id = keys.W -- 'W' key on keyboard
```

#### <a name="keyboard.get_pressed"></a> ```get_pressed```
```lua
keyboard.get_pressed([return_symbol]): keys | char
```
| Name          | Type       | Description                                        |
| :---:         | :---:      | :---:                                              |
| return_symbol | ```boolean``` | If true then function return char, default = false |

Awaiting for pressing key and return [key](https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Keyboard.php) / char.

---

#### <a name="keyboard.is_pressed"></a> ```is_pressed```
```lua
keyboard.is_pressed(key_code: keys): boolean
```
| Name     | Type       | Description          |
| :---:    | :---:      | :---:                |
| key_code | ```keys``` | key from 'keys' enum |

Returns true if the key is pressed, else false.


### :mouse2: Mouse
#### :star: [buttons](https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Mouse.php#a4fb128be433f9aafe66bc0c605daaa90)
```lua
local button_id = buttons.Left -- left mouse button
```

#### <a name="mouse.get_pressed"></a> ```get_pressed```
```lua
mouse.get_pressed(): buttons
```

Awaiting for pressing button and return [button](https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Mouse.php#a4fb128be433f9aafe66bc0c605daaa90).

---

#### <a name="mouse.is_pressed"></a> ```is_pressed```
```lua
mouse.is_pressed(button_code: buttons): boolean
```
| Name        | Type          | Description                |
| :---:       | :---:         | :---:                      |
| button_code | ```buttons``` | button from 'buttons' enum |

Returns true if the button is pressed, else false.

---

#### <a name="mouse.is_scrolling_up"></a> ```is_scrolling_up```
```lua
mouse.is_scrolling_up(): boolean
```

Returns true if scrolling up, else false.

---

#### <a name="mouse.is_scrolling_down"></a> ```is_scrolling_down```
```lua
mouse.is_scrolling_down(): boolean
```

Returns true if scrolling down, else false.


### :video_game: Cursor
#### :star: [cursors](https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Cursor.php)
```lua
local cursor_type_id = cursors.Arrow -- 'Arrow' type
```

#### <a name="cursor.get_pos"></a> ```get_pos```
```lua
cursor.get_pos(): Vector2
```

Returns the cursor [position](#vector2.new).

---

#### <a name="cursor.in_window"></a> ```in_window```
```lua
cursor.in_window(): boolean
```

Returns true if cursor in window, else false.

---

#### <a name="cursor.is_bound"></a> ```is_bound```
```lua
cursor.is_bound(x: integer, y: integer, w: integer, h: integer)
```
| Name             | Type          | Description                                                            |
| :---:            | :---:         | :---:                                                                  |
| x                | ```integer```  | X position                                                             |
| y                | ```integer```  | Y position                                                             |
| w                | ```integer```  | Width                                                                  |
| h                | ```integer```  | Height                                                                 |

Returns true if cursor in bounds, else false.

---

#### <a name="cursor.change_type"></a> ```change_type```
```lua
cursor.change_type(cursor: cursors)
```
| Name    | Type          | Description                     |
| :---:   | :---:         | :---:                           |
| cursor  | ```cursors``` | cursor type from 'cursors' enum |

Changes the cursor state to the specified type.


### :file_folder: File

#### <a name="file.read"></a> ```read```
```lua
file.read(path: string[, line_number: integer]): table<string>
```
| Name        | Type         | Description                                          |
| :---:       | :---:        | :---:                                                |
| path        | ```string``` | Path to file                                         |
| line_number | ```integer``` | Number of the line to be read, default read all file |

Reads the file and writes it to the string table.

---

#### <a name="file.write"></a> ```write```
```lua
file.write(path: string, content: table<string>[, is_rewrite: boolean])
file.write(path: string, content: string[, is_rewrite: boolean])
```
| Name       | Type                              | Description                                                                |
| :---:      | :---:                             | :---:                                                                      |
| path       | ```string```                      | Path to file                                                               |
| content    | ```table<string>``` / ```string```| Content that will be written to a file                                     |
| is_rewrite | ```boolean```                        | If the value is true, file will be cleared before writing, default = false |

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
file.exists(path: string): boolean
```
| Name  | Type         | Description                          |
| :---: | :---:        | :---:                                |
| path  | ```string``` | Path to file or folder with its name |

Returns true if the file is found, else false.

---

#### <a name="file.line_count"></a> ```line_count```
```lua
file.line_count(path: string): integer
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
cmath.rand_int(min: integer, max: integer): integer
```
| Name  | Type     | Description          |
| :---: | :---:    | :---:                |
| min   | ```integer```| Minimum random value |
| max   | ```integer```| Maximum random value |

Returns the random integer number [min, max].

---

#### <a name="cmath.rand_double"></a> ```rand_double```
```lua
cmath.rand_double(min: number, max: number): number
```
| Name  | Type        | Description          |
| :---: | :---:       | :---:                |
| min   | ```number```| Minimum random value |
| max   | ```number```| Maximum random value |

Returns the random point floating number [min, max].

---

#### <a name="cmath.lerp"></a> ```lerp```
```lua
cmath.lerp(start_v: number, end_v: number, time: number): number
```
| Name    | Type       | Description |
| :---:   | :---:      | :---:       |
| start_v | ```number```| Start value |
| end_v   | ```number```| End value   |
| time    | ```number```| Step value  |

Returns the linear interpolation.

---

#### <a name="cmath.clamp"></a> ```clamp```
```lua
cmath.clamp(number: number, lower: number, upper: number): number
```
| Name   | Type       | Description    |
| :---:  | :---:      | :---:          |
| number | ```number```| Value to clamp |
| lower  | ```number```| Lower bound    |
| upper  | ```number```| Upper bound    |

Returns the clumped value.

---

#### <a name="cmath.round"></a> ```round```
```lua
cmath.round(number: number): integer
```
| Name   | Type       | Description       |
| :---:  | :---:      | :---:             |
| number | ```number```| Value to rounding |

Returns the rounded value.


### :mag: GlobalVars
#### <a name="globalvars.get_executable_path"></a> ```get_executable_path```
```lua
globalvars.get_executable_path(): string
```

Returns the path of executable.

---

#### <a name="globalvars.get_os_name"></a> ```get_os_name```
```lua
globalvars.get_os_name(): string
```

Returns the os name ("Windows", "Linux", "Unknown").

---

#### <a name="globalvars.get_args"></a> ```get_args```
```lua
globalvars.get_args(): table<string>
```

Returns a list of arguments starting after the argument that is the main script.


### :satellite: Network
#### <a name="network.bind"></a> ```bind```
```lua
network.bind(port: integer, socket_type: char)
```
| Name         | Type       | Description                                  |
| :---:        | :---:      | :---:                                        |
| port         | ```integer```  | Valid port                                   |
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
network.send(ip: string, port: integer, packet: table)
network.send(packet: table)
```
| Name   | Type        | Description                                                    |
| :---:  | :---:       | :---:                                                          |
| ip     | ```string```| Recipient's IP address                                         |
| port   | ```integer```   | Recipient's port                                               |
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
Sound:new(path: string, volume: integer[, is_repeat: boolean]): Sound&
```
| Name      | Type         | Description                                        |
| :---:     | :---:        | :---:                                              |
| path      | ```string``` | Path to sound file [WAV, OGG, FLAC]                |
| volume    | ```integer``` | Volume of sound [0 - 100]                          |
| is_repeat | ```boolean```   | If true then sound will be looped, default = false |

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
sound_object:play([is_reset: boolean])
```
| Name     | Type        | Description                                                                      |
| :---:    | :---:       | :---:                                                                            |
| is_reset | ```boolean```  | If true, the sound will be played every time from the beginning, default = false |

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
sound_object:set_volume(volume: integer)
```
| Name   | Type         | Description               |
| :---:  | :---:        | :---:                     |
| volume | ```integer``` | Volume of sound [0 - 100] |

Sets the [sound](#sound.new) a new volume.

---

#### <a name="sound.get_volume"></a> ```get_volume```
```lua
sound_object:get_volume(): integer
```

Returns the [sound](#sound.new) volume.

---

#### <a name="sound.set_loop"></a> ```set_loop```
```lua
sound_object:set_loop(is_repeat: boolean)
```
| Name      | Type        | Description                           |
| :---:     | :---:       | :---:                                 |
| is_repeat | ```boolean```  | If true then the sound will be looped |

Sets the [sound](#sound.new) a new loop.

---

#### <a name="sound.get_loop"></a> ```get_loop```
```lua
sound_object:get_loop(): boolean
```

Returns true if the sound is looped, else false.

---

#### <a name="sound.is_play"></a> ```is_play```
```lua
sound_object:is_play(): boolean
```

Returns true if the sound is playing, else false.


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
Vector2:new(x: number, y: number): Vector2&
```
| Name  | Type         | Description  |
| :---: | :---:        | :---:        |
| x     | ```number``` | X coordinate |
| y     | ```number``` | Y coordinate |

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
Font:new(name: string, size: integer[, style: string]): Font&
```
| Name  | Type         | Description                                                                                                                     |
| :---: | :---:        | :---:                                                                                                                           |
| name  | ```string``` | Name of font, with file extension                                                                                               |
| size  | ```integer``` | Size of font                                                                                                                    |
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
font_object:get_size(): integer
```

Returns the font size.

---

#### <a name="font.get_style"></a> ```get_style```
```lua
font_object:get_style(): string
```

Returns the font style, example: "r".

---

#### <a name="font.get_glyph"></a> ```get_glyph```
```lua
font_object:get_glyph(symbol: char): Vector2
```
```
| Name   | Type       | Description                                 |
| :---:  | :---:      | :---:                                       |
| symbol | ```char``` | The character whose size will be calculated |

Returns the measure of the font symbol.


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
Color:new(r: integer, g: integer, b: integer[, a: integer]): Color&
Color:new(hex: string): Color&
```
| Name  | Type         | Description                  |
| :---: | :---:        | :---:                        |
| r     | ```integer```    | Red [0 - 255]                |
| g     | ```integer```    | Green [0 - 255]              |
| b     | ```integer```    | Blue [0 - 255]               |
| a     | ```integer```    | Alpha [0 - 255], default 255 |

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
color_object:unpack(color: Color): integer, integer, integer, integer
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
Sprite:new(path: string, w: integer, h: integer[, t_x: integer, t_y: integer, t_w: integer, t_h: integer]): Sprite&
```
| Name  | Type         | Description                                     |
| :---: | :---:        | :---:                                           |
| path  | ```string``` | Image location directory                        |
| w     | ```integer```    | Width of image                                  |
| h     | ```integer```    | Height of image                                 |
| t_x   | ```integer``` | X coordinate of areas in the image, default = 0 |
| t_y   | ```integer``` | Y coordinate of areas in the image, default = 0 |
| t_w   | ```integer``` | Width of areas in the image, default = w        |
| t_h   | ```integer``` | Height of areas in the image, default = h       |

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
sprite_object:set_pos(x: integer, y: integer)
```
| Name  | Type      | Description                 |
| :---: | :---:     | :---:                       |
| x     | ```integer``` | New x coordinate for sprite |
| y     | ```integer``` | New y coordinate for sprite |

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
sprite_object:set_rotation(angle: number)
```
| Name  | Type         | Description                   |
| :---: | :---:        | :---:                         |
| angle | ```number``` | New rotation angle for sprite |

Sets a new rotation angle for the sprite.

---

#### <a name="sprite.get_rotation"></a> ```get_rotation```
```lua
sprite_object:get_rotation(): number
```

Returns the rotation angle of the sprite.

---

#### <a name="sprite.set_scale"></a> ```set_scale```
```lua
sprite_object:set_scale(x_factor: number, y_factor: number)
```
| Name     | Type         | Description                   |
| :---:    | :---:        | :---:                         |
| x_factor | ```number``` | New x scale factor for sprite |
| y_factor | ```number``` | New y scale factor for sprite |

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
sprite_object:set_origin(x: number, y: number)
```
| Name  | Type         | Description             |
| :---: | :---:        | :---:                   |
| x     | ```number``` | New x origin for sprite |
| y     | ```number``` | New y origin for sprite |

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
sprite_object:set_size(w: integer, h: integer)
```
| Name  | Type      | Description                  |
| :---: | :---:     | :---:                        |
| w     | ```integer``` | New width for sprite         |
| h     | ```integer``` | New heigth origin for sprite |

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
sprite_object:scale(x_factor: number, y_factor: number)
```
| Name     | Type         | Description               |
| :---:    | :---:        | :---:                     |
| x_factor | ```number``` | X scale factor for sprite |
| y_factor | ```number``` | Y scale factor for sprite |

Scales the sprite.

---

#### <a name="sprite.rotate"></a> ```rotate```
```lua
sprite_object:rotate(angle: number)
```
| Name  | Type         | Description                |
| :---: | :---:        | :---:                      |
| angle | ```number``` | Rotations angle for sprite |

Rotates the sprite.

---

#### <a name="sprite.move"></a> ```move```
```lua
sprite_object:move(x_offset: number, y_offset: number)
```
| Name     | Type         | Description                       |
| :---:    | :---:        | :---:                             |
| x_offset | ```number``` | X offset of coordinate for sprite |
| y_offset | ```number``` | Y offset of coordinate for sprite |

Moves the sprite.


### :camera: View
```lua
tostring(view)   -- "{ x: x, y: y, w: w, h: h }"
view == view     -- true
```

#### <a name="view.new"></a> ```new```
```lua
View:new([x: integer, y: integer, w: integer, h: integer]): View&
```
| Name   | Type        | Description             |
| :---:  | :---:       | :---:                   |
| x      | ```integer```| X position, default = 0 |
| y      | ```integer```| Y position, default = 0 |
| w      | ```integer```| Width, default = 0      |
| h      | ```integer```| Height, default = 0     |

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
view_object:set_port(x: integer, y: integer, w: integer, h: integer)
```
| Name  | Type        | Description |
| :---: | :---:       | :---:       |
| x     | ```integer```| X position  |
| y     | ```integer```| Y position  |
| w     | ```integer```| Width       |
| h     | ```integer```| Height      |

Sets the view a new view port.

---

#### <a name="view.set_center"></a> ```set_center```
```lua
view_object:set_center(x: integer, y: integer)
```
| Name  | Type        | Description |
| :---: | :---:       | :---:       |
| x     | ```integer```| X position  |
| y     | ```integer```| Y position  |

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
view_object:set_size(w: integer, h: integer)
```
| Name  | Type         | Description |
| :---: | :---:        | :---:       |
| w     | ```integer``` | Width       |
| h     | ```integer``` | Height      |

Sets the view a new size.

---

#### <a name="view.set_zoom"></a> ```set_zoom```
```lua
view_object:set_zoom(zoom_factor: number)
```
| Name        | Type        | Description |
| :---:       | :---:       | :---:       |
| zoom_factor | ```number``` | Zoom degree |

Zooms view.

---

#### <a name="view.get_rotation"></a> ```get_rotation```
```lua
view_object:get_rotation(): number
```

Returns a view rotation.

---

#### <a name="view.set_rotation"></a> ```set_rotation```
```lua
view_object:set_rotation(angle: number)
```
| Name  | Type        | Description              |
| :---: | :---:       | :---:                    |
| angle | ```number``` | Rotation angle [0 - 360] |

Sets the view a new rotation angle.
