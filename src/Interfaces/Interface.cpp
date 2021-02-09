/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Interface.cpp
*/

#include "Interface.hpp"
#include "InterfaceManager.hpp"
#include "../Properties/ClientProperties.hpp"

AInterface::AInterface(void) :
    _closeWindow(false), _mousePos(0, 0), _deltaTime(0),
    _errorText(new LimitedText(ClientProperties::_directPath + "/rsrc/font/SEASRN__.ttf", {0, 0}, 25))
{}

void AInterface::setDeltaTime(double deltaTime) noexcept
{
    _deltaTime = deltaTime;
}

void AInterface::setMousePos(const Position &pos) noexcept
{
    _mousePos = pos;
}
