#include "LuaStack.hpp"

LuaStack::LuaStack(lua_State* lua_state) {
    elements.reserve(lua_gettop(lua_state));

    for (int i = 1; i <= lua_gettop(lua_state); ++i) {
        switch (lua_type(lua_state, i)) {
            case LUA_TTABLE:
                elements.push_back(LuaTable(lua_state, i));
                break;
            case LUA_TSTRING:
                elements.push_back(static_cast<std::string>(lua_tostring(lua_state, i)));
                break;
            case LUA_TBOOLEAN:
                elements.push_back(LuaBoolean(lua_toboolean(lua_state, i)));
                break;
            case LUA_TNUMBER:
                elements.push_back(static_cast<lua_Number>(lua_tonumber(lua_state, i)));
                break;
            case LUA_TFUNCTION:
                elements.push_back(static_cast<lua_CFunction>(lua_tocfunction(lua_state, i)));
                break;
            default:
                elements.push_back(LuaNil());
        }
    }
}

LuaMultiValueType LuaStack::get_type(size_t index) const {
    switch (elements.at(index).index()) {
        case 0:
            return LuaMultiValueType::Number;
        case 1:
            return LuaMultiValueType::Function;
        case 2:
            return LuaMultiValueType::String;
        case 3:
            return LuaMultiValueType::Boolean;
        case 4:
            return LuaMultiValueType::Table;
        default:
            return LuaMultiValueType::Nil;
    }
}

size_t LuaStack::size() const noexcept {
    return elements.size();
}

size_t LuaStack::empty() const noexcept {
    return elements.empty();
}