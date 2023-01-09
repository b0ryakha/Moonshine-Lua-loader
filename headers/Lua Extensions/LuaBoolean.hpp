#pragma once

class LuaBoolean final {
    bool state = false;

public:
    LuaBoolean(bool state);
    operator bool() const;
};