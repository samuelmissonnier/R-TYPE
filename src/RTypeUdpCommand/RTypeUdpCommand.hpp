/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** RTypeUdpCommand.hpp
*/

#ifndef _RTYPEUDPCOMMAND_HPP_
#define _RTYPEUDPCOMMAND_HPP_

class UdpConnection;

#include <map>
#include <string>
#include <functional>

typedef std::map<std::string, std::function<void(UdpConnection*, const std::string&)>> UdpCommands;

class RTypeUdpCommand {
public:
    RTypeUdpCommand(void) = default;
    ~RTypeUdpCommand(void) = default;

    virtual void unknowUdpRequest(UdpConnection *connection, const std::string &message) = 0;

    const UdpCommands &getUdpCommands(void) const noexcept { return _udpCommands; }

protected:
    UdpCommands _udpCommands;
};

#endif /* _RTYPEUDPCOMMAND_HPP_ */
