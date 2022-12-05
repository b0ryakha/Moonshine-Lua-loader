#pragma once

#include <variant>
#include <string>
#include <array>
#include <unordered_map>

#include "lua.hpp"
extern "C" {
    #pragma comment(lib, "lua54.lib")
}

#include "misc_functions.hpp"

enum class LuaMultiValueType : size_t { Number = 0, Function, String, Boolean, Table, Nil };

inline const std::array<std::string, 6> TYPE_NAME = { "Number", "Function", "String", "Boolean", "Table", "Nil" };

struct LuaNil {};

struct LuaBoolean {
    bool state = false;
    LuaBoolean(bool state) : state(state) {}
};

class LuaTable {
private:
    std::unordered_map<std::string_view, std::variant<lua_Number, lua_CFunction, std::string, LuaBoolean, LuaNil>> elements;

    __forceinline void check_errors(LuaMultiValueType expected_type, std::string key) const {
        if (elements.find(key) == elements.end()) {
            throw_error("[Table] Attempt to get an element under key " + key + ".");
        }

        if (elements.at(key).index() != static_cast<size_t>(expected_type)) {
            throw_error("Incorrect type, received " + TYPE_NAME[elements.at(key).index()] + ", but expected " + TYPE_NAME[static_cast<size_t>(expected_type)] + ".");
        }
    }

public:
    LuaTable(lua_State* lua_state, int index);

    template<typename T>
    T get(const std::string& key) const { throw_error("Unknown Type!"); }

    template<>
    int get<int>(const std::string& key) const {
        check_errors(LuaMultiValueType::Number, key);

        return static_cast<int>(std::get<lua_Number>(elements.at(key)));
    }

    template<>
    size_t get<size_t>(const std::string& key) const {
        check_errors(LuaMultiValueType::Number, key);

        const lua_Number tmp = std::get<lua_Number>(elements.at(key));
        return static_cast<size_t>((tmp > 0) ? tmp : 0);
    }

    template<>
    float get<float>(const std::string& key) const {
        check_errors(LuaMultiValueType::Number, key);

        return static_cast<float>(std::get<lua_Number>(elements.at(key)));
    }

    template<>
    std::string get<std::string>(const std::string& key) const {
        check_errors(LuaMultiValueType::String, key);

        return static_cast<std::string>(std::get<std::string>(elements.at(key)));
    }

    template<>
    bool get<bool>(const std::string& key) const {
        check_errors(LuaMultiValueType::Boolean, key);

        return static_cast<bool>(std::get<LuaBoolean>(elements.at(key)).state);
    }

    template<>
    LuaNil get<LuaNil>(const std::string& key) const {
        check_errors(LuaMultiValueType::Nil, key);

        return static_cast<LuaNil>(std::get<LuaNil>(elements.at(key)));
    }
};

using LuaMultiValue = std::variant<lua_Number, lua_CFunction, std::string, LuaBoolean, LuaTable, LuaNil>;