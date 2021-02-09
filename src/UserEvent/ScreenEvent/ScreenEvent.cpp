/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** ScreenEvent.cpp
*/

#include "ScreenEvent.hpp"

ScreenEvent::ScreenEvent(ScreenEventType screenEvent) :
    AUserEvent(IUserEvent::EventType::SCREEN_EVENT), _screenEvent(screenEvent)
{}

ScreenEvent::ScreenEventType ScreenEvent::getScreenEvent(void) const noexcept
{
    return _screenEvent;
}
