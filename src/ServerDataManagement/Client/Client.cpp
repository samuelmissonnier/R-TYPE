/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Client.cpp
*/

#include "Client.hpp"

Client::Client(TcpConnection::ptr &ptr) :
    _name(""), _ptr(ptr), _lobby(nullptr), _isReady(false)
{}

void Client::setName(const std::string &name)
{
    _name = name;
}

void Client::joinLobby(Lobby *lobby) noexcept
{
    _lobby = lobby;
}

void Client::leaveLobby(void) noexcept
{
    _lobby = nullptr;
    _isReady = false;
}

void Client::ready(void) noexcept
{
    _isReady = true;
}

void Client::notReady(void) noexcept
{
    _isReady = false;
}

bool Client::operator==(const Client &client) const noexcept
{
    return client.getConnection() == _ptr.get();
}

bool Client::operator!=(const Client &client) const noexcept
{
    return !operator==(client);
}
