#include "LuaStack.hpp"

LuaStack::LuaStack(lua_State* lua_state, std::string_view func_name) {
    linked_func_name = std::move(func_name);
    elements.reserve(lua_gettop(lua_state));

    for (int i = 1; i <= lua_gettop(lua_state); ++i) {
        switch (lua_type(lua_state, i)) {
            case LUA_TTABLE:
                elements.push_back(LuaTable(lua_state, i));
                break;
            case LUA_TSTRING:
                elements.push_back(std::string(lua_tostring(lua_state, i)));
                break;
            case LUA_TBOOLEAN:
                elements.push_back(LuaBoolean(lua_toboolean(lua_state, i)));
                break;
            case LUA_TNUMBER:
                elements.push_back(lua_tonumber(lua_state, i));
                break;
            case LUA_TFUNCTION:
                elements.push_back(lua_tocfunction(lua_state, i));
                break;
            case LUA_TUSERDATA:
                elements.push_back(LuaUserdata(lua_touserdata(lua_state, i)));
                break;
            default:
                elements.push_back(LuaNil());
        }
    }

    counter_of_get = elements.size();
}

LuaStack::LuaStack(const LuaStack& other) : elements(other.elements) {}

LuaStack::LuaStack(LuaStack&& tmp) noexcept : elements(std::move(tmp.elements)) {}

LuaStack& LuaStack::operator=(const LuaStack& other) {
    if (this != &other)
        elements = other.elements;

    return *this;
}

LuaStack& LuaStack::operator=(LuaStack&& tmp) noexcept {
    if (this != &tmp)
        elements = std::move(tmp.elements);

    return *this;
}

size_t LuaStack::size() const {
    return elements.size();
}

size_t LuaStack::empty() const {
    return elements.empty();
}

LuaMultiValue LuaStack::get_type(size_t index) const {
    if (index < 0 || index >= elements.size())
        return LuaMultiValue::Nil;

    return static_cast<LuaMultiValue>(elements[index].index());
}