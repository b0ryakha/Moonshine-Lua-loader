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
end

global record keyboard
    get_pressed: function(?boolean): number | string
	is_pressed: function(number): boolean
end

global record key
	A: number
	B: number
	C: number
	D: number
	E: number
	F: number
	G: number
	H: number
	I: number
	J: number
	K: number
	L: number
	M: number
	N: number
	O: number
	P: number
	Q: number
	R: number
	S: number
	T: number
	U: number
	V: number
	W: number
	X: number
	Y: number
	Z: number
	Num0: number
	Num1: number
	Num2: number
	Num3: number
	Num4: number
	Num5: number
	Num6: number
	Num7: number
	Num8: number
	Num9: number
	Escape: number
	LControl: number
	LShift: number
	LAlt: number
	LSystem: number
	RControl: number
	RShift: number
	RAlt: number
	RSystem: number
	Menu: number
	LBracket: number
	RBracket: number
	Semicolon: number
	Comma: number
	Period: number
	Quote: number
	Slash: number
	Backslash: number
	Tilde: number
	Equal: number
	Hyphen: number
	Space: number
	Enter: number
	Backspace: number
	Tab: number
	PageUp: number
	PageDown: number
	End: number
	Home: number
	Insert: number
	Delete: number
	Add: number
	Subtract: number
	Multiply: number
	Divide: number
	Left: number
	Right: number
	Up: number
	Down: number
	Numpad1: number
	Numpad2: number
	Numpad3: number
	Numpad0: number
	Numpad4: number
	Numpad5: number
	Numpad6: number
	Numpad7: number
	Numpad8: number
	Numpad9: number
	F1: number
	F2: number
	F3: number
	F4: number
	F5: number
	F6: number
	F7: number
	F8: number
	F9: number
	F10: number
	F11: number
	F12: number
	F13: number
	F14: number
	F15: number
	Pause: number
end

global record mouse
    get_pressed: function(): number
	is_pressed: function(number): boolean
	is_scrolling_up: function(): boolean
	is_scrolling_down: function(): boolean
end

global record button
	Left: number
	Right: number
	Middle: number
	XButton1: number
	XButton2: number
end

global record cursor_type
	Arrow: number
	ArrowWait: number
	Wait: number
	Text: number
	Hand: number
	SizeHorizontal: number
	SizeVertical: number
	SizeTopLeftBottomRight: number
	SizeBottomLeftTopRight: number
	SizeLeft: number
	SizeRight: number
	SizeTop: number
	SizeBottom: number
	SizeTopLeft: number
	SizeTopRight: number
	SizeBottomLeft: number
	SizeBottomRight: number
	SizeAll: number
	Cross: number
	Help: number
	NotAllowed: number
end

global record cursor
	get_pos: function(): Vector2
	in_window: function(): boolean
	is_bound: function(number, number, number, number): boolean
	change_type: function(number)
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
	round: function(number): number
end

global record globalvars
    get_executable_path: function(): string
	get_os_name: function(): string
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