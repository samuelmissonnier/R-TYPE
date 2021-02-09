/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** KeyboardEvent.cpp
*/

#include "KeyboardEvent.hpp"
#include <iostream>

KeyboardEvent::KeyboardEvent(StateEvent::EventState keyboardState, KeyboardInput key, Add add) :
    AUserEvent(IUserEvent::EventType::KEYBOARD_EVENT), StateEvent(keyboardState),
    _key(key), _add(add)
{}

KeyboardInput KeyboardEvent::getKey(void) const noexcept
{
    return _key;
}

KeyboardEvent::Add KeyboardEvent::getAddition(void) const noexcept
{
    return _add;
}

std::wstring KeyboardEvent::getKey(KeyboardInput key) noexcept
{
    if (key < _ref.size()) {
        std::wstring str;
        for (auto it : _ref[key])
            str += it;
        return str;
    }
    return L"NONE";
}

const std::vector<std::string> KeyboardEvent::_ref = {
    "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O",
    "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
    "ESC", "LCTRL", "LSHIFT", "LALT", "LSYS", "RCTRL", "RSHIFT", "RALT", "RSYS", "MENU",
    "[", "]", ";", ",", "PERIOD", "\'", "/", "\\", "~", "=", "HYPHEN",
    "SPACE", "ENTER", "BACKSPACE", "TAB", "PAGEUP", "PAGEDOWWN", "END", "HOME",
    "INSERT", "DEL", "+", "-", "*",
    "/", "LEFT", "RIGHT", "UP", "DOWN",
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
    "F0", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "F13", "F14", "F15", "Pause"
};
