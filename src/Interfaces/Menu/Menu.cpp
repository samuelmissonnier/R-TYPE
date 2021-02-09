/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Menu.cpp
*/

#include "Menu.hpp"
#include "../../Properties/ClientProperties.hpp"
#include "../../Utils/ClientUtils.hpp"
#include "../InterfaceManager.hpp"

Menu::Menu(void) :
    _backgrounds({
        std::shared_ptr<IEntity>(new NotAnimatedSprite(ClientProperties::_directPath + "/rsrc/sprites/Background2.jpg", ClientProperties::_screenSize, {1, 1})),
        std::shared_ptr<IEntity>(new Square({(ClientProperties::_screenSize.first / 3), (ClientProperties::_screenSize.second / 4)}, {(ClientProperties::_screenSize.first / 3), 550}, {0, 243, 255, 170}))
    }),
    _defaultButtonColor({RGBAColor(0, 0, 0, 0), RGBAColor(0, 195, 255, 255), RGBAColor(0, 153, 255, 255)}),
    _buttons({
        std::shared_ptr<Button>(new Button({645, 295}, {210, 85}, _defaultButtonColor)),
        std::shared_ptr<Button>(new Button({645, 395}, {190, 85}, _defaultButtonColor)),
        std::shared_ptr<Button>(new Button({645, 495}, {350, 85}, _defaultButtonColor)),
        std::shared_ptr<Button>(new Button({645, 595}, {185, 85}, _defaultButtonColor))}),
    _defaultTextColor({13, 95, 151, 200}),
    _texts({
        std::shared_ptr<Text>(new Text(ClientProperties::_directPath + "/rsrc/font/SEASRN__.ttf", L"R-TYPE", {530, 30}, 150, _defaultTextColor)),
        std::shared_ptr<Text>(new Text(ClientProperties::_directPath + "/rsrc/font/SEASRN__.ttf", L"R-TYPE", {525, 25}, 150, {0, 243, 255, 255})),
        std::shared_ptr<Text>(new Text(ClientProperties::_directPath + "/rsrc/font/SEASRN__.ttf", L"PLAY", {650, 295}, 75, _defaultTextColor)),
        std::shared_ptr<Text>(new Text(ClientProperties::_directPath + "/rsrc/font/SEASRN__.ttf", L"MAP", {650, 395}, 75, _defaultTextColor)),
        std::shared_ptr<Text>(new Text(ClientProperties::_directPath + "/rsrc/font/SEASRN__.ttf", L"OPTION", {645, 495}, 75, _defaultTextColor)),
        std::shared_ptr<Text>(new Text(ClientProperties::_directPath + "/rsrc/font/SEASRN__.ttf", L"EXIT", {650, 595}, 75, _defaultTextColor))})
{

    for (auto background : _backgrounds)
        _activeEntity.push_back(background.get());
    for (auto button : _buttons)
        _activeEntity.push_back(button.get());
    for (auto text : _texts)
        _activeEntity.push_back(text.get());
}

size_t Menu::handleUserEvent(const std::vector<std::shared_ptr<IUserEvent>> &userEvents)
{
    _nextLoopInterface = InterfaceManager::Interface::Menu;
    for (auto button : _buttons) {
        if (ClientUtils::isPosInRect(button.get(), getMousePos())) {
            if (button->isIdle())
                button->on();
        } else {
            button->idle();
        }
    }
    for (auto userEvent : userEvents) {
        switch (userEvent->getEventType()) {
        case IUserEvent::EventType::MOUSE_EVENT:
            handleUserEvent(std::dynamic_pointer_cast<MouseEvent>(userEvent));
            break;
        default:
            break;
        }
    }
    return _nextLoopInterface;
}

void Menu::handleUserEvent(std::shared_ptr<MouseEvent> mouseEvent)
{
    if (mouseEvent->getButtonType() == MouseEvent::MouseButtonType::LEFT) {
        if (mouseEvent->getEventState() == StateEvent::EventState::PRESSED) {
            for (auto button : _buttons)
                if (ClientUtils::isPosInRect(button.get(), getMousePos()))
                    button->selected();
        }
        if (mouseEvent->getEventState() == StateEvent::EventState::RELEASED) {
            if (ClientUtils::isPosInRect(_buttons[0].get(), getMousePos())) {
                _nextLoopInterface = InterfaceManager::Interface::ServerConnection;
            } else if (ClientUtils::isPosInRect(_buttons[1].get(), getMousePos())) {
                _nextLoopInterface = InterfaceManager::Interface::MapCreator;
            } else if (ClientUtils::isPosInRect(_buttons[2].get(), getMousePos())) {
                _nextLoopInterface = InterfaceManager::Interface::Option;
            } else if (ClientUtils::isPosInRect(_buttons[3].get(), getMousePos()))
                _nextLoopInterface = InterfaceManager::Interface::Closing;
        }
    }
}
