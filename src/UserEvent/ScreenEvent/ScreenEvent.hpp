/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** ScreenEvent.hpp
*/

#ifndef SCREENEVENT_HPP_
#define SCREENEVENT_HPP_

#include "../UserEvent.hpp"

class ScreenEvent : public AUserEvent {
public:
    enum ScreenEventType {LOST_FOCUS, GAIN_FOCUS, MOUSE_ENTERED, MOUSE_LEFT};

    ScreenEvent(ScreenEventType screenEvent);
    ~ScreenEvent(void) = default;

    ScreenEventType getScreenEvent(void) const noexcept;

private:
    ScreenEventType _screenEvent;
};

#endif /* SCREENEVENT_HPP_ */
