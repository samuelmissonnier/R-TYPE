/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Lobby.hpp
*/

#ifndef LOBBY_HPP_
#define LOBBY_HPP_

#include "../../RTypeUdpCommand/RTypeUdpCommand.hpp"
#include "../../UdpConnection/UdpConnection.hpp"
#include "../Client/Client.hpp"
#include "../../Entity/Sprite/Enemy/Enemy.hpp"
#include "../../Entity/Sprite/Player/Player.hpp"
#include "../../Entity/Sprite/Projectile/Projectile.hpp"
#include <memory>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <thread>
#include <string>
#include <vector>

class Lobby : public RTypeUdpCommand
{
public:
    Lobby(boost::asio::io_context &context, const std::string &name, Client *creator, size_t maxClient = 4);
    ~Lobby(void) = default;

    virtual void unknowUdpRequest(UdpConnection *connection, const std::string &command);
    void loadingBeam(UdpConnection *connection, const std::string &command);
    void beamShooted(UdpConnection *connection, const std::string &command);
    void playerDirection(UdpConnection *connection, const std::string &command);

    bool addClient(Client *newClient);
    bool removeClient(Client *client);
    void startGame(void);
    void stopGame(void);
    void gameLoop(void);

    const std::string &getName(void) const noexcept { return _name; }
    std::vector<Client *> &getClients(void) noexcept { return _clients; }
    const std::vector<Client *> &getClients(void) const noexcept { return _clients; }

private:
    void sendToClients(const std::string &command);

    const std::string _name;
    std::vector<Client *> _clients;
    std::thread _gameThread;
    const size_t _maxClient;
    bool _threadLoop;
    int _port;
    boost::asio::io_context &_context;
    boost::asio::ip::udp::endpoint _endpoint;
    UdpConnection::ptr _udpConnection;
    std::vector<std::shared_ptr<AEnemy>> _enemies;
    std::vector<std::shared_ptr<Player>> _players;
    std::vector<std::shared_ptr<Projectile>> _projectiles;

};

#endif /* LOBBY_HPP_ */
