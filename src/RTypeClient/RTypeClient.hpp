/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** RTypeClient.hpp
*/

#ifndef _RTYPECLIENT_HPP_
#define _RTYPECLIENT_HPP_

#include "../RTypeTcpCommand/RTypeTcpCommand.hpp"
#include "../RTypeUdpCommand/RTypeUdpCommand.hpp"
#include "../TcpConnection/TcpConnection.hpp"
#include "../UdpConnection/UdpConnection.hpp"
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <thread>

class RTypeClient : public RTypeTcpCommand, public RTypeUdpCommand {
public:;
    RTypeClient(const std::string &ip, const int &port, const std::string &username);
    virtual ~RTypeClient(void);

    virtual void unknowUdpRequest(UdpConnection *connection, const std::string &command);
    void sendPlayerBeamLoading(UdpConnection *connection, const std::string &command);
    void sendPlayerBeamShooted(UdpConnection *connection, const std::string &command);
    void sendPlayerDirection(UdpConnection *connection, const std::string &command);
    void sendPlayerEnemyShoot(UdpConnection *connection, const std::string &command);
    void updateEntitiesPosition(UdpConnection *connection, const std::string &command);

    virtual void unknowRequest(TcpConnection *connection, const std::string &command);
    void loginSuccess(TcpConnection *connection, const std::string &command);
    void loginFailure(TcpConnection *connection, const std::string &command);
    void createGameSuccess(TcpConnection *connection, const std::string &command);
    void createGameFailure(TcpConnection *connection, const std::string &command);
    void updateGameList(TcpConnection *connection, const std::string &command);
    void joinGameSuccess(TcpConnection *connection, const std::string &command);
    void joinGameFailure(TcpConnection *connection, const std::string &command);
    void leftGameSuccess(TcpConnection *connection, const std::string &command);
    void leftGameFailure(TcpConnection *connection, const std::string &command);
    void updatePlayerList(TcpConnection *connection, const std::string &command);
    void readySuccess(TcpConnection *connection, const std::string &command);
    void readyFailure(TcpConnection *connection, const std::string &command);
    void unreadySuccess(TcpConnection *connection, const std::string &command);
    void unreadyFailure(TcpConnection *connection, const std::string &command);
    void startGame(TcpConnection *connection, const std::string &command);

    void sendRequest(size_t tag, const std::string &data);
    void sendRequest(const std::string &request);

    const std::string &getUserName(void) const noexcept { return _username; }

private:
    void connect(void);
    void handleConnect(TcpConnection::ptr newConnection, const boost::system::error_code &error);

    std::string _ip;
    int _port;
    boost::asio::io_context _context;
    std::thread _thread;
    boost::asio::ip::tcp::endpoint _endpoint;
    std::string _username;
    TcpConnection::ptr _connection;
    bool _isConnect;
    UdpConnection::ptr _udpConnection;
};

#endif /* _RTYPECLIENT_HPP_ */
