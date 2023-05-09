#include "LuaTable.hpp"

LuaTable::LuaTable(lua_State* lua_state, int index) {
    lua_pushvalue(lua_state, index);
    lua_pushnil(lua_state);

    while (lua_next(lua_state, -2)) {
        lua_pushvalue(lua_state, -2);

        const std::string_view key = lua_tostring(lua_state, -1);

        switch (lua_type(lua_state, -2)) {
        case LUA_TTABLE:
            elements[key] = std::move(std::make_shared<LuaTable>(lua_state, -2));
            break;
        case LUA_TSTRING:
            elements[key] = std::move(std::string(lua_tostring(lua_state, -2)));
            break;
        case LUA_TBOOLEAN:
            elements[key] = LuaBoolean(lua_toboolean(lua_state, -2));
            break;
        case LUA_TNUMBER:
            elements[key] = lua_tonumber(lua_state, -2);
            break;
        case LUA_TFUNCTION:
            elements[key] = lua_tocfunction(lua_state, -2);
            break;
        case LUA_TUSERDATA:
            elements[key] = LuaUserdata(lua_touserdata(lua_state, -2));
            break;
        default:
            elements[key] = LuaNil();
        }

        lua_pop(lua_state, 2);
    }

    lua_pop(lua_state, 1);

    counter_of_get = elements.size();
}

LuaTable::LuaTable(const LuaTable& other) : elements(other.elements) {}

LuaTable::LuaTable(LuaTable&& tmp) noexcept : elements(std::move(tmp.elements)) {}

LuaTable& LuaTable::operator=(const LuaTable& other) {
    if (this != &other)
        elements = other.elements;

    return *this;
}

LuaTable& LuaTable::operator=(LuaTable&& tmp) noexcept {
    if (this != &tmp)
        elements = std::move(tmp.elements);

    return *this;
}

size_t LuaTable::size() const noexcept {
    return elements.size();
}

size_t LuaTable::empty() const noexcept {
    return elements.empty();
}

LuaMultiValue LuaTable::get_type(const std::string& key) const {
    if (elements.find(key) == elements.end())
        return LuaMultiValue::Nil;

    return static_cast<LuaMultiValue>(elements.at(key).index());
}