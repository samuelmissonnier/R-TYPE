/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** GameLobby.cpp
*/

#include "GameLobby.hpp"
#include "../../Properties/ClientProperties.hpp"
#include "../../Utils/ClientUtils.hpp"
#include "../InterfaceManager.hpp"

GameLobby::GameLobby(void) :
    _background({
        std::shared_ptr<IEntity>(new NotAnimatedSprite(ClientProperties::_directPath + "/rsrc/sprites/Background2.jpg", ClientProperties::_screenSize, {1, 1})),
        std::shared_ptr<Square>(new Square({(ClientProperties::_screenSize.first / 4), (ClientProperties::_screenSize.second / 4)}, {(ClientProperties::_screenSize.first / 2), 550}, {0, 243, 255, 140}))}),
    _sprite({
        std::shared_ptr<IEntity>(new NotAnimatedSprite(ClientProperties::_directPath + "/rsrc/sprites/Back_Arrow.svg.png", {1024, 1024}, {8200, 4500}, {0.05, 0.05}))}),
    _squares({
        std::shared_ptr<Square>(new Square({535, 400}, {(ClientProperties::_screenSize.first / 3), 225}, {0, 243, 255, 140}))}),
    _defaultButtonColor({RGBAColor(0, 0, 0, 0), RGBAColor(0, 195, 255, 255), RGBAColor(0, 153, 255, 255)}),
    _buttons({
        std::shared_ptr<Button>(new Button({410, 225}, {51, 51}, {0, 0, 0, 0})),
        std::shared_ptr<Button>(new Button({730, 650}, {150, 50}, {0, 243, 255, 140}))}),
    _textFont(ClientProperties::_directPath + "/rsrc/font/SEASRN__.ttf"),
    _defaultTextColor(13, 95, 151, 200),
    _texts({
        std::shared_ptr<Text>(new Text(_textFont, L"R-TYPE", {530, 30}, 150, _defaultTextColor)),
        std::shared_ptr<Text>(new Text(_textFont, L"R-TYPE", {525, 25}, 150, {0, 243, 255, 255})),
        std::shared_ptr<Text>(new Text(_textFont, L"Game Lobby", {630, 250}, 50, _defaultTextColor)),
        std::shared_ptr<Text>(new Text(_textFont, L"Ready", {765, 662}, 25, _defaultTextColor))}),
    _roomName(new Text(_textFont, L"Rooms 42 :", {535, 350}, 40, _defaultTextColor)),
    _isGameLaunched(false), _isReady(false)
{
    for (auto background : _background)
        _activeEntity.push_back(background.get());
    for (auto square : _squares)
        _activeEntity.push_back(square.get());
    for (auto sprite : _sprite)
        _activeEntity.push_back(sprite.get());
    for (auto button : _buttons)
        _activeEntity.push_back(button.get());
    for (auto text : _texts)
        _activeEntity.push_back(text.get());
    _activeEntity.push_back(_errorText.get());
}

size_t GameLobby::handleUserEvent(const std::vector<std::shared_ptr<IUserEvent>> &userEvents)
{
    _nextLoopInterface = InterfaceManager::Interface::GameLobby;
    _errorText->setPosition({690, 770});
    _errorText->setSize(25);
    *_errorText.get() += getDeltaTime();
    if (_isGameLaunched) {
        _isGameLaunched = false;
        return InterfaceManager::Interface::Game;
    }
    if (getConnectionState() == ConnectionState::Connected) {
        setConnectionState(ConnectionState::Disconnected);
        if (_requestType == RequestType::LEAVE)
            return InterfaceManager::Interface::Rooms;
        else
            _isReady ^= 1;
    }
    if (!_buttons[1]->isSelected()) {
        if (ClientUtils::isPosInRect(_buttons[1].get(), getMousePos())) {
            if (_buttons[1]->isIdle())
                _buttons[1]->on();
        } else
            _buttons[1]->idle();
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

void GameLobby::handleUserEvent(std::shared_ptr<MouseEvent> mouseEvent)
{
    if (mouseEvent->getButtonType() == MouseEvent::MouseButtonType::LEFT) {
        if (mouseEvent->getEventState() == StateEvent::EventState::PRESSED) {
            if (getConnectionState() != ConnectionState::Connecting) {
                if (ClientUtils::isPosInRect(_buttons[1].get(), getMousePos()))
                    _buttons[1]->selected();
                else
                    _buttons[1]->idle();
            }
        } else {
            if (ClientUtils::isPosInRect(_buttons[0].get(), getMousePos())) {
                ClientProperties::_client->sendRequest("150{}");
                setConnectionState(ConnectionState::Connecting);
                _requestType = RequestType::LEAVE;
            }
            if (ClientUtils::isPosInRect(_buttons[1].get(), getMousePos())) {
                if (!_isReady)
                    ClientProperties::_client->sendRequest("170{}");
                else
                    ClientProperties::_client->sendRequest("180{}");
                setConnectionState(ConnectionState::Connecting);
                _requestType = RequestType::READY;
            }
        }
    }
}

void GameLobby::setRoomName(const std::string &str)
{
    _roomName->setText(std::wstring(str.begin(), str.end()));
}

void GameLobby::reloadPlayersName(const std::vector<std::string> &playersName)
{
    size_t i = 0;
    for (; i < playersName.size(); i++) {
        if (i >= _playersText.size()) {
            _playersText.push_back(std::shared_ptr<Text>(new Text(_textFont, L"", {700, 425 + i * 50}, 25, _defaultTextColor)));
            _activeEntity.push_back(_playersText[i].get());
        }
        _playersText[i]->setText(std::wstring(playersName[i].begin(), playersName[i].end()));
    }
    for (; i < _playersText.size(); i++)
        _playersText[i]->setText(L"");
}
