#pragma once

class LuaUserdata final {
    void* self = nullptr;

public:
    LuaUserdata(void* userdata) : self(userdata) {}

    template<typename T>
    constexpr operator T*() const {
        return reinterpret_cast<T*>(self);
    }
};