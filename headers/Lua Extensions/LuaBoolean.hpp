#pragma once

class LuaBoolean final {
    bool state = false;

public:
    explicit LuaBoolean(bool state) : state(state) {}

    constexpr operator bool() const {
        return state;
    }
};