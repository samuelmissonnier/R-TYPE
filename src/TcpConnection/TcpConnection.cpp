/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TcpConnection.cpp
*/

#include "TcpConnection.hpp"
#include <boost/bind.hpp>
#include <iostream>
#include "../Logger/Logger.hpp"

TcpConnection::TcpConnection(boost::asio::io_context &context, RTypeTcpCommand *rtypeTcpCommand) :
    _rtypeTcpCommand(rtypeTcpCommand),
    _socket(context)
{
}

TcpConnection::ptr TcpConnection::pointerCreate(boost::asio::io_context &context, RTypeTcpCommand *RTypeTcpCommand)
{
    return TcpConnection::ptr(new TcpConnection(context, RTypeTcpCommand));
}

void TcpConnection::write(const std::string &str)
{
    boost::asio::async_write(_socket, boost::asio::buffer(str), boost::bind(&TcpConnection::handleWrite, shared_from_this(), boost::asio::placeholders::error));
    std::cerr << Logger::log(LogLvl::LOG, "write: " + str) << std::endl;
}

void TcpConnection::read(void)
{
    boost::asio::async_read(_socket, boost::asio::buffer(_networkBuffer), boost::asio::transfer_at_least(3), boost::bind(&TcpConnection::handleRead, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

boost::asio::ip::tcp::socket &TcpConnection::getSocket(void)
{
    return _socket;
}

void TcpConnection::handleWrite(const boost::system::error_code &error)
{
    if (!error) {
        read();
    } else {
        std::cerr << error.message();
    }
}

void TcpConnection::handleRead(const boost::system::error_code& error, size_t number_bytes_read)
{
    if (!error) {
        _msg.clear();
        for (size_t i = 0; i < number_bytes_read; i++)
            _msg += _networkBuffer[i];
        std::cerr << Logger::log(LogLvl::LOG, "read: " + _msg) << std::endl;
        size_t find = _msg.find('{');
        if (find != std::string::npos && find + 1 != std::string::npos) {
            std::string code(_msg.substr(0, find));
            if (_rtypeTcpCommand->getCommands().find(code) != _rtypeTcpCommand->getCommands().end())
                _rtypeTcpCommand->getCommands().at(code)(this, _msg);
            else
                _rtypeTcpCommand->unknowRequest(this, _msg);
        }
        read();
    } else {
        std::cerr << Logger::log(LogLvl::ERROR, "Read: " + error.message()) << std::endl;
    }
}
