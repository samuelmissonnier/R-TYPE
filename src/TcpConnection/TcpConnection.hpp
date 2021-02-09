/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TcpConnection.hpp
*/

#ifndef _TCPCONNECTION_HPP_
#define _TCPCONNECTION_HPP_

#include "../RTypeTcpCommand/RTypeTcpCommand.hpp"
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/array.hpp>

class TcpConnection : public boost::enable_shared_from_this<TcpConnection> {
public:
    TcpConnection(boost::asio::io_context &context, RTypeTcpCommand *rtypeTcpCommand);
    virtual ~TcpConnection(void) = default;

    typedef boost::shared_ptr<TcpConnection> ptr;
    static ptr pointerCreate(boost::asio::io_context &context, RTypeTcpCommand *rtypeTcpCommand);
    void write(const std::string &str);
    void read(void);
    boost::asio::ip::tcp::socket &getSocket(void);

private:
    void handleWrite(const boost::system::error_code &error);
    void handleRead(const boost::system::error_code &error, size_t number_bytes_read);

    RTypeTcpCommand *_rtypeTcpCommand;
    boost::asio::ip::tcp::socket _socket;
    std::string _msg;
    boost::array<char, 2048> _networkBuffer;
};

#endif /* _TCPCONNECTION_HPP_ */
