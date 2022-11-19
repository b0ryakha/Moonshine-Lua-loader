#pragma once

#include <vector>
#include <string>
#include <iterator>

#include "misc_functions.hpp"
#include "lua_types.hpp"

class LuaStack {
private:
	std::vector<LuaMultiValue> elements;

public:
	LuaStack(lua_State* lua_state);
	
	size_t size() const noexcept;
    size_t empty() const noexcept;
    LuaMultiValueType get_type(size_t index) const;

    template<typename T>
    T get(size_t index) const { throw_error("Unknown Type!"); }

    template<>
    int get<int>(size_t index) const {
        return static_cast<int>(std::get<lua_Number>(elements.at(index)));
    }

    template<>
    size_t get<size_t>(size_t index) const {
        int result = static_cast<int>(std::get<lua_Number>(elements.at(index)));
        return static_cast<size_t>(result > 0 ? result : 0);
    }

    template<>
    float get<float>(size_t index) const {
        return static_cast<float>(std::get<lua_Number>(elements.at(index)));
    }

    template<>
    std::string get<std::string>(size_t index) const {
        return static_cast<std::string>(std::get<std::string>(elements.at(index)));
    }

    template<>
    bool get<bool>(size_t index) const {
        return static_cast<bool>(std::get<LuaBoolean>(elements.at(index)).state);
    }

    template<>
    LuaNil get<LuaNil>(size_t index) const {
        return static_cast<LuaNil>(std::get<LuaNil>(elements.at(index)));
    }

    template<>
    LuaTable get<LuaTable>(size_t index) const {
        return static_cast<LuaTable>(std::get<LuaTable>(elements.at(index)));
    }
};