#include "API/Objects/Sound.hpp"

API::Sound::Sound(const LuaStack& args) {
    if (args.size() != 2 && args.size() != 3)
        throw_error("[Sound:new] Incorrect number of arguments!");

    path = args.get<std::string>();
    size_t volume = args.get<size_t>();
    bool is_repeat = (args.size() == 3) ? args.get<bool>() : false;

    if (!buffer.loadFromFile(path))
        throw_error("[Sound:new] Sound by path '" + path + "' cannot be loaded!");

    setBuffer(buffer);
    setLoop(is_repeat);
    setVolume(volume);
}

const std::string API::Sound::get_path() const {
	return path;
}

void API::Sound::play(bool is_reset) {
    if (is_reset || getStatus() != sf::SoundSource::Status::Playing) {
        setBuffer(buffer);
        sf::Sound::play();
    }
}