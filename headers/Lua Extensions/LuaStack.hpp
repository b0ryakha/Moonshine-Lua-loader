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
    std::string linked_func_name;
    mutable size_t counter_of_get = 0u;

    void check_errors(LuaMultiValue expected_type, size_t index) const {
        if (index < 0u || index >= elements.size())
            throw_error("[Stack assert] Out of range, index = " + std::to_string(index) + ", size = " + std::to_string(elements.size()) + ".");

        if (elements[index].index() != static_cast<size_t>(expected_type))
            throw_error("[" + linked_func_name + "] Bad argument #" + std::to_string(index + 1) + " (" + LuaMultiValue_s[static_cast<size_t>(expected_type)] + " expected, got " + LuaMultiValue_s[elements[index].index()] + ")");
    }

public:
    LuaStack(lua_State* lua_state, std::string_view func_name);
    LuaStack(const LuaStack& other);
    LuaStack(LuaStack&& tmp) noexcept;
    ~LuaStack() = default;
    LuaStack& operator=(const LuaStack& other);
    LuaStack& operator=(LuaStack&& tmp) noexcept;

    size_t size() const;
    size_t empty() const;
    LuaMultiValue get_type(size_t index) const;
    
    void error(const std::string& error) const {
        throw_error("[" + linked_func_name + "] " + error);
    }

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

    template<typename T, typename APIStruct>
    APIStruct get(size_t index) const {
        if (!std::is_same_v<T, LuaUserdata>)
            throw_error("[Stack assert] Unknown type for get<LuaUserdata, APIStruct>!");

        check_errors(LuaMultiValue::Userdata, index);

        return *(*static_cast<APIStruct**>(std::get<LuaUserdata>(elements[index])));
    }

    template<typename T, typename APIStruct>
    APIStruct get() const {
        return get<T, APIStruct>(elements.size() - counter_of_get--);
    }
};