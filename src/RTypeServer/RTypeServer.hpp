/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** RTypeServer.hpp
*/

#ifndef _RTYPESERVER_HPP_
#define _RTYPESERVER_HPP_

#include "../RTypeTcpCommand/RTypeTcpCommand.hpp"
#include "../TcpConnection/TcpConnection.hpp"
#include "../ServerDataManagement/Client/Client.hpp"
#include "../ServerDataManagement/Lobby/Lobby.hpp"
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <vector>

class RTypeServer : public RTypeTcpCommand
{
public:
    RTypeServer(const int &port, boost::asio::io_context &context);
    virtual ~RTypeServer(void) = default;

    virtual void unknowRequest(TcpConnection *connection, const std::string &command);
    void login(TcpConnection *connection, const std::string &command);
    void disconnect(TcpConnection *connection, const std::string &command);
    void createGame(TcpConnection *connection, const std::string &command);
    void joinGame(TcpConnection *connection, const std::string &command);
    void leaveGame(TcpConnection *connection, const std::string &command);
    void clientReady(TcpConnection *connection, const std::string &command);
    void clientNotReady(TcpConnection *connection, const std::string &command);

private:
    void checkStartGame(Lobby *lobby);
    void updateGameList(void);
    void sendGameList(Client *client);
    void updateGamePlayerList(Lobby *lobby);
    void sendGamePlayerList(Client *client);

    static Client *getClient(TcpConnection *connection, std::vector<std::shared_ptr<Client>> &clients);
    Client *getClient(TcpConnection *connection);

    void asyncWaitForNewConnection(void);
    void handleAccept(TcpConnection::ptr newConnection, const boost::system::error_code &error);

    boost::asio::io_context &_context;
    boost::asio::ip::tcp::endpoint _endpoint;
    boost::asio::ip::tcp::acceptor _acceptor;
    std::vector<std::shared_ptr<Client>> _clients;
    std::vector<std::shared_ptr<Lobby>> _lobbies;
};

#endif /* _RTYPESERVER_HPP_ */
