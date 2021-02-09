/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** TextEvent.hpp
*/

#ifndef TEXTEVENT_HPP_
#define TEXTEVENT_HPP_

#include "../UserEvent.hpp"

class TextEvent : public AUserEvent {
public:
    TextEvent(wchar_t code);
    ~TextEvent(void) = default;

    wchar_t getCode(void) const noexcept;

private:
    const wchar_t _code;
};

#endif /* TEXTEVENT_HPP_ */
