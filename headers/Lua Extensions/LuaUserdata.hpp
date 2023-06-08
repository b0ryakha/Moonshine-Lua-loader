#pragma once

class LuaUserdata final {
    void* self = nullptr;

public:
    LuaUserdata(void* userdata);

    template<typename T>
    operator T*() const {
        return static_cast<T*>(self);
    };
};