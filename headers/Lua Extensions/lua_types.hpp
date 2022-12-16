#pragma once

#include <variant>
#include <string>
#include <array>
#include <unordered_map>
#include <memory>

#include "lua.hpp"
extern "C" {
    #pragma comment(lib, "lua54.lib")
}

#include "misc_functions.hpp"

enum class LuaMultiValueType : size_t { Number = 0, Function, String, Boolean, Table, Userdata, Nil };

inline const std::array<std::string, 7> S_TYPE_NAME = { "Number", "Function", "String", "Boolean", "Table", "Userdata", "Nil" };

struct LuaNil {};

class LuaUserdata {
    void* self = nullptr;

public:
    LuaUserdata(void* userdata) : self(userdata) {}
    operator void*() const { return self; };
};

class LuaBoolean {
    bool state = false;

public:
    LuaBoolean(bool state) : state(state) {}
    operator bool () const { return state; };
};

class LuaTable {
private:
    std::unordered_map<std::string_view, std::variant<lua_Number, lua_CFunction, std::string, LuaBoolean, std::shared_ptr<LuaTable>, LuaUserdata, LuaNil>> elements;
    mutable size_t counter_of_get = 0;

    __forceinline void check_errors(LuaMultiValueType expected_type, std::string key) const {
        if (elements.find(key) == elements.end()) {
            throw_error("[Table] Attempt to get element under key '" + key + "'.");
        }

        if (elements.at(key).index() != static_cast<size_t>(expected_type)) {
            throw_error("[Table] Incorrect type. Received " + S_TYPE_NAME[elements.at(key).index()] + ", but expected " + S_TYPE_NAME[static_cast<size_t>(expected_type)] + ".");
        }
    }

public:
    LuaTable(lua_State* lua_state, int index);

    size_t size() const noexcept;
    size_t empty() const noexcept;

    template<typename T>
    T get(const std::string& key) const { throw_error("[Table] Unknown type for get<T>, mb you meant get<LuaUserdata, T>?"); }

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
    double get<double>(const std::string& key) const {
        check_errors(LuaMultiValueType::Number, key);

        return std::get<lua_Number>(elements.at(key));
    }

    template<>
    float get<float>(const std::string& key) const {
        check_errors(LuaMultiValueType::Number, key);

        return static_cast<float>(std::get<lua_Number>(elements.at(key)));
    }

    template<>
    std::string get<std::string>(const std::string& key) const {
        check_errors(LuaMultiValueType::String, key);

        return std::get<std::string>(elements.at(key));
    }

    template<>
    bool get<bool>(const std::string& key) const {
        check_errors(LuaMultiValueType::Boolean, key);

        return static_cast<bool>(std::get<LuaBoolean>(elements.at(key)));
    }

    template<>
    LuaNil get<LuaNil>(const std::string& key) const {
        check_errors(LuaMultiValueType::Nil, key);

        return std::get<LuaNil>(elements.at(key));
    }

    template<>
    LuaTable get<LuaTable>(const std::string& key) const {
        check_errors(LuaMultiValueType::Table, key);

        return *(std::get<std::shared_ptr<LuaTable>>(elements.at(key)));
    }

    template<typename T>
    T get() const {
        return get<T>(std::to_string(1 + elements.size() - counter_of_get--));
    }

    template<typename T, typename Class>
    Class* get(const std::string& key) const {
        check_errors(LuaMultiValueType::Userdata, key);

        return *static_cast<Class**>(std::get<LuaUserdata>(elements.at(key)).self);
    }

    template<typename T, typename Class>
    Class* get() const {
        return get<T, Class>(std::to_string(1 + elements.size() - counter_of_get--));
    }
};

using LuaMultiValue = std::variant<lua_Number, lua_CFunction, std::string, LuaBoolean, LuaTable, LuaUserdata, LuaNil>;