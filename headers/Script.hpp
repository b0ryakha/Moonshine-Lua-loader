#pragma once
#include "lua_helper.hpp"

#include <string>
#include <future>

class Script final {
private:
	lua_State* lua_state = nullptr;
	std::future<void> future;
	std::string lua_path;

	void open_API();

public:
	Script() = default;
	Script(std::string_view path);

	void open(std::string_view path);
	bool is_open() const;
};