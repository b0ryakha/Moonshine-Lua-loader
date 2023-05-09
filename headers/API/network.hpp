#pragma once

#include <SFML/Network.hpp>
#include <memory>

#include "lua_extensions.hpp"

namespace API
{
    static std::unique_ptr<sf::TcpListener> listener;
    static std::unique_ptr<sf::TcpSocket> socket;
    static bool client_connected = false;

    static int network_open(lua_State* L) {
        LuaStack args(L);
        
        if (args.size() != 1)
            throw_error("[network.open] Incorrect number of arguments!");

        if (listener != nullptr || socket != nullptr)
            throw_error("[network.open] Host is already a server or client!");

        size_t port = args.get<size_t>();

        listener = std::make_unique<sf::TcpListener>();
        listener->setBlocking(false);

        socket = std::make_unique<sf::TcpSocket>();

        if (listener->listen(port) != sf::Socket::Done)
            throw_error("[network.open] Server creation error!");

        return 0;
    }

    static int network_close(lua_State* L) {
        if (listener == nullptr || socket == nullptr)
            return 0;

        listener->close();
        listener = nullptr;

        socket->disconnect();
        socket = nullptr;

        client_connected = false;

        return 0;
    }

    static int network_listen(lua_State* L) {
        if (listener == nullptr)
            throw_error("[network.listen] Server closed!");

        if (listener->accept(*socket) == sf::Socket::Done)
            client_connected = true;

        return 0;
    }

    static int network_client_ready(lua_State* L) {
        lua_pushboolean(L, (listener != nullptr && client_connected));
        return 1;
    }

    static int network_connect(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 2)
            throw_error("[network.connect] Incorrect number of arguments!");

        std::string ip = args.get<std::string>();
        size_t port = args.get<size_t>();

        socket = std::make_unique<sf::TcpSocket>();

        if (socket->connect(ip, port) != sf::Socket::Done)
            throw_error("[network.connect] Connection error!");

        return 0;
    }

    static int network_disconnect(lua_State* L) {
        if (listener != nullptr || socket == nullptr)
            return 0;

        socket->disconnect();
        socket = nullptr;

        return 0;
    }

    static int network_send(lua_State* L) {
        LuaStack args(L);

        if (args.empty())
            throw_error("[network.send] Incorrect number of arguments!");

        if (socket == nullptr)
            throw_error("[network.send] Connection error!");

        sf::Packet packet;
        
        packet << args.size();

        for (size_t i = 0, args_size = args.size(); i < args_size; ++i) {
            switch (args.get_type(i)) {
                case LuaMultiValue::Number:
                    packet << static_cast<size_t>(LuaMultiValue::Number) << args.get<double>(i);
                    break;
                case LuaMultiValue::String:
                    packet << static_cast<size_t>(LuaMultiValue::String) << args.get<std::string>(i);
                    break;
                case LuaMultiValue::Boolean:
                    packet << static_cast<size_t>(LuaMultiValue::Boolean) << args.get<bool>(i);
                    break;
                default:
                    packet << static_cast<size_t>(LuaMultiValue::Nil);
            }
        }

        socket->send(packet);

        return 0;
    }

    static int network_receive(lua_State* L) {
        if (socket == nullptr) {
            lua_pushnil(L);
            return 1;
        }

        sf::Packet packet;
        size_t size;

        socket->receive(packet);
        
        if (!(packet >> size)) {
            lua_pushnil(L);
            return 1;
        }
        
        std::vector<LuaMultiValue_t> result;
        result.reserve(size);

        for (size_t i = 0; i < size; ++i) {
            size_t type_id;
            if (!(packet >> type_id)) {
                lua_pushnil(L);
                return 1;
            }

            switch (LuaMultiValue(type_id)) {
                case LuaMultiValue::Number: {
                    double tmp;
                    if (packet >> tmp)
                        result.push_back(tmp);

                    break;
                }
                case LuaMultiValue::String: {
                    std::string tmp;
                    if (packet >> tmp)
                        result.push_back(std::move(tmp));

                    break;
                }
                case LuaMultiValue::Boolean: {
                    bool tmp;
                    if (packet >> tmp)
                        result.push_back(tmp);

                    break;
                }
                default:
                    result.push_back(std::move(LuaNil()));
            }
        }

        lua_pushtable(L, result);
        return 1;
    }

    static int network_get_local_address(lua_State* L) {
        lua_pushstring(L, sf::IpAddress::getLocalAddress().toString().c_str());
        return 1;
    }
}