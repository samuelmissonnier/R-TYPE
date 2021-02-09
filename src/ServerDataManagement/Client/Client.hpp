/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Client.hpp
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include "../../TcpConnection/TcpConnection.hpp"
#include <string>

class Lobby;

class Client {
public:
    Client(TcpConnection::ptr &ptr);
    ~Client(void) = default;

    void setName(const std::string &name);

    const std::string &getName(void) const noexcept { return _name; }

    TcpConnection *getConnection(void) noexcept { return _ptr.get(); }

    const TcpConnection *getConnection(void) const noexcept { return _ptr.get(); }

    bool isReady(void) const noexcept { return _isReady; };

    Lobby *getLobby(void) const noexcept { return _lobby; }

    void joinLobby(Lobby *lobby) noexcept;
    void leaveLobby(void) noexcept;

    void ready(void) noexcept;
    void notReady(void) noexcept;

    bool operator==(const Client &client) const noexcept;
    bool operator!=(const Client &client) const noexcept;

private:
    std::string _name;
    TcpConnection::ptr _ptr;
    Lobby *_lobby;
    bool _isReady;
};

#endif /* CLIENT_HPP_ */
