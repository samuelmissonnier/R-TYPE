/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** KeyboardEvent.hpp
*/

#ifndef KEYBOARD_EVENT_HPP_
#define KEYBOARD_EVENT_HPP_

#include "../UserEvent.hpp"
#include <vector>

enum KeyboardInput {
    A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    NUM0, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9,
    ESC, LCONTROL, LSHIFT, LALT, LSYSTEM, RCONTROL, RSHIFT, RALY, RSYSTEM, MENU,
    LBRACKET, RBRACKET, SEMICOLON, COMMA, PERIOD, QUOTE, SLASH, BACKSLASH, TILDE, EQUAL, HYPHEN,
    SPACE, ENTER, BACKSPACE, TAB, PAGEUP, PAGEDOWWN, END, HOME, INSERT, DELETE, ADD, SUBSTRACT, MULTIPLY,
    DIVIDE, LEFT, RIGHT, UP, DOWN,
    NUMPAD0, NUMPAD1, NUMPAD2, NUMPAD3, NUMPAD4, NUMPAD5, NUMPAD6, NUMPAD7, NUMPAD8, NUMPAD9,
    F0, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, Pause};

class KeyboardEvent : public AUserEvent, public StateEvent {
public:
    enum Add{ALT = 0b1, CTRL = 0b01, SHIFT = 0b001, SYS = 0b0001};

    KeyboardEvent(StateEvent::EventState keyboardState, KeyboardInput key, Add add);
    ~KeyboardEvent(void) = default;
    KeyboardInput getKey(void) const noexcept;

    Add getAddition(void) const noexcept;

    static std::wstring getKey(KeyboardInput key) noexcept;

private:
    const KeyboardInput _key;
    const Add _add;
    static const std::vector<std::string> _ref;
};

#endif /* KEYBOARD_EVENT_HPP_ */
