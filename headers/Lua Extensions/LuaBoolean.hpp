#pragma once

class LuaBoolean final {
    bool state = false;

public:
    LuaBoolean(bool state) : state(state) {}

    constexpr operator bool() const {
        return state;
    }
};