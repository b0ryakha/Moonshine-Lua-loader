#include "API/Objects/Font.hpp"

#include "Application.hpp"
extern Application* app;

#include <filesystem>
namespace fs = std::filesystem;

API::Font::Font(const LuaStack& args) {
	if (args.size() != 2 && args.size() != 3)
		throw_error("[Font:new] Incorrect number of arguments!");

	family = args.get<std::string>();
	size = args.get<size_t>();
	
	if (args.size() == 3) {
		const std::string styles = args.get<std::string>();
		if (!styles.empty()) {
			if (styles.find('r') != std::string::npos)
				this->styles |= sf::Text::Style::Regular;

			if (styles.find('b') != std::string::npos)
				this->styles |= sf::Text::Style::Bold;

			if (styles.find('i') != std::string::npos)
				this->styles |= sf::Text::Style::Italic;

			if (styles.find('l') != std::string::npos)
				this->styles |= sf::Text::Style::Underlined;

			if (styles.find('s') != std::string::npos)
				this->styles |= sf::Text::Style::StrikeThrough;
		}
	}

	const auto path = app->font_path + family;

	if (!fs::exists(path) || !loadFromFile(path))
		throw_error("[Font:new] Font '" + family + "' was not found or not installed!");
}

size_t API::Font::get_size() const {
	return size;
}

sf::Text::Style API::Font::get_style() const {
	return static_cast<sf::Text::Style>(styles);
}