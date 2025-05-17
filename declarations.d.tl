global record render
    text: function(number, number, Font, string, Color)
    sprite: function(Sprite)
    measure_text: function(Font, string): Vector2
    rectangle: function(number, number, number, number, Color, ?number)
    outline_rectangle: function(number, number, number, number, number, Color, ?number)
    circle: function(number, number, number, Color, ?number, ?Color)
    line: function(number, number, number, number, number, Color)
    polygon: function({{number}}, Color)
end

global record window
	is_open: function(): boolean
    display: function()
    clear: function(?Color)
	close: function()
	capture: function(string, ?number, ?number, ?number, ?number)
	get_size: function(): Vector2
	set_size: function(number, number)
	get_pos: function(): Vector2
	set_pos: function(number, number)
	set_title: function(string)
	set_vsync: function(boolean)
	set_frame_limit: function(number)
	sleep: function(number)
	await: function()
	set_icon: function(Sprite)
	set_style: function(integer)
end

global record keyboard
    get_pressed: function(?boolean): integer | string
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

global record cursor_type
	Arrow: integer
	ArrowWait: integer
	Wait: integer
	Text: integer
	Hand: integer
	SizeHorizontal: integer
	SizeVertical: integer
	SizeTopLeftBottomRight: integer
	SizeBottomLeftTopRight: integer
	SizeLeft: integer
	SizeRight: integer
	SizeTop: integer
	SizeBottom: integer
	SizeTopLeft: integer
	SizeTopRight: integer
	SizeBottomLeft: integer
	SizeBottomRight: integer
	SizeAll: integer
	Cross: integer
	Help: integer
	NotAllowed: integer
end

global record cursor
	get_pos: function(): Vector2
	in_window: function(): boolean
	is_bound: function(number, number, number, number): boolean
	change_type: function(integer)
end

global record file
	read: function(string, ?number): {string}
	write: function(string, {string}, ?boolean)
	write: function(string, string, ?boolean)
	copy: function(string, ?string)
	create: function(string)
	remove: function(string)
	exists: function(string): boolean
	line_count: function(string): integer
	clear: function(string)
	rename: function(string, string)
	get_list: function(string): {string}
end

global record cmath
    rand_int: function(number, number): integer
	rand_double: function(number, number): number
	lerp: function(number, number, number): number
	clamp: function(number, number, number): number
	round: function(number): integer
end

global record globalvars
    get_executable_path: function(): string
	get_os_name: function(): string
	get_args: function(): { string }
end

global record network
    bind: function(number, string)
	unbind: function()
	send: function(string, number, table)
	send: function(table)
	receive: function(): table
	get_local_address: function(): string
end


global type Sound = record
    new: function<Self>(Self, string, number, ?boolean): Self
    copy: function<Self>(Self): Self
    play: function<Self>(Self, ?boolean)
	stop: function<Self>(Self)
	get_path: function<Self>(Self): string
	set_volume: function<Self>(Self, number)
	get_volume: function<Self>(Self): integer
	set_loop: function<Self>(Self, boolean)
	get_loop: function<Self>(Self): boolean
	is_play: function<Self>(Self): boolean
end

global type Vector2 = record
    x: number
    y: number
    new: function<Self>(Self, number, number): Vector2
    copy: function<Self>(Self): Vector2
	metamethod __add: function<Self>(Self, Vector2 | number): Self
	metamethod __sub: function<Self>(Self, Vector2 | number): Self
	metamethod __mul: function<Self>(Self, Vector2 | number): Self
	metamethod __div: function<Self>(Self, Vector2 | number): Self
	metamethod __len: function<Self>(Self): integer
	metamethod __index: function<Self>(Self, number): number
	metamethod __newindex: function<Self>(Self, number)
end

global type Font = record
    new: function<Self>(Self, string, number, ?string): Self
    copy: function<Self>(Self): Self
    get_family: function<Self>(Self): string
    get_size: function<Self>(Self): integer
    get_style: function<Self>(Self): string
    get_glyph: function<Self>(Self, string): Vector2
end

global type Color = record
    r: integer
    g: integer
    b: integer
    a: integer
    new: function<Self>(Self, number, number, number, ?number): Self
    new: function<Self>(Self, string): Self
    copy: function<Self>(Self): Self
    unpack: function<Self>(Self): integer, integer, integer, integer
    to_hex: function<Self>(Self): string
end

global type Sprite = record
    new: function<Self>(Self, string, number, number, ?number, ?number, ?number, ?number): Self
    copy: function<Self>(Self): Self
    set_color: function<Self>(Self, Color)
    get_color: function<Self>(Self): Color
    set_pos: function<Self>(Self, number, number)
    get_pos: function<Self>(Self): Vector2
    set_rotation: function<Self>(Self, number)
    get_rotation: function<Self>(Self): number
    set_scale: function<Self>(Self, number, number)
    get_scale: function<Self>(Self): Vector2
    set_origin: function<Self>(Self, number, number)
    get_origin: function<Self>(Self): Vector2
    set_size: function<Self>(Self, number, number)
    get_size: function<Self>(Self): Vector2
    scale: function<Self>(Self, number, number)
    rotate: function<Self>(Self, number)
    move: function<Self>(Self, number, number)
end

global type View = record
	new: function<Self>(Self, ?number, ?number, ?number, ?number): Self
	copy: function<Self>(Self): Self
	active: function<Self>(Self)
	set_port: function<Self>(Self, number, number, number, number)
	set_center: function<Self>(Self, number, number)
	get_size: function<Self>(Self): Vector2
	set_size: function<Self>(Self, number, number)
	set_zoom: function<Self>(Self, number)
	get_rotation: function<Self>(Self): integer
	set_rotation: function<Self>(Self, number)
end