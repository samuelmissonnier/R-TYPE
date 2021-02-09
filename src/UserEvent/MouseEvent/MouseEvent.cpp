/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** MouseEvent.cpp
*/

#include "MouseEvent.hpp"

MouseEvent::MouseEvent(MouseButtonType buttonType, StateEvent::EventState mouseState) :
    AUserEvent(IUserEvent::EventType::MOUSE_EVENT), StateEvent(mouseState),
    _buttonType(buttonType)
{}

MouseEvent::MouseButtonType MouseEvent::getButtonType(void) const noexcept
{
    return _buttonType;
}

std::ostream &operator<<(std::ostream &os, MouseEvent::MouseButtonType mouseType)
{
    switch (mouseType) {
    case MouseEvent::MouseButtonType::LEFT:
        os << "Left";
        break;
    case MouseEvent::MouseButtonType::RIGHT:
        os << "Right";
        break;
    case MouseEvent::MouseButtonType::WHEEL:
        os << "Wheel";
        break;
    default:
        os << "Extra button";
        break;
    }
    return os;
}
