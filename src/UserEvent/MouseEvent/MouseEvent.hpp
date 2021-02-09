/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** MouseEvent.hpp
*/

#ifndef MOUSE_EVENT_HPP_
#define MOUSE_EVENT_HPP_

#include "../UserEvent.hpp"
#include <iostream>

class MouseEvent : public AUserEvent, public StateEvent {
public:
    enum MouseButtonType {LEFT, RIGHT, WHEEL, XBUTTON1, XBUTTON2};

    MouseEvent(MouseButtonType buttonType, StateEvent::EventState mouseState);
    ~MouseEvent(void) = default;

    MouseButtonType getButtonType(void) const noexcept;

private:
    const MouseButtonType _buttonType;
};

std::ostream &operator<<(std::ostream &os, MouseEvent::MouseButtonType mouseType);

#endif /* MOUSE_EVENT_HPP_ */
