/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** NetworkInterface.hpp
*/

#ifndef NETWORK_INTERFACE_HPP_
#define NETWORK_INTERFACE_HPP_

enum ConnectionState {Disconnected, Connecting, Connected};

class NetworkInterface {
public:
    NetworkInterface(void);
    ~NetworkInterface(void) = default;

    ConnectionState getConnectionState(void) const noexcept { return _state; }

    virtual void setConnectionState(ConnectionState state) noexcept;

private:
    ConnectionState _state;
};

#endif /* NETWORK_INTERFACE_HPP_ */
