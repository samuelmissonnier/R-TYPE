/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** UserEvent.hpp
*/

#ifndef USER_EVENT_HPP_
#define USER_EVENT_HPP_

#include <string>

class IUserEvent {
public:
    enum EventType {SCREEN_EVENT, TEXT_EVENT, KEYBOARD_EVENT, MOUSE_EVENT, MouseWheel, MouseMove};

    virtual ~IUserEvent(void) = default;

    virtual IUserEvent::EventType getEventType(void) const noexcept = 0;
};

class AUserEvent : public IUserEvent {
public:
    AUserEvent(const IUserEvent::EventType &inputType);
    ~AUserEvent(void) = default;

    virtual IUserEvent::EventType getEventType(void) const noexcept;

private:
    const IUserEvent::EventType _type;
};

class StateEvent {
public:
    enum EventState {PRESSED, RELEASED};

    StateEvent(EventState state);
    ~StateEvent(void) = default;

    EventState getEventState(void) const noexcept;

private:
    const EventState _state;
};

#endif /* USER_EVENT_HPP_ */
