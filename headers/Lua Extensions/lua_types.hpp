#pragma once

#include <variant>
#include <string>
#include <array>
#include <map>

#include "lua.hpp"
extern "C" {
    #pragma comment(lib, "lua54.lib")
}

#include "misc_functions.hpp"

enum class LuaMultiValueType : size_t {
    Number = 0, Function, String, Boolean, Table, Nil
};

struct LuaNil {};

struct LuaBoolean {
    bool state = false;
    LuaBoolean(bool state) : state(state) {}
};

class LuaTable {
private:
    mutable std::map<std::string, std::variant<lua_Number, lua_CFunction, std::string, LuaBoolean, LuaNil>> elements;

    __forceinline void check_type(LuaMultiValueType expected_type, std::string key) const {
        static const std::array<std::string, 6> TYPE_NAME = { "Number", "Function", "String", "Boolean", "Table", "Nil" };

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
        check_type(LuaMultiValueType::Number, key);

        return static_cast<int>(std::get<lua_Number>(elements.at(key)));
    }

    template<>
    size_t get<size_t>(const std::string& key) const {
        check_type(LuaMultiValueType::Number, key);

        int result = static_cast<int>(std::get<lua_Number>(elements.at(key)));
        return static_cast<size_t>(result > 0 ? result : 0);
    }

    template<>
    float get<float>(const std::string& key) const {
        check_type(LuaMultiValueType::Number, key);

        return static_cast<float>(std::get<lua_Number>(elements.at(key)));
    }

    template<>
    std::string get<std::string>(const std::string& key) const {
        check_type(LuaMultiValueType::String, key);

        return static_cast<std::string>(std::get<std::string>(elements.at(key)));
    }

    template<>
    bool get<bool>(const std::string& key) const {
        check_type(LuaMultiValueType::Boolean, key);

        return static_cast<bool>(std::get<LuaBoolean>(elements.at(key)).state);
    }

    template<>
    LuaNil get<LuaNil>(const std::string& key) const {
        check_type(LuaMultiValueType::Nil, key);

        return static_cast<LuaNil>(std::get<LuaNil>(elements.at(key)));
    }
};

using LuaMultiValue = std::variant<lua_Number, lua_CFunction, std::string, LuaBoolean, LuaTable, LuaNil>;