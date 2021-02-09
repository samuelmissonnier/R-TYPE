/*
** EPITECH PROJECT, 2020
** UserEvent
** File description:
** UserEvent.cpp
*/

#include "UserEvent.hpp"

AUserEvent::AUserEvent(const IUserEvent::EventType &inputType) :
    _type(inputType)
{}

IUserEvent::EventType AUserEvent::getEventType(void) const noexcept
{
    return _type;
}

StateEvent::StateEvent(EventState state) :
    _state(state)
{}

StateEvent::EventState StateEvent::getEventState(void) const noexcept
{
    return _state;
}

/*
const int &UserEvent::getTextEntered(void) const noexcept
{
    return _unicode;
}
*/
