#include "API/Objects/Font.hpp"

API::Font::Font(const LuaStack& args) {
	if (args.size() != 2)
		throw_error("[Font.new] Incorrect number of arguments!");

	family = args.get<std::string>();
	size = args.get<size_t>();

	self = std::make_shared<sf::Font>();

	if (!self->loadFromFile(FONTS_PATH + family))
		throw_error("[Font.new] Font '" + family + "' was not found, perhaps the file extension was not specified!");
}

API::Font::operator sf::Font*() const {
	return self.get();
}

size_t API::Font::get_size() const {
	return size;
}

std::string API::Font::get_family() const {
	return family;
}