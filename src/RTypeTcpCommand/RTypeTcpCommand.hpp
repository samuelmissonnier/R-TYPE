/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** RTypeTcpCommand.hpp
*/

#ifndef _RTYPETCPCOMMAND_HPP_
#define _RTYPETCPCOMMAND_HPP_

#include <map>
#include <string>
#include <functional>

class TcpConnection;

typedef std::map<std::string, std::function<void(TcpConnection*, const std::string&)>> Commands;

class RTypeTcpCommand {
public:
    RTypeTcpCommand(void) = default;
    ~RTypeTcpCommand(void) = default;

    virtual void unknowRequest(TcpConnection *connection, const std::string &message) = 0;

    const Commands &getCommands(void) const noexcept { return _commands; }

protected:
    Commands _commands;
};

#endif /* _RTYPETCPCOMMAND_HPP_ */
