/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** UdpConnection.hpp
*/

#ifndef _UDPCONNECTION_HPP_
#define _UDPCONNECTION_HPP_

#include "../RTypeUdpCommand/RTypeUdpCommand.hpp"
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/enable_shared_from_this.hpp>

class UdpConnection : public boost::enable_shared_from_this<UdpConnection> {
public:
    UdpConnection(boost::asio::io_context &context, const std::string &ip, const int &port, bool isServer, RTypeUdpCommand *rtypeUdpCommand);
    ~UdpConnection(void) = default;

    typedef boost::shared_ptr<UdpConnection> ptr;
    static ptr pointerCreate(boost::asio::io_context &context, const std::string &ip, const int &port, bool isServer, RTypeUdpCommand *rtypeUdpCommand);
    void write(const std::string &str, boost::asio::ip::udp::endpoint endpoint);
    void read(void);
    boost::asio::ip::udp::socket &getSocket(void);
    boost::asio::ip::udp::endpoint getEndpoint(void);
    std::vector<boost::asio::ip::udp::endpoint> getEndpoints(void);

private:
    void handleWrite(const boost::system::error_code &error);
    //void handleRead(const boost::system::error_code &error);
    void handleRead(const boost::system::error_code &error, size_t number_bytes_read);

    RTypeUdpCommand *_rtypeUdpCommand;
    boost::asio::io_context &_context;
    boost::asio::ip::udp::endpoint _endpoint;
    boost::asio::ip::udp::socket _socket;
    std::vector<boost::asio::ip::udp::endpoint> _remoteEndpoints;
    std::string _msg;
    boost::array<char, 1024> _networkBuffer;
};

#endif /* _UDPCONNECTION_HPP_ */
