#pragma once

#include <vector>
#include <string>
#include <array>
#include <iterator>

#include "misc_functions.hpp"
#include "lua_types.hpp"

class LuaStack {
private:
    std::vector<LuaMultiValue> elements;
    mutable size_t get_counter = 1;

    __forceinline void check_type(LuaMultiValueType expected_type, size_t index) const {
        static const std::array<std::string, 6> TYPE_NAME = { "Number", "Function", "String", "Boolean", "Table", "Nil" };

        if (elements.at(index).index() != static_cast<size_t>(expected_type)) {
            throw_error("Incorrect type, received " + TYPE_NAME[elements.at(index).index()] + ", but expected " + TYPE_NAME[static_cast<size_t>(expected_type)] + ".");
        }
    }

public:
    LuaStack(lua_State* lua_state);

    size_t size() const noexcept;
    size_t empty() const noexcept;
    LuaMultiValueType get_type(size_t index) const;

    template<typename T>
    T get(size_t index) const { throw_error("Unknown Type!"); }

    template<>
    int get<int>(size_t index) const {
        check_type(LuaMultiValueType::Number, index);

        return static_cast<int>(std::get<lua_Number>(elements.at(index)));
    }

    template<>
    size_t get<size_t>(size_t index) const {
        check_type(LuaMultiValueType::Number, index);

        int result = static_cast<int>(std::get<lua_Number>(elements.at(index)));
        return static_cast<size_t>(result > 0 ? result : 0);
    }

    template<>
    float get<float>(size_t index) const {
        check_type(LuaMultiValueType::Number, index);

        return static_cast<float>(std::get<lua_Number>(elements.at(index)));
    }

    template<>
    std::string get<std::string>(size_t index) const {
        check_type(LuaMultiValueType::String, index);

        return static_cast<std::string>(std::get<std::string>(elements.at(index)));
    }

    template<>
    bool get<bool>(size_t index) const {
        check_type(LuaMultiValueType::Boolean, index);

        return static_cast<bool>(std::get<LuaBoolean>(elements.at(index)).state);
    }

    template<>
    LuaNil get<LuaNil>(size_t index) const {
        check_type(LuaMultiValueType::Nil, index);

        return static_cast<LuaNil>(std::get<LuaNil>(elements.at(index)));
    }

    template<>
    LuaTable get<LuaTable>(size_t index) const {
        check_type(LuaMultiValueType::Table, index);

        return static_cast<LuaTable>(std::get<LuaTable>(elements.at(index)));
    }

    template<typename T>
    T get() const {
        return get<T>(elements.size() - get_counter--);
    }
};