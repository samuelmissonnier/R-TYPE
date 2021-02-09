/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** RTypeServer.cpp
*/

#include "RTypeServer.hpp"
#include "../Utils/ServerUtils.hpp"
#include "../Properties/ServerProperties.hpp"
#include "../Logger/Logger.hpp"
#include "../RTypeException/RTypeServerException.hpp"
#include <iostream>
#include <boost/bind.hpp>
#include <vector>
#include "../DLLoader/EnemyGenerator.hpp"

RTypeServer::RTypeServer(const int &port, boost::asio::io_context &context) :
    _context(context),
    _endpoint(boost::asio::ip::tcp::v4(), port),
    _acceptor(_context, _endpoint)
{
    using std::placeholders::_1;
    using std::placeholders::_2;
    _commands["100"] = std::bind(&RTypeServer::login, this, _1, _2);
    _commands["110"] = std::bind(&RTypeServer::disconnect, this, _1, _2);
    _commands["120"] = std::bind(&RTypeServer::createGame, this, _1, _2);
    _commands["140"] = std::bind(&RTypeServer::joinGame, this, _1, _2);
    _commands["150"] = std::bind(&RTypeServer::leaveGame, this, _1, _2);
    _commands["170"] = std::bind(&RTypeServer::clientReady, this, _1, _2);
    _commands["180"] = std::bind(&RTypeServer::clientNotReady, this, _1, _2);
    asyncWaitForNewConnection();
}

void RTypeServer::unknowRequest(TcpConnection *connection, const std::string &command)
{
    (void)connection;
    std::cerr << Logger::log(LogLvl::WARNING, "Unknow request: " + command) << std::endl;
}

void RTypeServer::login(TcpConnection *connection, const std::string &command)
{
    std::vector<std::string> args = RTypeUtils::getArgs(command);
    bool alreadyExist = false;

    try {
        Client *client = getClient(connection);
        for (auto client : _clients)
            if (client->getName() == args[0])
                alreadyExist = true;
        if (alreadyExist) {
            std::cerr << Logger::log(LogLvl::LOG, "Client name already assign: " + command) << std::endl;
            connection->write("102{\"User already exist\";}");
        } else {
            client->setName(args[0]);
            std::cerr << Logger::log(LogLvl::LOG, "Welcome \"" + args[0] + "\"") << std::endl;
            connection->write("101{}");
            sleep(1);
            sendGameList(client);
        }
    } catch (RTypeServerException &e) {
        std::cerr << Logger::log(LogLvl::ERROR, "Client unreachable:" + command) << std::endl;
        connection->write("102{\"User unreachable\";}");
    }
}

void RTypeServer::disconnect(TcpConnection *connection, const std::string &command)
{
    try {
        Client *client = getClient(connection);
        for (size_t i = 0; i < _clients.size(); i++) {
            if (_clients[i]->getConnection() == connection) {
                std::cerr << Logger::log(LogLvl::LOG, "\"" + client->getName() + "\" left the server") << std::endl;
                if (client->getLobby() != nullptr)
                    leaveGame(client->getConnection(), "150{}");
                _clients.erase(_clients.begin() + i);
                break;
            }
        }
    } catch (RTypeServerException &e) {
        std::cerr << Logger::log(LogLvl::ERROR, "Client unreachable:" + command) << std::endl;
        connection->write("122{\"User unreachable\";}");
    }
}

void RTypeServer::createGame(TcpConnection *connection, const std::string &command)
{
    std::vector<std::string> args = RTypeUtils::getArgs(command);
    bool alreadyExist = false;

    try {
        Client *client = getClient(connection);
        for (auto &lobby : _lobbies)
            if (lobby->getName() == args[0])
                alreadyExist = true;
        if (alreadyExist) {
            std::cerr << Logger::log(LogLvl::LOG, "Game name already assign: " + command) << std::endl;
            connection->write("122{\"Game already exist\";}");
        } else {
            _lobbies.push_back(std::shared_ptr<Lobby>(new Lobby(_context, args[0], client)));
            connection->write("121{\"" + args[0] + "\";}");
            updateGamePlayerList(client->getLobby());
            updateGameList();
        }
    } catch (RTypeServerException &e) {
        std::cerr << Logger::log(LogLvl::ERROR, "Client unreachable:" + command) << std::endl;
        connection->write("122{\"User unreachable\";}");
    }
}

void RTypeServer::joinGame(TcpConnection *connection, const std::string &command)
{
    std::vector<std::string> args = RTypeUtils::getArgs(command);
    bool gameJoin = false;

    try {
        Client *client = getClient(connection);
        for (auto lobby : _lobbies) {
            if (lobby.get()->getName() == args[0]) {
                gameJoin = true;
                std::cerr << Logger::log(LogLvl::LOG, client->getName() + " joined " + lobby->getName()) << std::endl;
                if (lobby->addClient(client)) {
                    connection->write("141{\"" + lobby->getName() + "\";}");
                    updateGamePlayerList(client->getLobby());
                } else {
                    std::cerr << Logger::log(LogLvl::LOG, "Lobby capacity full: " + command) << std::endl;
                    connection->write("142{\"Couldn't join game\";}");
                }
                break;
            }
        }
        if (!gameJoin) {
            std::cerr << Logger::log(LogLvl::WARNING, "Cannot join game: " + command) << std::endl;
            connection->write("142{\"Couldn't join game\";}");
        }
    } catch (RTypeServerException &e) {
        std::cerr << Logger::log(LogLvl::ERROR, "Client unreachable:" + command) << std::endl;
        connection->write("142{\"User unreachable\";}");
    }
}

void RTypeServer::leaveGame(TcpConnection *connection, const std::string &command)
{
    try {
        Client *client = getClient(connection);
        Lobby *lobby = client->getLobby();
        if (client->getLobby()->removeClient(client)) {
            std::cerr << Logger::log(LogLvl::LOG, client->getName() + " left " + lobby->getName()) << std::endl;
            connection->write("151{}");
            updateGamePlayerList(lobby);
            updateGameList();
        } else {
            std::cerr << Logger::log(LogLvl::WARNING, "Cannot leave game: " + command) << std::endl;
            connection->write("152{\"Couldn't left the game\";}");
        }
    } catch (RTypeServerException &e) {
        std::cerr << Logger::log(LogLvl::ERROR, "Client unreachable:" + command) << std::endl;
        connection->write("152{\"User unreachable\";}");
    }
}

void RTypeServer::clientReady(TcpConnection *connection, const std::string &command)
{
    try {
        Client *client = getClient(connection);
        client->ready();
        std::cerr << Logger::log(LogLvl::LOG, client->getName() + " is now ready") << std::endl;
        connection->write("171{}");
        updateGamePlayerList(client->getLobby());
        checkStartGame(client->getLobby());
    } catch (RTypeServerException &e) {
        std::cerr << Logger::log(LogLvl::ERROR, "Client unreachable:" + command) << std::endl;
        connection->write("172{\"Couldn't set is state as ready\";}");
    }
}

void RTypeServer::clientNotReady(TcpConnection *connection, const std::string &command)
{
    try {
        Client *client = getClient(connection);
        client->notReady();
        std::cerr << Logger::log(LogLvl::LOG, client->getName() + " is not ready") << std::endl;
        connection->write("181{}");
        updateGamePlayerList(client->getLobby());
    } catch (RTypeServerException &e) {
        std::cerr << Logger::log(LogLvl::ERROR, "Client unreachable:" + command) << std::endl;
        connection->write("182{\"Couldn't set is state as not ready\";}");
    }
}

void RTypeServer::checkStartGame(Lobby *lobby)
{
    bool playersReady = true;
    for (auto client : lobby->getClients())
        if (!client->isReady())
            playersReady = false;
    if (playersReady) {
        EnemyGenerator generator(ServerProperties::_directPath + "/build/lib/");
        auto enemies = generator.getEnemies(ServerProperties::_directPath + "/map/default.map");
        std::string data;
        for (auto enemy : enemies)
            data += enemy->toString();
        boost::asio::deadline_timer timer(_context, boost::posix_time::seconds(3));
        timer.wait();
        for (auto client : lobby->getClients())
            if (!client->isReady())
                playersReady = false;
        if (playersReady) {
            std::cerr << Logger::log(LogLvl::LOG, lobby->getName() + "start the game") << std::endl;
            for (size_t i = 0; i < lobby->getClients().size(); i++) {
                std::string serverdata("Data:{\""+ std::to_string(lobby->getClients().size()) + ":" + std::to_string(i) + "\";}");
                lobby->getClients()[i]->getConnection()->write("190{" + serverdata + " " + data + "}");
            }
            lobby->startGame();
        }
    }
}

void RTypeServer::updateGameList(void)
{
    std::cerr << Logger::log(LogLvl::LOG, "Send game list to all clients") << std::endl;
    for (auto client : _clients) {
        if (client->getLobby() == nullptr)
            sendGameList(client.get());
    }
}

void RTypeServer::sendGameList(Client *client)
{
    std::string msg = "";

    for (auto lobby : _lobbies)
        msg += "\"" + lobby->getName() + "\";";
    usleep(100);
    client->getConnection()->write("130{" + msg + "}");
}

void RTypeServer::updateGamePlayerList(Lobby *lobby)
{
    if (lobby->getClients().size() == 0) {
        std::cerr << Logger::log(LogLvl::LOG, "Destruction of lobby: " + lobby->getName()) << std::endl;
        lobby->stopGame();
        for (size_t i = 0; i < _lobbies.size(); i++)
            if (_lobbies[i]->getName() == lobby->getName())
                _lobbies.erase(_lobbies.begin() + i);
    } else {
        std::cerr << Logger::log(LogLvl::LOG, "Send game player list to all lobby clients") << std::endl;
        for (auto client : lobby->getClients())
            sendGamePlayerList(client);
    }
}

void RTypeServer::sendGamePlayerList(Client *client)
{
    std::string msg = "";

    for (auto clientName : client->getLobby()->getClients())
        msg += "\"" + clientName->getName() + " | " + (clientName->isReady() ? "ready" : "not ready") + "\";";
    usleep(100);
    client->getConnection()->write("160{" + msg + "}");
}

Client *RTypeServer::getClient(TcpConnection *connection, \
                               std::vector<std::shared_ptr<Client>> &clients)
{
    for (auto client : clients) {
        if (client->getConnection() == connection) {
            return client.get();
        }
    }
    throw RTypeServerException("can't get client");
}

Client *RTypeServer::getClient(TcpConnection *connection)
{
    return getClient(connection, _clients);
}

void RTypeServer::asyncWaitForNewConnection(void)
{
    TcpConnection::ptr newConnection = TcpConnection::pointerCreate(_context, this);

    _acceptor.async_accept(newConnection->getSocket(), boost::bind(&RTypeServer::handleAccept, this, newConnection, boost::asio::placeholders::error));
}

void RTypeServer::handleAccept(TcpConnection::ptr newConnection, const boost::system::error_code &error)
{
    if (!error) {
        _clients.push_back(std::shared_ptr<Client>(new Client(newConnection)));
        newConnection->read();
    } else
        std::cerr << Logger::log(LogLvl::ERROR, error.message()) << std::endl;
    asyncWaitForNewConnection();
}
