#pragma once
#include "lua_helper.hpp"

#include <SFML/Network.hpp>
#include <optional>
#include <unordered_map>
#include <iterator>

namespace API
{
    static std::unordered_map<ushort_t, std::string> clients;

    static std::optional<sf::UdpSocket> l_socket;
    //TODO: fix for 3.0.0
    static const std::string l_ip = "";//sf::IpAddress::getLocalAddress().value().toString();
    static ushort_t l_port = 0;

    static char socket_type = '\0';

    static int network_bind(lua_State* L) {
        LuaStack args(L, "network.bind");

        if (args.size() != 2)
            args.error("Incorrect number of arguments!");

        if (l_port != 0)
            return 0;

        l_port = args.get<ushort_t>();
        socket_type = args.get<char>();

        if (socket_type != 's' && socket_type != 'c')
            args.error("Invalid socket type!");

        l_socket.emplace();
        l_socket->setBlocking(false);

        if (l_socket->bind(l_port) != sf::Socket::Status::Done)
            args.error("Binding error!");

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
        LuaStack args(L, "network.send");

        if (args.size() != 1 && args.size() != 3)
            args.error("Incorrect number of arguments!");

        if (socket_type == '\0')
            args.error("Local socket is not bind!");

        const std::string recipient_ip = args.size() == 1 ? "" : args.get<std::string>();
        const ushort_t recipient_port = args.size() == 1 ? 0 : args.get<ushort_t>();
        const LuaTable table = args.get<LuaTable>();

        sf::Packet packet;
        packet << static_cast<int>(table.size());

        for (size_t i = 1, size = table.size(); i <= size; ++i) {
            const std::string key = std::to_string(i);

            switch (table.get_type(key)) {
                case LuaMultiValue::Number:
                    packet << static_cast<int>(LuaMultiValue::Number) << table.get<double>(key);
                    break;
                case LuaMultiValue::String:
                    packet << static_cast<int>(LuaMultiValue::String) << table.get<std::string>(key);
                    break;
                case LuaMultiValue::Boolean:
                    packet << static_cast<int>(LuaMultiValue::Boolean) << table.get<bool>(key);
                    break;
                default:
                    packet << static_cast<int>(LuaMultiValue::Nil);
            }
        }
        
        if (socket_type == 's') {
            if (recipient_port != 0)
                clients[recipient_port] = recipient_ip;

            for (auto it = clients.begin(), end = clients.end(); it != end; ++it) {
                if (it->first == l_port && it->second == l_ip)
                    continue;

                if (l_socket->send(packet, sf::IpAddress::resolve(it->second).value(), it->first) == sf::Socket::Status::Disconnected) {
                    it = clients.erase(it);
                    std::advance(it, -1);
                }
            }
        }
        else {
            l_socket->send(packet, sf::IpAddress::resolve(recipient_ip).value(), recipient_port);
        }

        return 0;
    }

    static int network_receive(lua_State* L) {
        if (!l_socket.has_value()) {
            lua_pushnil(L);
            return 1;
        }

        sf::Packet packet;
        std::optional<sf::IpAddress> new_ip;
        ushort_t new_port;

        if (l_socket->receive(packet, new_ip, new_port) != sf::Socket::Status::Done || !new_ip.has_value()) {
            lua_pushnil(L);
            return 1;
        }
        
        if (socket_type == 's')
            clients[new_port] = new_ip.value().toString();

        int size;
        if (!(packet >> size)) {
            lua_pushnil(L);
            return 1;
        }

        std::vector<LuaMultiValue_t> result;
        result.reserve(size);

        for (size_t i = 0; i < static_cast<size_t>(size); ++i) {
            int type_id;
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
                        result.push_back(LuaBoolean(tmp));

                    break;
                }
                default:
                    result.push_back(LuaNil());
            }
        }

        lhelper::push_table(L, result);
        return 1;
    }

    static int network_get_local_address(lua_State* L) {
        lua_pushstring(L, l_ip.c_str());
        return 1;
    }
}