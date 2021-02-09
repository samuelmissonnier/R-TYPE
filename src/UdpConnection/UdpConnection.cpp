/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** UdpConnection.cpp
*/

#include "UdpConnection.hpp"
#include "../Logger/Logger.hpp"
#include <iostream>
#include <boost/bind.hpp>

UdpConnection::UdpConnection(boost::asio::io_context &context, const std::string &ip, const int &port, bool isServer, RTypeUdpCommand *rtypeUdpCommand) :
    _rtypeUdpCommand(rtypeUdpCommand),
    _context(context),
    _endpoint(boost::asio::ip::address::from_string(ip), port),
    _socket(_context)
{
    if (isServer) {
        _socket = boost::asio::ip::udp::socket(_context, _endpoint);
    } else {
        _socket = boost::asio::ip::udp::socket(_context);
        _socket.open(boost::asio::ip::udp::v4());
    }
}

UdpConnection::ptr UdpConnection::pointerCreate(boost::asio::io_context &context, const std::string &ip, const int &port, bool isServer, RTypeUdpCommand *rtypeUdpCommand)
{
    return UdpConnection::ptr(new UdpConnection(context, ip, port, isServer, rtypeUdpCommand));
}

void UdpConnection::write(const std::string &str, boost::asio::ip::udp::endpoint endpoint)
{
    _socket.async_send_to(boost::asio::buffer(str), endpoint, boost::bind(&UdpConnection::handleWrite, shared_from_this(), boost::asio::placeholders::error));
}

void UdpConnection::read(void)
{
    _socket.async_receive_from(boost::asio::buffer(_networkBuffer), _endpoint, boost::bind(&UdpConnection::handleRead, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred()));
}

boost::asio::ip::udp::socket &UdpConnection::getSocket(void)
{
    return _socket;
}

boost::asio::ip::udp::endpoint UdpConnection::getEndpoint(void)
{
    return _endpoint;
}

std::vector<boost::asio::ip::udp::endpoint> UdpConnection::getEndpoints(void)
{
    return _remoteEndpoints;
}

void UdpConnection::handleWrite(const boost::system::error_code &error)
{
    if (!error) {
        read();
    } else {
        std::cerr << error.message() << std::endl;
    }
}

void UdpConnection::handleRead(const boost::system::error_code &error, size_t number_bytes_read)
{
    bool exist = false;
    for (auto endpoint : _remoteEndpoints)
        if (_endpoint == endpoint)
            exist = true;
    _remoteEndpoints.push_back(_endpoint);
    if (!error) {
        _msg.clear();
        for (size_t i = 0; i < number_bytes_read; i++)
            _msg += _networkBuffer[i];
        std::cerr << Logger::log(LogLvl::LOG, "read: " + _msg) << std::endl;
        size_t find = _msg.find('{');
        if (find != std::string::npos && find + 1 != std::string::npos) {
            std::string code(_msg.substr(0, find));
            if (_rtypeUdpCommand->getUdpCommands().find(code) != _rtypeUdpCommand->getUdpCommands().end())
                _rtypeUdpCommand->getUdpCommands().at(code)(this, _msg);
            else
                _rtypeUdpCommand->unknowUdpRequest(this, _msg);
        }
        read();
    } else {
        std::cerr << Logger::log(LogLvl::ERROR, "Read: " + error.message()) << std::endl;
    }
}
