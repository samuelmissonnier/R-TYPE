/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** InterfaceManager.hpp
*/

#ifndef INTERFACE_MANAGER_HPP_
#define INTERFACE_MANAGER_HPP_

#include "Interface.hpp"
#include <functional>
#include <map>

class IInterfaceManager {
public:
    virtual ~IInterfaceManager(void) = default;

    virtual size_t updateActiveInterface(const std::vector<std::shared_ptr<IUserEvent>> &userEvents,
                      const Position &mousePos, double deltaTime) = 0;

    virtual const Entities &getActiveEntity(void) const noexcept = 0;

    virtual std::shared_ptr<IInterface> getCurrentInterface(void) const noexcept = 0;

    virtual std::shared_ptr<IInterface> getInterface(size_t interface) const noexcept = 0;

    virtual std::shared_ptr<IInterface> getInterface(size_t index) noexcept = 0;

private:
    virtual void buildInterface(size_t index) = 0;
};

typedef std::vector<std::function<std::shared_ptr<IInterface>()>> InterfaceCreator;

class AInterfaceManager : public IInterfaceManager {
public:
    AInterfaceManager(const InterfaceCreator &interfaceCreator, const size_t &beginIndex = 0);
    ~AInterfaceManager(void) = default;

    virtual size_t updateActiveInterface(const std::vector<std::shared_ptr<IUserEvent>> &userEvents,
                      const Position &mousePos, double deltaTime);

    virtual const Entities &getActiveEntity(void) const noexcept;

    virtual std::shared_ptr<IInterface> getCurrentInterface(void) const noexcept;

    virtual std::shared_ptr<IInterface> getInterface(size_t index) const noexcept;

    virtual std::shared_ptr<IInterface> getInterface(size_t index) noexcept;

private:
    virtual void buildInterface(size_t index);

private:
    size_t _interfaceIndex;

protected:
    std::map<int, std::shared_ptr<IInterface>> _interfaces;

private:
    const InterfaceCreator _interfacesCreator;
};

class InterfaceManager : public AInterfaceManager {
public:
    enum Interface {Closing, Menu, Option, Rooms, CreateRoom, ServerConnection, GameLobby, Game, MapCreator, EndGame};

    InterfaceManager(void);
    ~InterfaceManager(void) = default;
};

#endif /* INTERFACE_MANAGER_HPP_ */
