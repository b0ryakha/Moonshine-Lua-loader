#include "API/Objects/Sound.hpp"

API::Sound::Sound(const LuaStack& args) {
    if (args.size() != 2 && args.size() != 3)
        throw_error("[Sound.new] Incorrect number of arguments!");

    path = args.get<std::string>();
    size_t volume = args.get<size_t>();
    bool is_repeat = (args.size() == 3) ? args.get<bool>() : false;

    if (!buffer.loadFromFile(path))
        throw_error("[Sound.new] The sound cannot be found in the path '" + path + "'!");

    sound.setBuffer(buffer);
    sound.setLoop(is_repeat);
    sound.setVolume((volume > 100) ? 100 : volume);
}

API::Sound::operator sf::Sound() const {
	sound.setBuffer(buffer);
	return sound;
}

std::string API::Sound::get_path() const {
	return path;
}

size_t API::Sound::get_volume() const {
	return sound.getVolume();
}

void API::Sound::set_volume(int volume) {
	if (volume > 100) volume = 100;
	if (volume < 0) volume = 0;

	sound.setVolume(volume);
}

bool API::Sound::get_loop() const {
	return sound.getLoop();
}

void API::Sound::set_loop(bool is_repeat) {
	sound.setLoop(is_repeat);
}

void API::Sound::play(bool is_reset) {
    if (is_reset || sound.getStatus() != sf::SoundSource::Status::Playing) {
        sound.setBuffer(buffer);
        sound.play();
    }
}

void API::Sound::stop() {
    sound.stop();
}