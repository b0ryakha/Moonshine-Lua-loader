#include "LuaBoolean.hpp"

LuaBoolean::LuaBoolean(bool state) : state(state) {}

LuaBoolean::operator bool() const {
	return state;
};