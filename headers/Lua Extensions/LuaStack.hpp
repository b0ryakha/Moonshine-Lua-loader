#pragma once

#include <vector>
#include <string>
#include <array>
#include <iterator>

#include "misc_functions.hpp"
#include "LuaTable.hpp"

class LuaStack final {
private:
    std::vector<LuaMultiValue_t> elements;
    mutable size_t counter_of_get = 0;

    __forceinline void check_errors(LuaMultiValue expected_type, size_t index) const {
        if (index < 0 || index >= elements.size())
            throw_error("[Stack assert] Out of range, index = " + std::to_string(index) + ", size = " + std::to_string(elements.size()) + ".");

        if (elements[index].index() != static_cast<size_t>(expected_type))
            throw_error("[Stack] Cannot convert '" + LuaMultiValue_s[elements[index].index()] + "' to '" + LuaMultiValue_s[static_cast<size_t>(expected_type)] + "'.");
    }

public:
    LuaStack(lua_State* lua_state);
    LuaStack(const LuaStack& other);

    template<typename T>
    LuaStack(LuaStack&& tmp) noexcept : elements(std::forward<T>(tmp.elements)) {}

    ~LuaStack() = default;
    LuaStack& operator=(const LuaStack& other);
    LuaStack& operator=(LuaStack&& tmp) noexcept;

    size_t size() const noexcept;
    size_t empty() const noexcept;
    LuaMultiValue get_type(size_t index) const;

    template<typename T>
    T get(size_t index) const { throw_error("[Stack assert] Unknown type for get<T>, mb you meant get<LuaUserdata, T>?"); }

    template<>
    short get<short>(size_t index) const {
        check_errors(LuaMultiValue::Number, index);

        return static_cast<short>(std::get<lua_Number>(elements[index]));
    }

    template<>
    ushort_t get<ushort_t>(size_t index) const {
        check_errors(LuaMultiValue::Number, index);

        return static_cast<ushort_t>(std::get<lua_Number>(elements[index]));
    }

    template<>
    int get<int>(size_t index) const {
        check_errors(LuaMultiValue::Number, index);

        return static_cast<int>(std::get<lua_Number>(elements[index]));
    }

    template<>
    size_t get<size_t>(size_t index) const {
        check_errors(LuaMultiValue::Number, index);

        const lua_Number tmp = std::get<lua_Number>(elements[index]);
        return static_cast<size_t>((tmp > 0) ? tmp : 0);
    }

    template<>
    double get<double>(size_t index) const {
        check_errors(LuaMultiValue::Number, index);

        return std::get<lua_Number>(elements[index]);
    }

    template<>
    float get<float>(size_t index) const {
        check_errors(LuaMultiValue::Number, index);

        return static_cast<float>(std::get<lua_Number>(elements[index]));
    }

    template<>
    char get<char>(size_t index) const {
        check_errors(LuaMultiValue::String, index);

        const std::string_view tmp{std::get<std::string>(elements[index]).c_str(), std::get<std::string>(elements[index]).size()};
        return *(tmp.data());
    }

    template<>
    std::string get<std::string>(size_t index) const {
        check_errors(LuaMultiValue::String, index);

        return std::get<std::string>(elements[index]);
    }

    template<>
    bool get<bool>(size_t index) const {
        check_errors(LuaMultiValue::Boolean, index);

        return static_cast<bool>(std::get<LuaBoolean>(elements[index]));
    }

    template<>
    LuaNil get<LuaNil>(size_t index) const {
        check_errors(LuaMultiValue::Nil, index);

        return std::get<LuaNil>(elements[index]);
    }

    template<>
    LuaTable get<LuaTable>(size_t index) const {
        check_errors(LuaMultiValue::Table, index);

        return std::get<LuaTable>(elements[index]);
    }

    template<typename T>
    T get() const {
        return get<T>(elements.size() - counter_of_get--);
    }

    template<typename T, typename Class>
    Class get(size_t index) const {
        check_errors(LuaMultiValue::Userdata, index);

        return *(*static_cast<Class**>(std::get<LuaUserdata>(elements[index])));
    }

    template<typename T, typename Class>
    Class get() const {
        return get<T, Class>(elements.size() - counter_of_get--);
    }
};