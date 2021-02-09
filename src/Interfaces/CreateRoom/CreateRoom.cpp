/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** CreateRoom.cpp
*/

#include "CreateRoom.hpp"
#include "../../Properties/ClientProperties.hpp"
#include "../../Utils/ClientUtils.hpp"
#include "../InterfaceManager.hpp"

CreateRoom::CreateRoom(void) :
    _background({
        std::shared_ptr<IEntity>(new NotAnimatedSprite(ClientProperties::_directPath + "/rsrc/sprites/Background2.jpg", ClientProperties::_screenSize, {1, 1})),
        std::shared_ptr<Square>(new Square({(ClientProperties::_screenSize.first / 4), (ClientProperties::_screenSize.second / 4)}, {(ClientProperties::_screenSize.first / 2), 550}, {0, 243, 255, 170}))}),
    _sprite({
        std::shared_ptr<IEntity>(new NotAnimatedSprite(ClientProperties::_directPath + "/rsrc/sprites/Back_Arrow.svg.png", {1024, 1024}, {8200, 4500}, {0.05, 0.05}))}),
    _defaultButtonColor({RGBAColor(0, 255, 255, 255), RGBAColor(0, 195, 255, 255), RGBAColor(0, 153, 255, 255)}),
    _buttons({
        std::shared_ptr<Button>(new Button({410, 225}, {51, 51}, {0, 0, 0, 0})),
        std::shared_ptr<Button>(new Button({500, 480}, {615, 50}, RGBAColor(0, 230, 255, 160), RGBAColor(0, 195, 255, 255), RGBAColor(0, 153, 255, 255))),
        std::shared_ptr<Button>(new Button({740, 555}, {125, 50}, RGBAColor(0, 0, 0, 0), RGBAColor(0, 195, 255, 255), RGBAColor(0, 153, 255, 255)))}),
    _defaultTextColor({13, 95, 151, 200}),
    _fontPath(ClientProperties::_directPath + "/rsrc/font/SEASRN__.ttf"),
    _texts({
        std::shared_ptr<Text>(new Text(_fontPath, L"R-TYPE", {530, 30}, 150, _defaultTextColor)),
        std::shared_ptr<Text>(new Text(_fontPath, L"R-TYPE", {525, 25}, 150, {0, 243, 255, 255})),
        std::shared_ptr<Text>(new Text(_fontPath, L"Create Room", {615, 250}, 50, _defaultTextColor)),
        std::shared_ptr<Text>(new Text(_fontPath, L"Name Room :", {665, 405}, 40, _defaultTextColor)),
        std::shared_ptr<Text>(new Text(_fontPath, L"OK", {770, 560}, 35, _defaultTextColor))}),
    _textInput(new Text(_fontPath, L"jfe", {500, 490}, 25, _defaultTextColor))
{
    for (auto background : _background)
        _activeEntity.push_back(background.get());
    for (auto sprite : _sprite)
        _activeEntity.push_back(sprite.get());
    for (auto button : _buttons)
        _activeEntity.push_back(button.get());
    for (auto text : _texts)
        _activeEntity.push_back(text.get());
    _activeEntity.push_back(_textInput.get());
}

size_t CreateRoom::handleUserEvent(const std::vector<std::shared_ptr<IUserEvent>> &userEvents)
{
    _nextLoopInterface = InterfaceManager::Interface::CreateRoom;
    if (getConnectionState() == ConnectionState::Connected) {
        setConnectionState(ConnectionState::Disconnected);
        return _nextLoopInterface = InterfaceManager::Interface::GameLobby;
    }
    for (size_t i = 1; i < _buttons.size(); i++) {
        if (!_buttons[i]->isSelected()) {
            if (ClientUtils::isPosInRect(_buttons[i].get(), getMousePos())) {
                if (_buttons[i]->isIdle())
                    _buttons[i]->on();
            } else
                _buttons[i]->idle();
        }
    }
    for (auto userEvent : userEvents) {
        switch (userEvent->getEventType()) {
        case IUserEvent::EventType::MOUSE_EVENT:
            handleUserEvent(std::dynamic_pointer_cast<MouseEvent>(userEvent));
            break;
        case IUserEvent::EventType::TEXT_EVENT:
            handleUserEvent(std::dynamic_pointer_cast<TextEvent>(userEvent));
            break;
        default:
            break;
        }
    }
    return _nextLoopInterface;
}

void CreateRoom::handleUserEvent(std::shared_ptr<MouseEvent> mouseEvent)
{
    if (mouseEvent->getButtonType() == MouseEvent::MouseButtonType::LEFT) {
        if (mouseEvent->getEventState() == StateEvent::EventState::PRESSED) {
            for (size_t i = 1; i < _buttons.size(); i++) {
            if (ClientUtils::isPosInRect(_buttons[i].get(), getMousePos()))
                _buttons[i]->selected();
            else
                _buttons[i]->idle();
            }
        }
        if (mouseEvent->getEventState() == StateEvent::EventState::RELEASED) {
            if (ClientUtils::isPosInRect(_buttons[0].get(), getMousePos()))
                _nextLoopInterface = InterfaceManager::Interface::Rooms;
            if (ClientUtils::isPosInRect(_buttons[2].get(), getMousePos())
                && _textInput->getText().size()) {
                ClientProperties::_client->sendRequest("120{\"" + ClientUtils::convertWstringInToString(_textInput->getText()) + "\";\"" + ClientProperties::_client->getUserName() + "\";}");
            }
        }
    }
}

void CreateRoom::handleUserEvent(std::shared_ptr<TextEvent> textEvent)
{
    if (_buttons[1]->isSelected()) {
        if (_textInput->getText().size() < 16
            && (textEvent->getCode() == ' ' ||
                std::isalnum(textEvent->getCode())))
            *_textInput.get() += textEvent->getCode();
        if (textEvent->getCode() == 8)
            _textInput->operator--();
    }
}
