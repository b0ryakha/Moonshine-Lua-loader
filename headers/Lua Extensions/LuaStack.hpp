#pragma once

#include <vector>
#include <string>
#include <array>
#include <iterator>

#include "misc_functions.hpp"
#include "lua_types.hpp"

class LuaStack final {
private:
    std::vector<LuaMultiValue> elements;
    mutable size_t counter_of_get = 0;

    __forceinline void check_errors(LuaMultiValueType expected_type, size_t index) const {
        if (index < 0 || index >= elements.size()) {
            throw_error("[Stack] Attempt to get an element under index '" + std::to_string(index) + "', size = " + std::to_string(elements.size()) + ".");
        }

        if (elements[index].index() != static_cast<size_t>(expected_type)) {
            throw_error("[Stack] Attempt to get a type element '" + S_TYPE_NAME[elements[index].index()] + "', but expected '" + S_TYPE_NAME[static_cast<size_t>(expected_type)] + "'.");
        }
    }

public:
    LuaStack(lua_State* lua_state);
    LuaStack(const LuaStack& other);
    LuaStack(LuaStack&& tmp) noexcept;
    ~LuaStack() = default;
    LuaStack& operator=(const LuaStack& other);
    LuaStack& operator=(LuaStack&& tmp) noexcept;

    size_t size() const noexcept;
    size_t empty() const noexcept;
    LuaMultiValueType get_type(size_t index) const;

    template<typename T>
    T get(size_t index) const { throw_error("[Stack] Unknown type for get<T>, mb you meant get<LuaUserdata, T>?"); }

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
    double get<double>(size_t index) const {
        check_errors(LuaMultiValueType::Number, index);

        return std::get<lua_Number>(elements[index]);
    }

    template<>
    float get<float>(size_t index) const {
        check_errors(LuaMultiValueType::Number, index);

        return static_cast<float>(std::get<lua_Number>(elements[index]));
    }

    template<>
    std::string get<std::string>(size_t index) const {
        check_errors(LuaMultiValueType::String, index);

        return std::get<std::string>(elements[index]);
    }

    template<>
    bool get<bool>(size_t index) const {
        check_errors(LuaMultiValueType::Boolean, index);

        return static_cast<bool>(std::get<LuaBoolean>(elements[index]));
    }

    template<>
    LuaNil get<LuaNil>(size_t index) const {
        check_errors(LuaMultiValueType::Nil, index);

        return std::get<LuaNil>(elements[index]);
    }

    template<>
    LuaTable get<LuaTable>(size_t index) const {
        check_errors(LuaMultiValueType::Table, index);

        return std::get<LuaTable>(elements[index]);
    }

    template<typename T>
    T get() const {
        return get<T>(elements.size() - counter_of_get--);
    }

    template<typename T, typename Class>
    Class get(size_t index) const {
        check_errors(LuaMultiValueType::Userdata, index);

        return *(*static_cast<Class**>(std::get<LuaUserdata>(elements[index])));
    }

    template<typename T, typename Class>
    Class get() const {
        return get<T, Class>(elements.size() - counter_of_get--);
    }
};