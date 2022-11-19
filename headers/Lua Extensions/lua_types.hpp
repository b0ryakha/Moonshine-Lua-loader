#pragma once

#include <variant>
#include <string>
#include <map>

#include "lua.hpp"
extern "C" {
    #pragma comment(lib, "lua54.lib")
}

#include "misc_functions.hpp"

struct LuaNil {};

struct LuaBoolean {
    bool state = false;
    LuaBoolean(bool state) : state(state) {}
};

class LuaTable {
private:
    mutable std::map<std::string, std::variant<lua_Number, lua_CFunction, std::string, LuaBoolean, LuaNil>> elements;

public:
    LuaTable(lua_State* lua_state, int index);

    template<typename T>
    T get(const std::string& key) const { throw_error("Unknown Type!"); }

    template<>
    int get<int>(const std::string& key) const {
        return static_cast<int>(std::get<lua_Number>(elements[key]));
    }

    template<>
    size_t get<size_t>(const std::string& key) const {
        int result = static_cast<int>(std::get<lua_Number>(elements[key]));
        return static_cast<size_t>(result > 0 ? result : 0);
    }

    template<>
    float get<float>(const std::string& key) const {
        return static_cast<float>(std::get<lua_Number>(elements[key]));
    }

    template<>
    std::string get<std::string>(const std::string& key) const {
        return static_cast<std::string>(std::get<std::string>(elements[key]));
    }

    template<>
    bool get<bool>(const std::string& key) const {
        return static_cast<bool>(std::get<LuaBoolean>(elements[key]).state);
    }

    template<>
    LuaNil get<LuaNil>(const std::string& key) const {
        return static_cast<LuaNil>(std::get<LuaNil>(elements[key]));
    }
};

enum class LuaMultiValueType {
    Number, Function, String, Boolean, Nil, Table
};

using LuaMultiValue = std::variant<lua_Number, lua_CFunction, std::string, LuaBoolean, LuaTable, LuaNil>;