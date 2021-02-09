/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** NetworkInterface
*/

#include "NetworkInterface.hpp"

NetworkInterface::NetworkInterface(void) :
    _state(ConnectionState::Disconnected)
{}

void NetworkInterface::setConnectionState(ConnectionState state) noexcept
{
    _state = state;
}
