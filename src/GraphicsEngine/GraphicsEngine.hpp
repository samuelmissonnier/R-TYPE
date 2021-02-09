/*
** EPITECH PROJECT, 2020
** Graphics
** File description:
** Graphics.hpp
*/

#ifndef GRAPHICS_HPP_
#define GRAPHICS_HPP_

#include <string>
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../UserEvent/UserEvent.hpp"
#include "../Entity/Entity.hpp"
#include <memory>

class IGraphics {
public:
    virtual ~IGraphics(void) = default;

public:
    /*
    ** Method to be implemented
    */
    virtual void display(const Entities &entity) = 0;

    virtual bool isWindowOpen(void) const noexcept = 0;

    virtual void closeWindow(void) = 0;

    virtual const std::vector<std::shared_ptr<IUserEvent>> &getUserEvent(void) = 0;

    virtual Position getMousePos(void) const noexcept = 0;
};

class AGraphics : public IGraphics {
public:
    virtual ~AGraphics(void) = default;

public:
    /*
    ** Method to be implemented
    */
    virtual void display(const Entities &entity) = 0;

    virtual bool isWindowOpen(void) const noexcept = 0;

    virtual void closeWindow(void) = 0;

    virtual const std::vector<std::shared_ptr<IUserEvent>> &getUserEvent(void) = 0;

    virtual Position getMousePos(void) const noexcept = 0;

protected:
    std::vector<std::shared_ptr<IUserEvent>> _userEvents;
};

#endif /* GRAPHICS_HPP_ */
