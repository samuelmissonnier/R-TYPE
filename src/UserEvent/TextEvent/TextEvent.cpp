/*
** EPITECH PROJECT, 2020
** TextEvent
** File description:
** TextEvent.cpp
*/

#include "TextEvent.hpp"

TextEvent::TextEvent(wchar_t code) :
    AUserEvent(IUserEvent::EventType::TEXT_EVENT), _code(code)
{}

wchar_t TextEvent::getCode(void) const noexcept
{
    return _code;
}
