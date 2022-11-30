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
    T const& get(size_t index) const { throw_error("Unknown Type!"); }

    template<>
    int const& get<int>(size_t index) const {
        check_errors(LuaMultiValueType::Number, index);

        return static_cast<int>(std::get<lua_Number>(elements[index]));
    }

    template<>
    size_t const& get<size_t>(size_t index) const {
        check_errors(LuaMultiValueType::Number, index);

        int result = static_cast<int>(std::get<lua_Number>(elements[index]));
        return static_cast<size_t>(result > 0 ? result : 0);
    }

    template<>
    float const& get<float>(size_t index) const {
        check_errors(LuaMultiValueType::Number, index);

        return static_cast<float>(std::get<lua_Number>(elements[index]));
    }

    template<>
    std::string const& get<std::string>(size_t index) const {
        check_errors(LuaMultiValueType::String, index);

        return static_cast<std::string>(std::get<std::string>(elements[index]));
    }

    template<>
    bool const& get<bool>(size_t index) const {
        check_errors(LuaMultiValueType::Boolean, index);

        return static_cast<bool>(std::get<LuaBoolean>(elements[index]).state);
    }

    template<>
    LuaNil const& get<LuaNil>(size_t index) const {
        check_errors(LuaMultiValueType::Nil, index);

        return static_cast<LuaNil>(std::get<LuaNil>(elements[index]));
    }

    template<>
    LuaTable const& get<LuaTable>(size_t index) const {
        check_errors(LuaMultiValueType::Table, index);

        return static_cast<LuaTable>(std::get<LuaTable>(elements[index]));
    }

    template<typename T>
    T const& get() const {
        return get<T>(elements.size() - get_counter--);
    }
};