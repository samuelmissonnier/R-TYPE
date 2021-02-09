/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Lobby.cpp
*/

#include "Lobby.hpp"
#include "../../Logger/Logger.hpp"
#include "../../Utils/RTypeUtils.hpp"
#include <boost/asio.hpp>
#include <iostream>

Lobby::Lobby(boost::asio::io_context &context, const std::string &name, Client *creator, size_t maxClient) :
    _name(name),
    _maxClient(maxClient),
    _context(context)
{
    addClient(creator);
    using std::placeholders::_1;
    using std::placeholders::_2;
    _udpCommands["210"] = std::bind(&Lobby::loadingBeam, this, _1, _2);
    _udpCommands["220"] = std::bind(&Lobby::beamShooted, this, _1, _2);
    _udpCommands["230"] = std::bind(&Lobby::playerDirection, this, _1, _2);
}

void Lobby::unknowUdpRequest(UdpConnection *connection, const std::string &command)
{
    (void)connection;
    std::cerr << Logger::log(LogLvl::WARNING, "Unknow request: " + command) << std::endl;
}

void Lobby::loadingBeam(UdpConnection *connection, const std::string &command)
{
    
}

void Lobby::beamShooted(UdpConnection *connection, const std::string &command)
{
    
}

void Lobby::playerDirection(UdpConnection *connection, const std::string &command)
{
    
}

bool Lobby::addClient(Client *newClient)
{
    if (_clients.size() < _maxClient) {
        _clients.push_back(newClient);
        newClient->joinLobby(this);
        return true;
    }
    return false;
}

bool Lobby::removeClient(Client *client)
{
    for (size_t i = 0; i < _clients.size(); i++) {
        if (client == _clients[i]) {
            client->leaveLobby();
            _clients.erase(_clients.begin() + i);
            return true;
        }
    }
    return false;
}

void Lobby::startGame(void)
{
    _threadLoop = true;
    //_gameThread = std::thread(std::bind(&Lobby::gameLoop, this));
    UdpConnection::ptr udp = UdpConnection::pointerCreate(_context, "127.0.0.1", 7172, true, this);
    _udpConnection = udp;
    _udpConnection->write("aaaaaaaaaaaaa", _endpoint);
    //_udpConnection->read();
}

void Lobby::stopGame(void)
{
    _threadLoop = false;
    if (_gameThread.joinable())
        _gameThread.join();
}

void Lobby::gameLoop(void)
{
    // while (_threadLoop) {
    //     for (auto player : _players) {
    //         for (auto enemy : _enemies) {
    //         }
    //     }
    // }
}

void Lobby::sendToClients(const std::string &command)
{
    for (auto it : _udpConnection->getEndpoints())
        _udpConnection->write(command, it);
}
