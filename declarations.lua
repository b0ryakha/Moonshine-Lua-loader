---@meta

---@class (exact) Vector2
---@field x number
---@field y number
---@operator add(Vector2 | number): Vector2
---@operator sub(Vector2 | number): Vector2
---@operator mul(Vector2 | number): Vector2
---@operator div(Vector2 | number): Vector2
---@operator len: integer
Vector2 = {}

---@param x number
---@param y number
---@return Vector2
function Vector2:new(x, y) end

---@return Vector2
function Vector2:copy() end


---@class (exact) Color
---@field r integer
---@field g integer
---@field b integer
---@field a integer
Color = {}

---@param r integer
---@param g integer
---@param b integer
---@param a? integer default = 255
---@return Color
function Color:new(r, g, b, a) end

---@param hex string
---@return Color
function Color:new(hex) end

---@return Color
function Color:copy() end

---@return integer, integer, integer, integer
function Color:unpack() end

---@return string
function Color:to_hex() end


---@class (exact) Font
Font = {}

---@return Font
---@param name string
---@param size integer
---@param style? string default = "r"
function Font:new(name, size, style) end

---@return Font
function Font:copy() end

---@return string
function Font:get_family() end

---@return integer
function Font:get_size() end

---@return string
function Font:get_style() end

---@param symbol string -> symbol
---@return Vector2
function Font:get_bounds(symbol) end


---@class (exact) Sprite
Sprite = {}

---@param path string
---@param w integer
---@param h integer
---@param t_x? integer default = nil
---@param t_y? integer default = nil
---@param t_w? integer default = w
---@param t_h? integer default = h
---@return Sprite
function Sprite:new(path, w, h, t_x, t_y, t_w, t_h) end

---@return Sprite
function Sprite:copy() end

---@param color Color
function Sprite:set_color(color) end

---@return Color
function Sprite:get_color() end

---@param x integer
---@param y integer
function Sprite:set_pos(x, y) end

---@return Vector2
function Sprite:get_pos() end

---@param angle number [0 - 360]
function Sprite:set_rotation(angle) end

---@return number
function Sprite:get_rotation() end

---@param x_factor number
---@param y_factor number
function Sprite:set_scale(x_factor, y_factor) end

---@return Vector2
function Sprite:get_scale() end

---@param x number
---@param y number
function Sprite:set_origin(x, y) end

---@return Vector2
function Sprite:get_origin() end

---@param w integer
---@param h integer
function Sprite:set_size(w, h) end

---@return Vector2
function Sprite:get_size() end

---@param x_factor number
---@param y_factor number
function Sprite:scale(x_factor, y_factor) end

---@param angle number [0 - 360]
function Sprite:rotate(angle) end

---@param x_offset number
---@param y_offset number
function Sprite:move(x_offset, y_offset) end


---@class (exact) Sound
Sound = {}

---@return Sound
---@param path string
---@param volume integer [0 - 100]
---@param is_repeat? boolean default = false
function Sound:new(path, volume, is_repeat) end

---@return Sound
function Sound:copy() end

---@param is_reset? boolean default = false
function Sound:play(is_reset) end

function Sound:stop() end

---@return string
function Sound:get_path() end

---@param volume integer [0 - 100]
function Sound:set_volume(volume) end

---@return integer
function Sound:get_volume() end

---@param is_repeat boolean
function Sound:set_loop(is_repeat) end

---@return boolean
function Sound:get_loop() end

---@return boolean
function Sound:is_play() end


---@class (exact) View
View = {}

---@return View
---@param x? integer default = nil
---@param y? integer default = nil
---@param w? integer default = nil
---@param h? integer default = nil
function View:new(x, y, w, h) end

---@return View
function View:copy() end

function View:active() end

---@param x integer
---@param y integer
---@param w integer
---@param h integer
function View:set_port(x, y, w, h) end

---@param x integer
---@param y integer
function View:set_center(x, y) end

---@return Vector2
function View:get_size() end

---@param w integer
---@param h integer
function View:set_size(w, h) end

---@param zoom_factor number
function View:set_zoom(zoom_factor) end

---@return integer
function View:get_rotation() end

---@param angle number [0 - 360]
function View:set_rotation(angle) end


window = {}

---@enum styles
styles = { Default = nil, Fullscreen = nil }

---@param is_visible boolean
function window.set_visible(is_visible) end

---@return boolean
function window.is_open() end

function window.display() end

---@param color? Color default = Color:new(0, 0, 0) aka black
function window.clear(color) end

function window.close() end

---@param path string
---@param x? integer default = nil
---@param y? integer default = nil
---@param w? integer default = window.get_size().x
---@param h? integer default = window.get_size().y
function window.capture(path, x, y, w, h) end

---@return Vector2
function window.get_size() end

---@param w integer
---@param h integer
function window.set_size(w, h) end

---@return Vector2
function window.get_pos() end

---@param x integer
---@param y integer
function window.set_pos(x, y) end

---@param title string
function window.set_title(title) end

---@param state boolean
function window.set_vsync(state) end

---@param fps_max integer
function window.set_frame_limit(fps_max) end

---@param milliseconds integer
function window.sleep(milliseconds) end

function window.await() end

---@param icon Sprite
function window.set_icon(icon) end

---@param style_code styles
function window.set_style(style_code) end


render = {}

---@param x number
---@param y number
---@param font Font
---@param text string
---@param color Color
function render.text(x, y, font, text, color) end

---@param sprite Sprite
function render.sprite(sprite) end

---@param font Font
---@param text string
---@return Vector2
function render.measure_text(font, text) end

---@param x number
---@param y number
---@param width number
---@param height number
---@param color Color
---@param rounding? number [0 - 100], default = 0
function render.rectangle(x, y, width, height, color, rounding) end

---@param x number
---@param y number
---@param width number
---@param height number
---@param thickness number
---@param color Color
---@param rounding? number [0 - 100], default = 0
function render.outline_rectangle(x, y, width, height, thickness, color, rounding) end

---@param x number
---@param y number
---@param width number
---@param height number
---@param color1 Color
---@param color2 Color
---@param color3 Color
---@param color4 Color
function render.gradient(x, y, width, height, color1, color2, color3, color4) end

---@param x number
---@param y number
---@param radius number
---@param color Color
---@param thickness? number default = nil
---@param outlineColor? Color default = nil
function render.circle(x, y, radius, color, thickness, outlineColor) end

---@param x1 number
---@param y1 number
---@param x2 number
---@param y2 number
---@param thickness number
---@param color Color
function render.line(x1, y1, x2, y2, thickness, color) end

---@param points table<number, number[]>
---@param color Color
function render.polygon(points, color) end


globalvars = {}

---@return string
function globalvars.get_executable_path() end

---@return string
function globalvars.get_os_name() end

---@return table<integer, string>
function globalvars.get_args() end


cmath = {}

---@param min integer
---@param max integer
---@return integer
function cmath.rand_int(min, max) end

---@param min number
---@param max number
---@return number
function cmath.rand_double(min, max) end

---@param start_v number
---@param end_v number
---@param time number
---@return number
function cmath.lerp(start_v, end_v, time) end

---@return number
---@param number number
---@param lower number
---@param upper number
function cmath.clamp(number, lower, upper) end

---@param number number
---@return integer
function cmath.round(number) end


file = {}

---@return table<integer, string>
---@param path string
---@param line_number? integer default = file.line_count(path) aka all
function file.read(path, line_number) end

---@param path string
---@param content table<integer, string>
---@param is_rewrite? boolean default = false
function file.write(path, content, is_rewrite) end

---@param path string
---@param content string
---@param is_rewrite? boolean default = false
function file.write(path, content, is_rewrite) end

---@param input string
---@param output? string default = input .. " (copy)"
function file.copy(input, output) end

---@param path string to file | folder
function file.create(path) end

---@param path string to file | folder
function file.remove(path) end

---@param path string to file | folder
---@return boolean
function file.exists(path) end

---@param path string to file
---@return integer
function file.line_count(path) end

---@param path string to file
function file.clear(path) end

---@param path string to file | folder
---@param new_name string
function file.rename(path, new_name) end

---@param path string to folder
---@return table<integer, string>
function file.get_list(path) end


network = {}

---@param port integer
---@param socket_type 's' | 'c'
function network.bind(port, socket_type) end

function network.unbind() end

---Sends data to a specific client.
---@param ip string
---@param port integer
---@param packet table<integer, number | string | boolean>
function network.send(ip, port, packet) end

---Sends data to all binded clients.
---@param packet table<integer, number | string | boolean>
function network.send(packet) end

---@return table<integer, number | string | boolean> | nil
function network.receive() end

---@return string
function network.get_local_address() end


cursor = {}

---@enum cursors
cursors = {
	Arrow = nil,
	ArrowWait = nil,
	Wait = nil,
	Text = nil,
	Hand = nil,
	SizeHorizontal = nil,
	SizeVertical = nil,
	SizeTopLeftBottomRight = nil,
	SizeBottomLeftTopRight = nil,
	SizeLeft = nil,
	SizeRight = nil,
	SizeTop = nil,
	SizeBottom = nil,
	SizeTopLeft = nil,
	SizeTopRight = nil,
	SizeBottomLeft = nil,
	SizeBottomRight = nil,
	SizeAll = nil,
	Cross = nil,
	Help = nil,
	NotAllowed = nil
}

---@return Vector2
function cursor.get_pos() end

---@return boolean
function cursor.in_window() end

---@param x integer
---@param y integer
---@param w integer
---@param h integer
---@return boolean
function cursor.is_bound(x, y, w, h) end

---@param cursor cursors
function cursor.change_type(cursor) end


keyboard = {}

---@enum keys
keys = {
	A = nil,
	B = nil,
	C = nil,
	D = nil,
	E = nil,
	F = nil,
	G = nil,
	H = nil,
	I = nil,
	J = nil,
	K = nil,
	L = nil,
	M = nil,
	N = nil,
	O = nil,
	P = nil,
	Q = nil,
	R = nil,
	S = nil,
	T = nil,
	U = nil,
	V = nil,
	W = nil,
	X = nil,
	Y = nil,
	Z = nil,
	Num0 = nil,
	Num1 = nil,
	Num2 = nil,
	Num3 = nil,
	Num4 = nil,
	Num5 = nil,
	Num6 = nil,
	Num7 = nil,
	Num8 = nil,
	Num9 = nil,
	Escape = nil,
	LControl = nil,
	LShift = nil,
	LAlt = nil,
	LSystem = nil,
	RControl = nil,
	RShift = nil,
	RAlt = nil,
	RSystem = nil,
	Menu = nil,
	LBracket = nil,
	RBracket = nil,
	Semicolon = nil,
	Comma = nil,
	Period = nil,
	Quote = nil,
	Slash = nil,
	Backslash = nil,
	Tilde = nil,
	Equal = nil,
	Hyphen = nil,
	Space = nil,
	Enter = nil,
	Backspace = nil,
	Tab = nil,
	PageUp = nil,
	PageDown = nil,
	End = nil,
	Home = nil,
	Insert = nil,
	Delete = nil,
	Add = nil,
	Subtract = nil,
	Multiply = nil,
	Divide = nil,
	Left = nil,
	Right = nil,
	Up = nil,
	Down = nil,
	Numpad1 = nil,
	Numpad2 = nil,
	Numpad3 = nil,
	Numpad0 = nil,
	Numpad4 = nil,
	Numpad5 = nil,
	Numpad6 = nil,
	Numpad7 = nil,
	Numpad8 = nil,
	Numpad9 = nil,
	F1 = nil,
	F2 = nil,
	F3 = nil,
	F4 = nil,
	F5 = nil,
	F6 = nil,
	F7 = nil,
	F8 = nil,
	F9 = nil,
	F10 = nil,
	F11 = nil,
	F12 = nil,
	F13 = nil,
	F14 = nil,
	F15 = nil,
	Pause = nil
}

---@param return_symbol? boolean default = false
---@return keys | string -> key | symbol
function keyboard.get_pressed(return_symbol) end

---@param key keys
---@return boolean
function keyboard.is_pressed(key) end


mouse = {}

---@enum buttons
buttons = {
    Left = nil,
	Right = nil,
	Middle = nil,
	XButton1 = nil,
	XButton2 = nil
}

---@return integer
function mouse.get_pressed() end

---@param button buttons
---@return boolean
function mouse.is_pressed(button) end

---@return boolean
function mouse.is_scrolling_up() end

---@return boolean
function mouse.is_scrolling_down() end


hotreload = {}

---@return table<string, any>
function hotreload.get_state() end

---@param state table<string, any>
function hotreload.set_state(state) end

function hotreload.reload() end