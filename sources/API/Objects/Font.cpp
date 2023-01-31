#include "API/Objects/Font.hpp"

API::Font::Font(const LuaStack& args) {
	if (args.size() != 2)
		throw_error("[Font:new] Incorrect number of arguments!");

	std::string family = args.get<std::string>();
	size = args.get<size_t>();

	if (!loadFromFile(FONTS_PATH + family))
		throw_error("[Font:new] Font '" + family + "' was not found, perhaps the file extension was not specified!");
}

size_t API::Font::get_size() const {
	return size;
}