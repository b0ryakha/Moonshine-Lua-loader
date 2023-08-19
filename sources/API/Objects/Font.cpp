#include "API/Objects/Font.hpp"

API::Font::Font(const LuaStack& args) {
	if (args.size() != 2)
		throw_error("[Font:new] Incorrect number of arguments!");

	std::string family = args.get<std::string>();
	size = args.get<size_t>();

	if (!loadFromFile(font_path + family))
		throw_error("[Font:new] Font '" + family + "' was not found or not installed!");
}

size_t API::Font::get_size() const {
	return size;
}