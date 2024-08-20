global record render
    text: function(integer, integer, Font, string, Color)
    sprite: function(Sprite)
    measure_text: function(Font, string): Vector2
    rectangle: function(integer, integer, integer, integer, Color, integer | nil)
    circle: function(integer, integer, integer, Color, number | nil, Color | nil)
    line: function(integer, integer, integer, integer, number, Color)
    polygon: function({{integer}}, Color)
end

global record window
    display: function()
    clear: function(Color | nil)
	close: function()
	capture: function(string, integer | nil, integer | nil, integer | nil, integer | nil)
	get_size: function(): Vector2
	set_size: function(integer, integer)
	get_pos: function(): Vector2
	set_pos: function(integer, integer)
	set_title: function(string)
	set_vsync: function(boolean)
	set_frame_limit: function(integer)
	sleep: function(integer)
	await: function()
	set_icon: function(Sprite)
end

global record keyboard
    get_pressed: function(boolean | nil): integer | string
	is_pressed: function(integer): boolean
end

global record key
	A: integer
	B: integer
	C: integer
	D: integer
	E: integer
	F: integer
	G: integer
	H: integer
	I: integer
	J: integer
	K: integer
	L: integer
	M: integer
	N: integer
	O: integer
	P: integer
	Q: integer
	R: integer
	S: integer
	T: integer
	U: integer
	V: integer
	W: integer
	X: integer
	Y: integer
	Z: integer
	Num0: integer
	Num1: integer
	Num2: integer
	Num3: integer
	Num4: integer
	Num5: integer
	Num6: integer
	Num7: integer
	Num8: integer
	Num9: integer
	Escape: integer
	LControl: integer
	LShift: integer
	LAlt: integer
	LSystem: integer
	RControl: integer
	RShift: integer
	RAlt: integer
	RSystem: integer
	Menu: integer
	LBracket: integer
	RBracket: integer
	Semicolon: integer
	Comma: integer
	Period: integer
	Quote: integer
	Slash: integer
	Backslash: integer
	Tilde: integer
	Equal: integer
	Hyphen: integer
	Space: integer
	Enter: integer
	Backspace: integer
	Tab: integer
	PageUp: integer
	PageDown: integer
	End: integer
	Home: integer
	Insert: integer
	Delete: integer
	Add: integer
	Subtract: integer
	Multiply: integer
	Divide: integer
	Left: integer
	Right: integer
	Up: integer
	Down: integer
	Numpad1: integer
	Numpad2: integer
	Numpad3: integer
	Numpad0: integer
	Numpad4: integer
	Numpad5: integer
	Numpad6: integer
	Numpad7: integer
	Numpad8: integer
	Numpad9: integer
	F1: integer
	F2: integer
	F3: integer
	F4: integer
	F5: integer
	F6: integer
	F7: integer
	F8: integer
	F9: integer
	F10: integer
	F11: integer
	F12: integer
	F13: integer
	F14: integer
	F15: integer
	Pause: integer
end

global record mouse
    get_pressed: function(): integer
	is_pressed: function(integer): boolean
	is_scrolling_up: function(): boolean
	is_scrolling_down: function(): boolean
end

global record button
	Left: integer
	Right: integer
	Middle: integer
	XButton1: integer
	XButton2: integer
end

global record cursor
	get_pos: function(): Vector2
	in_window: function(): boolean
	is_bound: function(integer, integer, integer, integer)
end

global record file
	read: function(string, integer | nil): {string}
	write: function(string, {string}, boolean | nil)
	write: function(string, string, boolean | nil)
	copy: function(string, string | nil)
	create: function(string)
	remove: function(string)
	exists: function(string): boolean
	line_count: function(string): integer
	clear: function(string)
	rename: function(string, string)
	get_list: function(string): {string}
end

global record cmath
    rand_int: function(integer, integer): integer
	rand_double: function(number, number): number
	lerp: function(number, number, number): number
	clamp: function(number, number, number): number
	round: function(number): integer
end

global record globalvars
    get_executable_path: function(): string
	get_os_name: function(): string
end

global record network
    bind: function(integer, string)
	unbind: function()
	send: function(string, integer, table)
	send: function(table)
	receive: function(): table
	get_local_address: function(): string
end


global type Sound = record
    new: function(Sound, string, integer, boolean | nil): Sound
    copy: function(Sound): Sound
    play: function(Sound, boolean | nil)
	stop: function(Sound)
	get_path: function(Sound): string
	set_volume: function(Sound, integer)
	get_volume: function(Sound): integer
	set_loop: function(Sound, boolean)
	get_loop: function(Sound): boolean
	is_play: function(Sound): boolean
end

global type Vector2 = record
    x: number
    y: number
    new: function(Vector2, number, number): Vector2
    copy: function(Vector2): Vector2
	metamethod __add: function(Vector2, Vector2 | number): Vector2
	metamethod __sub: function(Vector2, Vector2 | number): Vector2
	metamethod __mul: function(Vector2, Vector2 | number): Vector2
	metamethod __div: function(Vector2, Vector2 | number): Vector2
	metamethod __len: function(Vector2): integer
	metamethod __index: function(Vector2, number): number
	metamethod __newindex: function(Vector2, integer)
end

global type Font = record
    new: function(Font, string, number, string | nil): Font
    copy: function(Font): Font
    get_family: function(Font): string
    get_size: function(Font): integer
    get_style: function(Font): string
end

global type Color = record
    r: integer
    g: integer
    b: integer
    a: integer
    new: function(Color, integer, integer, integer, integer | nil): Color
    new: function(Color, string): Color
    copy: function(Color): Color
    unpack: function(Color): integer, integer, integer, integer
    to_hex: function(Color): string
end

global type Sprite = record
    new: function(Sprite, string, integer, integer, integer | nil, integer | nil, integer | nil, integer | nil): Sprite
    copy: function(Sprite): Sprite
    set_color: function(Sprite, Color)
    get_color: function(Sprite): Color
    set_pos: function(Sprite, integer, integer)
    get_pos: function(Sprite): Vector2
    set_rotation: function(Sprite, number)
    get_rotation: function(Sprite): number
    set_scale: function(Sprite, number, number)
    get_scale: function(Sprite): Vector2
    set_origin: function(Sprite, number, number)
    get_origin: function(Sprite): Vector2
    set_size: function(Sprite, integer, integer)
    get_size: function(Sprite): Vector2
    scale: function(Sprite, number, number)
    rotate: function(Sprite, number)
    move: function(Sprite, number, number)
end

global type View = record
	new: function(View, integer | nil, integer | nil, integer | nil, integer | nil): View
	copy: function(View): View
	active: function(View)
	set_port: function(View, integer, integer, integer, integer)
	set_center: function(View, integer, integer)
	get_size: function(View): Vector2
	set_size: function(View, integer, integer)
	set_zoom: function(View, number)
	get_rotation: function(View): number
	set_rotation: function(View, number)
end