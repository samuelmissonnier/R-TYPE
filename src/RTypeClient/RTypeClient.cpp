/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** RTypeClient.cpp
*/

#include "RTypeClient.hpp"
#include <boost/bind.hpp>
#include <iostream>
#include "../Properties/ClientProperties.hpp"
#include "../Interfaces/ServerConnection/ServerConnection.hpp"
#include "../Interfaces/Rooms/Rooms.hpp"
#include "../Interfaces/CreateRoom/CreateRoom.hpp"
#include "../Interfaces/GameLobby/GameLobby.hpp"
#include "../Interfaces/Game/Game.hpp"
#include "../Utils/ClientUtils.hpp"
#include "../Logger/Logger.hpp"

RTypeClient::RTypeClient(const std::string &ip, const int &port, const std::string &username) :
    _ip(ip),
    _port(port),
    _endpoint(boost::asio::ip::address::from_string(ip), port),
    _username(username),
    _isConnect(false)
{
    connect();
    using std::placeholders::_1;
    using std::placeholders::_2;
    _udpCommands["211"] = std::bind(&RTypeClient::sendPlayerBeamLoading, this, _1, _2);
    _udpCommands["221"] = std::bind(&RTypeClient::sendPlayerBeamShooted, this, _1, _2);
    _udpCommands["231"] = std::bind(&RTypeClient::sendPlayerDirection, this, _1, _2);
    _udpCommands["240"] = std::bind(&RTypeClient::sendPlayerEnemyShoot, this, _1, _2);
    _udpCommands["250"] = std::bind(&RTypeClient::updateEntitiesPosition, this, _1, _2);
    _commands["101"] = std::bind(&RTypeClient::loginSuccess, this, _1, _2);
    _commands["102"] = std::bind(&RTypeClient::loginFailure, this, _1, _2);
    _commands["121"] = std::bind(&RTypeClient::createGameSuccess, this, _1, _2);
    _commands["122"] = std::bind(&RTypeClient::createGameFailure, this, _1, _2);
    _commands["130"] = std::bind(&RTypeClient::updateGameList, this, _1, _2);
    _commands["141"] = std::bind(&RTypeClient::joinGameSuccess, this, _1, _2);
    _commands["142"] = std::bind(&RTypeClient::joinGameFailure, this, _1, _2);
    _commands["151"] = std::bind(&RTypeClient::leftGameSuccess, this, _1, _2);
    _commands["152"] = std::bind(&RTypeClient::leftGameFailure, this, _1, _2);
    _commands["160"] = std::bind(&RTypeClient::updatePlayerList, this, _1, _2);
    _commands["171"] = std::bind(&RTypeClient::readySuccess, this, _1, _2);
    _commands["172"] = std::bind(&RTypeClient::readyFailure, this, _1, _2);
    _commands["181"] = std::bind(&RTypeClient::unreadySuccess, this, _1, _2);
    _commands["182"] = std::bind(&RTypeClient::unreadyFailure, this, _1, _2);
    _commands["190"] = std::bind(&RTypeClient::startGame, this, _1, _2);
    _thread = std::thread([this](){
                _context.run();
                          });
    _thread.detach();
}

RTypeClient::~RTypeClient(void)
{
    _context.stop();
    _thread.std::thread::~thread();
    if (_isConnect)
        _connection->write("110{\"" + _username + "\";}");
}


void RTypeClient::unknowUdpRequest(UdpConnection *connection, const std::string &command)
{
    (void)connection;
    std::cerr << Logger::log(LogLvl::WARNING, "Unknow request: " + command) << std::endl;
}

void RTypeClient::sendPlayerBeamLoading(UdpConnection *connection, const std::string &command)
{
    
}

void RTypeClient::sendPlayerBeamShooted(UdpConnection *connection, const std::string &command)
{
    
}

void RTypeClient::sendPlayerDirection(UdpConnection *connection, const std::string &command)
{
    
}

void RTypeClient::sendPlayerEnemyShoot(UdpConnection *connection, const std::string &command)
{
    
}

void RTypeClient::updateEntitiesPosition(UdpConnection *connection, const std::string &command)
{
    
}

/*
** Request command
*/
void RTypeClient::unknowRequest(TcpConnection *connection, const std::string &command)
{
    (void)connection;
    std::cerr << Logger::log(LogLvl::WARNING, "Unknow request: " + command) << std::endl;
}

void RTypeClient::loginSuccess(TcpConnection *connection, const std::string &command)
{
    _isConnect = true;
    auto connectionInterface = ServerConnection::getInterface();
    if (connectionInterface) {
        connectionInterface->setConnectionState(ConnectionState::Connected);
        updateGameList(connection, command);
    } else
        Logger::log(LogLvl::ERROR, "Couldn't get interface");
}

void RTypeClient::loginFailure(TcpConnection *connection, const std::string &command)
{
    (void)connection;
    auto interface = ServerConnection::getInterface();
    if (interface) {
        interface->getErrorText()->display(std::wstring(command.begin(), command.end()));
        interface->setConnectionState(ConnectionState::Disconnected);
    } else
        Logger::log(LogLvl::ERROR, command);
}

void RTypeClient::createGameSuccess(TcpConnection *connection, const std::string &command)
{
    auto createRoomInterface = CreateRoom::getInterface();
    auto lobbyInterface = GameLobby::getInterface();
    if (createRoomInterface && lobbyInterface) {
        auto args = ClientUtils::getArgs(command);
        createRoomInterface->setConnectionState(ConnectionState::Connected);
        lobbyInterface->setRoomName(args[0]);
        updatePlayerList(connection, command);
    } else
        Logger::log(LogLvl::ERROR, "Couldn't get interface");
}

void RTypeClient::createGameFailure(TcpConnection *connection, const std::string &command)
{
    (void)connection;
    auto createRoomInterface = CreateRoom::getInterface();
    if (createRoomInterface) {
        createRoomInterface->getErrorText()->display(std::wstring(command.begin(), command.end()));
        createRoomInterface->setConnectionState(ConnectionState::Disconnected);
    } else
        Logger::log(LogLvl::ERROR, command);
}

void RTypeClient::updateGameList(TcpConnection *connection, const std::string &command)
{
    (void)connection;
    auto interface = Rooms::getInterface();
    if (interface) {
        auto args = RTypeUtils::getArgs(command);
        for (auto it : args)
            std::cerr << Logger::log(LogLvl::LOG, it) << std::endl;
        interface->reloadRooms(args);
    } else
        Logger::log(LogLvl::ERROR, "Couldn't get interface");
}

void RTypeClient::joinGameSuccess(TcpConnection *connection, const std::string &command)
{
    auto roomsInterface = Rooms::getInterface();
    auto lobbyInterface = GameLobby::getInterface();
    if (roomsInterface && lobbyInterface) {
        auto args = ClientUtils::getArgs(command);
        roomsInterface->setConnectionState(ConnectionState::Connected);
        lobbyInterface->setRoomName(args[0] + ":");
        updatePlayerList(connection, command);
    } else
        Logger::log(LogLvl::ERROR, "Couldn't get interface");
}

void RTypeClient::joinGameFailure(TcpConnection *connection, const std::string &command)
{
    (void)connection;
    auto roomsInterface = Rooms::getInterface();
    if (roomsInterface) {
        roomsInterface->getErrorText()->display(std::wstring(command.begin(), command.end()));
        roomsInterface->setConnectionState(ConnectionState::Disconnected);
    } else
        Logger::log(LogLvl::ERROR, command);
}

void RTypeClient::leftGameSuccess(TcpConnection *connection, const std::string &command)
{
    (void)connection;
    (void)command;
    auto gameLobby = GameLobby::getInterface();
    if (gameLobby) {
        gameLobby->setConnectionState(ConnectionState::Connected);
    } else
        Logger::log(LogLvl::ERROR, "Couldn't get interface");
}

void RTypeClient::leftGameFailure(TcpConnection *connection, const std::string &command)
{
    (void)connection;
    auto gameLobby = GameLobby::getInterface();
    if (gameLobby) {
        gameLobby->getErrorText()->display(std::wstring(command.begin(), command.end()));
        gameLobby->setConnectionState(ConnectionState::Disconnected);
    } else
        Logger::log(LogLvl::ERROR, command);
}

void RTypeClient::updatePlayerList(TcpConnection *connection, const std::string &command)
{
    (void)connection;
    auto gameLobby = GameLobby::getInterface();
    if (gameLobby) {
        auto args = RTypeUtils::getArgs(command);
        gameLobby->reloadPlayersName(args);
    } else
        Logger::log(LogLvl::ERROR, "Couldn't get interface");
}

void RTypeClient::readySuccess(TcpConnection *connection, const std::string &command)
{
    (void)connection;
    (void)command;
    auto gameLobby = GameLobby::getInterface();
    if (gameLobby) {
        gameLobby->setConnectionState(ConnectionState::Connected);
    } else
        Logger::log(LogLvl::ERROR, "Couldn't get interface");
}

void RTypeClient::readyFailure(TcpConnection *connection, const std::string &command)
{
    (void)connection;
    auto gameLobby = GameLobby::getInterface();
    if (gameLobby) {
        gameLobby->getErrorText()->display(std::wstring(command.begin(), command.end()));
        gameLobby->setConnectionState(ConnectionState::Disconnected);
    } else
        Logger::log(LogLvl::ERROR, command);
}

void RTypeClient::unreadySuccess(TcpConnection *connection, const std::string &command)
{
    (void)connection;
    (void)command;
    auto gameLobby = GameLobby::getInterface();
    if (gameLobby) {
        gameLobby->setConnectionState(ConnectionState::Connected);
    } else
        Logger::log(LogLvl::ERROR, "Couldn't get interface");
}

void RTypeClient::unreadyFailure(TcpConnection *connection, const std::string &command)
{
    (void)connection;
    auto gameLobby = GameLobby::getInterface();
    if (gameLobby) {
        gameLobby->getErrorText()->display(std::wstring(command.begin(), command.end()));
        gameLobby->setConnectionState(ConnectionState::Disconnected);
    } else
        Logger::log(LogLvl::ERROR, command);
}

void RTypeClient::startGame(TcpConnection *connection, const std::string &command)
{
    (void)connection;
    auto gameLobby = GameLobby::getInterface();
    auto game = Game::getInterface();
    if (gameLobby && game) {
        auto args = RTypeUtils::getArgs(command);
        auto args2 = RTypeUtils::splitVector(std::vector<std::string>(args.begin() + 1,  args.end()), 11);
        std::vector<AEntity *> entities;
        for (auto enemy : args2)
            entities.push_back(new AEnemy(enemy));
        game->updateEntites(entities);
        auto dataParams = RTypeUtils::getStringSep(args[0], ":");
        game->setPlayerIndex(std::stoi(dataParams[1]));
        game->addPlayers(std::stoi(dataParams[0]));
        gameLobby->launchGame();
        UdpConnection::ptr newUdp = UdpConnection::pointerCreate(_context, _ip, 7172, false, this);
        _udpConnection = newUdp;
        _udpConnection->read();
    } else
        Logger::log(LogLvl::ERROR, command);
}

/* End request command */


void RTypeClient::sendRequest(size_t tag, const std::string &data)
{
    sendRequest(std::to_string(tag) + data);
}

void RTypeClient::sendRequest(const std::string &request)
{
    _connection->write(request);
}

void RTypeClient::connect(void)
{
    TcpConnection::ptr newConnection = TcpConnection::pointerCreate(_context, this);

    _connection = newConnection;
    boost::asio::ip::tcp::socket &socket = newConnection->getSocket();
    socket.async_connect(_endpoint, boost::bind(&RTypeClient::handleConnect, this, newConnection, boost::asio::placeholders::error));
}

void RTypeClient::handleConnect(TcpConnection::ptr newConnection, const boost::system::error_code &error)
{
    if (!error) {
        newConnection->write("100{\"" + _username + "\";}");
    } else {
        auto interface = ServerConnection::getInterface();
        if (interface) {
            interface->setConnectionState(ConnectionState::Disconnected);
            std::string message(error.message());
            interface->setErrorText(std::wstring(message.begin(), message.end()));
        } else
            std::cerr << Logger::log(LogLvl::ERROR, "error: " + error.message()) << std::endl;
    }
}
