/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** InterfaceManager.cpp
*/

#include "InterfaceManager.hpp"
#include "Menu/Menu.hpp"
#include "Game/Game.hpp"
#include "ServerConnection/ServerConnection.hpp"
#include "Rooms/Rooms.hpp"
#include "GameLobby/GameLobby.hpp"
#include "CreateRoom/CreateRoom.hpp"
#include "Option/Option.hpp"
#include "MapCreator/MapCreator.hpp"
#include "EndGame/EndGame.hpp"

AInterfaceManager::AInterfaceManager(const InterfaceCreator &interfaceCreator, const size_t &beginIndex) :
    _interfaceIndex(beginIndex), _interfacesCreator(interfaceCreator)
{
    buildInterface(beginIndex);
}

size_t AInterfaceManager::updateActiveInterface(const std::vector<std::shared_ptr<IUserEvent> > &userEvents,
                                                const Position &mousePos, double deltaTime)
{
    std::shared_ptr<IInterface> &interface = _interfaces.at(_interfaceIndex);
    interface->setDeltaTime(deltaTime);
    interface->setMousePos(mousePos);
    size_t ret = interface->handleUserEvent(userEvents);
    if (ret) {
        size_t index = ret - 1;
        if (index < _interfacesCreator.size() && index != _interfaceIndex) {
            if (_interfaces.find(index) == _interfaces.end())
                buildInterface(index);
            _interfaces.erase(_interfaceIndex);
            _interfaceIndex = index;
        }
    }
    return ret;
}

void AInterfaceManager::buildInterface(size_t index)
{
    if (index < _interfacesCreator.size())
        _interfaces[index] = _interfacesCreator[index]();
}

std::shared_ptr<IInterface> AInterfaceManager::getCurrentInterface(void) const noexcept
{
    return _interfaces.at(_interfaceIndex);
}

std::shared_ptr<IInterface> AInterfaceManager::getInterface(size_t index) const noexcept
{
    if (index < _interfacesCreator.size()) {
        if (_interfaces.find(index) == _interfaces.end())
            return nullptr;
        return _interfaces.at(index);
    }
    return nullptr;
}

std::shared_ptr<IInterface> AInterfaceManager::getInterface(size_t index) noexcept
{
    if (index < _interfacesCreator.size()) {
        if (_interfaces.find(index) == _interfaces.end())
            buildInterface(index);
        return _interfaces.at(index);
    }
    return nullptr;
}

const Entities &AInterfaceManager::getActiveEntity(void) const noexcept
{
    return _interfaces.at(_interfaceIndex)->showActiveEntity();
}

InterfaceManager::InterfaceManager(void) :
    AInterfaceManager(InterfaceCreator({
        Menu::getInstance,
        Option::getInstance,
        Rooms::getInstance,
        CreateRoom::getInstance,
        ServerConnection::getInstance,
        GameLobby::getInstance,
        Game::getInstance,
        MapCreator::getInstance,
        EndGame::getInstance}))
{}
