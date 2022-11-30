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

    __forceinline void check_errors(LuaMultiValueType expected_type, size_t index) const {
        if (index < 0 || index >= elements.size()) {
            throw_error("[Stack] Attempt to get an element under index " + std::to_string(index) + ", but size = " + std::to_string(elements.size()) + ".");
        }

        static const std::array<std::string, 6> TYPE_NAME = { "Number", "Function", "String", "Boolean", "Table", "Nil" };

        if (elements[index].index() != static_cast<size_t>(expected_type)) {
            throw_error("Incorrect type, received " + TYPE_NAME[elements[index].index()] + ", but expected " + TYPE_NAME[static_cast<size_t>(expected_type)] + ".");
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
        check_errors(LuaMultiValueType::Number, index);

        return static_cast<int>(std::get<lua_Number>(elements[index]));
    }

    template<>
    size_t get<size_t>(size_t index) const {
        check_errors(LuaMultiValueType::Number, index);

        const lua_Number tmp = std::get<lua_Number>(elements[index]);
        return static_cast<size_t>((tmp > 0) ? tmp : 0);
    }

    template<>
    float get<float>(size_t index) const {
        check_errors(LuaMultiValueType::Number, index);

        return static_cast<float>(std::get<lua_Number>(elements[index]));
    }

    template<>
    std::string get<std::string>(size_t index) const {
        check_errors(LuaMultiValueType::String, index);

        return static_cast<std::string>(std::get<std::string>(elements[index]));
    }

    template<>
    bool get<bool>(size_t index) const {
        check_errors(LuaMultiValueType::Boolean, index);

        return static_cast<bool>(std::get<LuaBoolean>(elements[index]).state);
    }

    template<>
    LuaNil get<LuaNil>(size_t index) const {
        check_errors(LuaMultiValueType::Nil, index);

        return static_cast<LuaNil>(std::get<LuaNil>(elements[index]));
    }

    template<>
    LuaTable get<LuaTable>(size_t index) const {
        check_errors(LuaMultiValueType::Table, index);

        return static_cast<LuaTable>(std::get<LuaTable>(elements[index]));
    }

    template<typename T>
    T get() const {
        return get<T>(elements.size() - get_counter--);
    }
};