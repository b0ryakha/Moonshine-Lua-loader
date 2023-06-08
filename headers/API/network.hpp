#pragma once

#include <SFML/Network.hpp>
#include <optional>
#include <unordered_map>

#include "lua_extensions.hpp"

namespace API
{
    static std::unordered_map<ushort_t, sf::IpAddress> clients;

    static std::optional<sf::UdpSocket> l_socket;
    static const sf::IpAddress l_ip = sf::IpAddress::getLocalAddress();
    static ushort_t l_port = 0;

    static char socket_type = '\0';

    static int network_bind(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 2)
            throw_error("[network.bind] Incorrect number of arguments!");

        if (l_port != 0)
            return 0;

        l_port = args.get<ushort_t>();
        socket_type = args.get<char>();

        if (socket_type != 's' && socket_type != 'c')
            throw_error("[network.bind] Invalid socket type!");

        l_socket.emplace();
        l_socket->setBlocking(false);

        if (l_socket->bind(l_port) != sf::Socket::Done)
            throw_error("[network.bind] Binding error!");

        return 0;
    }

    static int network_unbind(lua_State* L) {
        if (socket_type == '\0')
            return 0;

        socket_type = '\0';
        l_socket->unbind();
        l_socket.reset();

        clients.clear();

        return 0;
    }

    static int network_send(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 1 && args.size() != 3)
            throw_error("[network.send] Incorrect number of arguments!");

        if (socket_type == '\0')
            throw_error("[network.send] Local socket is not bind!");

        const std::string recipient_ip = args.size() == 1 ? "" : args.get<std::string>();
        const ushort_t recipient_port = args.size() == 1 ? 0 : args.get<ushort_t>();
        const LuaTable table = args.get<LuaTable>();

        sf::Packet packet;
        packet << table.size();

        for (size_t i = 1, size = table.size(); i <= size; ++i) {
            const std::string key = std::to_string(i);

            switch (table.get_type(key)) {
                case LuaMultiValue::Number:
                    packet << static_cast<size_t>(LuaMultiValue::Number) << table.get<double>(key);
                    break;
                case LuaMultiValue::String:
                    packet << static_cast<size_t>(LuaMultiValue::String) << table.get<std::string>(key);
                    break;
                case LuaMultiValue::Boolean:
                    packet << static_cast<size_t>(LuaMultiValue::Boolean) << table.get<bool>(key);
                    break;
                default:
                    packet << static_cast<size_t>(LuaMultiValue::Nil);
            }
        }
        
        if (socket_type == 's') {
            if (recipient_port != 0)
                clients[recipient_port] = std::move(recipient_ip);

            for (auto it = clients.begin(), end = clients.end(); it != end; ++it) {
                if (it->first == l_port && it->second == l_ip)
                    continue;

                if (l_socket->send(packet, it->second, it->first) == sf::Socket::Disconnected) {
                    it = clients.erase(it);
                    --it;
                }
            }
        }
        else {
            l_socket->send(packet, recipient_ip, recipient_port);
        }

        return 0;
    }

    static int network_receive(lua_State* L) {
        if (!l_socket.has_value()) {
            lua_pushnil(L);
            return 1;
        }

        sf::Packet packet;
        sf::IpAddress new_ip;
        ushort_t new_port;

        if (l_socket->receive(packet, new_ip, new_port) != sf::Socket::Done) {
            lua_pushnil(L);
            return 1;
        }
        
        if (socket_type == 's')
            clients[new_port] = std::move(new_ip);

        size_t size;
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
        lua_pushstring(L, l_ip.toString().c_str());
        return 1;
    }
}