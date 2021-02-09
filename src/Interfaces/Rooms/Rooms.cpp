/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Rooms.cpp
*/

#include "Rooms.hpp"
#include "../../Properties/ClientProperties.hpp"
#include "../../Utils/ClientUtils.hpp"
#include "../InterfaceManager.hpp"
#include "../ServerConnection/ServerConnection.hpp"

Rooms::Rooms(void) :
    _background({
        std::shared_ptr<IEntity>(new NotAnimatedSprite(ClientProperties::_directPath + "/rsrc/sprites/Background2.jpg", ClientProperties::_screenSize, {1, 1})),
        std::shared_ptr<Square>(new Square({ClientProperties::_screenSize.first / 4, ClientProperties::_screenSize.second / 4}, {ClientProperties::_screenSize.first / 2, 550}, {0, 243, 255, 140}))}),
    _sprite({
        std::shared_ptr<IEntity>(new NotAnimatedSprite(ClientProperties::_directPath + "/rsrc/sprites/Back_Arrow.svg.png", {1024, 1024}, {8200, 4500}, {0.05, 0.05}))}),
    _squares({
            std::shared_ptr<Square>(new Square({535, 400}, {(ClientProperties::_screenSize.first / 3), 240}, {0, 243, 255, 140}))}),
    _defaultButtonColor({RGBAColor(0, 230, 255, 255), RGBAColor(0, 195, 255, 255), RGBAColor(0, 153, 255, 255)}),
    _buttons({
        std::shared_ptr<Button>(new Button({410, 225}, {51, 51}, {0, 0, 0, 0})),
        std::shared_ptr<Button>(new Button({535, 670}, {200, 50}, _defaultButtonColor)),
        std::shared_ptr<Button>(new Button({875, 670}, {200, 50}, _defaultButtonColor))}),
    _fontFilepath(ClientProperties::_directPath + "/rsrc/font/SEASRN__.ttf"),
    _roomsText({
        std::shared_ptr<Text>(new Text(_fontFilepath, L"", {535, 405}, 25, {13, 95, 151, 200})),
        std::shared_ptr<Text>(new Text(_fontFilepath, L"", {535, 445}, 25, {13, 95, 151, 200})),
        std::shared_ptr<Text>(new Text(_fontFilepath, L"", {535, 485}, 25, {13, 95, 151, 200})),
        std::shared_ptr<Text>(new Text(_fontFilepath, L"", {535, 525}, 25, {13, 95, 151, 200})),
        std::shared_ptr<Text>(new Text(_fontFilepath, L"", {535, 565}, 25, {13, 95, 151, 200})),
        std::shared_ptr<Text>(new Text(_fontFilepath, L"", {535, 605}, 25, {13, 95, 151, 200}))}),
    _roomsButton({
        std::shared_ptr<Button>(new Button({535, 400}, {ClientProperties::_screenSize.first/3, 40}, _defaultButtonColor)),
        std::shared_ptr<Button>(new Button({535, 440}, {ClientProperties::_screenSize.first/3, 40}, _defaultButtonColor)),
        std::shared_ptr<Button>(new Button({535, 480}, {ClientProperties::_screenSize.first/3, 40}, _defaultButtonColor)),
        std::shared_ptr<Button>(new Button({535, 520}, {ClientProperties::_screenSize.first/3, 40}, _defaultButtonColor)),
        std::shared_ptr<Button>(new Button({535, 560}, {ClientProperties::_screenSize.first/3, 40}, _defaultButtonColor)),
        std::shared_ptr<Button>(new Button({535, 600}, {ClientProperties::_screenSize.first/3, 40}, _defaultButtonColor))}),
    _texts({
        std::shared_ptr<Text>(new Text(_fontFilepath, L"R-TYPE", {530, 30}, 150, {13, 95, 151, 200})),
        std::shared_ptr<Text>(new Text(_fontFilepath, L"R-TYPE", {525, 25}, 150, {0, 243, 255, 255})),
        std::shared_ptr<Text>(new Text(_fontFilepath, L"Rooms", {700, 250}, 50, {13, 95, 151, 200})),
        std::shared_ptr<Text>(new Text(_fontFilepath, L"Server :", {535, 350}, 40, {13, 95, 151, 200})),
        std::shared_ptr<Text>(new Text(_fontFilepath, L"Join", {600, 682}, 25, {13, 95, 151, 200})),
        std::shared_ptr<Text>(new Text(_fontFilepath, L"Create", {925, 682}, 25, {13, 95, 151, 200}))}),
    _roomsOffset(0)
{
    for (auto background : _background)
        _activeEntity.push_back(background.get());
    for (auto sprite : _sprite)
        _activeEntity.push_back(sprite.get());
    for (auto square : _squares)
        _activeEntity.push_back(square.get());
    for (auto button : _buttons)
        _activeEntity.push_back(button.get());
    for (auto text : _texts)
        _activeEntity.push_back(text.get());
    for (auto text : _roomsButton)
        _activeEntity.push_back(text.get());
    for (auto text : _roomsText)
        _activeEntity.push_back(text.get());
    _activeEntity.push_back(_errorText.get());
    reloadRooms({});
}

size_t Rooms::handleUserEvent(const std::vector<std::shared_ptr<IUserEvent>> &userEvents)
{
    _nextLoopInterface = InterfaceManager::Interface::Rooms;
    if (getConnectionState() == ConnectionState::Connected) {
        setConnectionState(ConnectionState::Disconnected);
        return InterfaceManager::Interface::GameLobby;
    }
    _errorText->setPosition({690, 770});
    _errorText->setSize(25);
    for (size_t i = 1; i < _buttons.size(); i++) {
        if (ClientUtils::isPosInRect(_buttons[i].get(), getMousePos())) {
            if (_buttons[i]->isIdle())
                _buttons[i]->on();
        } else
            _buttons[i]->idle();
    }
    for (auto roomButton : _roomsButton) {
        if (roomButton->getColor() != RGBAColor(0, 0, 0, 0)) {
            if (!roomButton->isSelected()) {
                if (ClientUtils::isPosInRect(roomButton.get(), getMousePos())) {
                    if (roomButton->isIdle())
                        roomButton->on();
                } else
                    roomButton->idle();
            }
        }
    }
    for (auto userEvent : userEvents) {
        switch (userEvent->getEventType()) {
        case IUserEvent::EventType::MOUSE_EVENT:
            handleUserEvent(std::dynamic_pointer_cast<MouseEvent>(userEvent));
            break;
        case IUserEvent::EventType::KEYBOARD_EVENT:
            handleUserEvent(std::dynamic_pointer_cast<KeyboardEvent>(userEvent));
            break;
        default:
            break;
        }
    }
    return _nextLoopInterface;
}

void Rooms::setConnectionState(ConnectionState state) noexcept
{
    NetworkInterface::setConnectionState(state);
    // switch (state) {
    // case ConnectionState::Connected:
    //     break;
    // case ConnectionState::Connecting:
    //     break;
    // case ConnectionState::Disconnected:
    //     break;
    // }
}

void Rooms::handleUserEvent(std::shared_ptr<MouseEvent> mouseEvent)
{
    if (mouseEvent->getButtonType() == MouseEvent::MouseButtonType::LEFT) {
        if (mouseEvent->getEventState() == StateEvent::EventState::PRESSED) {
            for (size_t i = 1; i < _buttons.size(); i++) {
                if (ClientUtils::isPosInRect(_buttons[i].get(), getMousePos()))
                    _buttons[i]->selected();
                else
                    _buttons[i]->idle();
            }
            for (auto room : _roomsButton) {
                if (room->getColor() != RGBAColor(0, 0, 0, 0) && ClientUtils::isPosInRect(room.get(), getMousePos())) {
                    for (auto roomButton : _roomsButton) {
                        if (roomButton->getColor() != RGBAColor(0, 0, 0, 0))
                            roomButton->idle();
                    }
                    room->selected();
                    break;
                }
            }
        } else {
            if (ClientUtils::isPosInRect(_buttons[0].get(), getMousePos()))
                _nextLoopInterface = InterfaceManager::Interface::ServerConnection;
            if (ClientUtils::isPosInRect(_buttons[1].get(), getMousePos())) {
                int selectedRoom = getSelectedRoomIndex();
                if (selectedRoom != -1) {
                    ClientProperties::_client->sendRequest("140{\"" +_roomsNames[_roomsOffset + selectedRoom] + "\";}");
                    setConnectionState(ConnectionState::Connecting);
                    // _nextLoopInterface = InterfaceManager::Interface::GameLobby;
                }
            }
            if (ClientUtils::isPosInRect(_buttons[2].get(), getMousePos()))
                _nextLoopInterface = InterfaceManager::Interface::CreateRoom;
        }
    }
}

void Rooms::handleUserEvent(std::shared_ptr<KeyboardEvent> keyboardEvent)
{
    if (keyboardEvent->getEventState() == KeyboardEvent::EventState::RELEASED) {
        switch (keyboardEvent->getKey()) {
        case KeyboardInput::UP:
            if (_roomsOffset > 0) {
                _roomsOffset--;
                updateDisplay();
            }
            break;
        case KeyboardInput::DOWN:
            if (_roomsOffset + 6 < _roomsNames.size()) {
                _roomsOffset++;
                updateDisplay();
            }
            break;
        default:
            break;
        }
    }
}

void Rooms::reloadRooms(const std::vector<std::string> &vector)
{
    _roomsNames.clear();
    _roomsNames = vector;
    if (_roomsOffset + 6 > _roomsNames.size()) {
        if (_roomsNames.size() > 6)
            _roomsOffset = _roomsNames.size() - 6;
        else
            _roomsOffset = 0;
    }
    updateDisplay();
}

void Rooms::updateDisplay(void)
{
    for (auto room : _roomsText)
        room->setText(L"");
    for (size_t i = _roomsOffset; i - _roomsOffset < 6; i++) {
        if (i < _roomsNames.size()) {
            std::wstring str;
            for (auto it : _roomsNames[i])
                str += it;
            _roomsText[i - _roomsOffset]->setText(str);
            if (_roomsButton[i - _roomsOffset]->getColor() == RGBAColor(0, 0, 0, 0))
                _roomsButton[i - _roomsOffset]->idle();
        } else {
            _roomsButton[i - _roomsOffset]->setColor({0, 0, 0, 0});
        }
    }
}

int Rooms::getSelectedRoomIndex(void) const noexcept
{
    for (size_t i = 0; i < _roomsButton.size(); i++)
        if (_roomsButton[i]->isSelected())
            return i;
    return -1;
}
