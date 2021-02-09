/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** ServerConnection.cpp
*/

#include "ServerConnection.hpp"
#include "../../Properties/ClientProperties.hpp"
#include "../../Utils/ClientUtils.hpp"
#include "../InterfaceManager.hpp"
#include "../../RTypeClient/RTypeClient.hpp"

ServerConnection::ServerConnection(void) :
    _background({
        std::shared_ptr<IEntity>(new NotAnimatedSprite(ClientProperties::_directPath + "/rsrc/sprites/Background2.jpg", ClientProperties::_screenSize, {1, 1})),
        std::shared_ptr<Square>(new Square({(ClientProperties::_screenSize.first / 4), (ClientProperties::_screenSize.second / 4)}, {(ClientProperties::_screenSize.first / 2), 550}, {0, 243, 255, 140}))}),
    _sprite({
        std::shared_ptr<IEntity>(new NotAnimatedSprite(ClientProperties::_directPath + "/rsrc/sprites/Back_Arrow.svg.png", {1024, 1024}, {8200, 4500}, {0.05, 0.05}))}),
    _defaultButtonColor({RGBAColor(0, 230, 255, 255), RGBAColor(0, 195, 255, 255), RGBAColor(0, 153, 255, 255)}),
    _buttons({
        std::shared_ptr<Button>(new Button({410, 225}, {51, 51}, {0, 0, 0, 0})),
        std::shared_ptr<Button>(new Button({430, 400}, {760, 40}, _defaultButtonColor)),
        std::shared_ptr<Button>(new Button({430, 510}, {760, 40}, _defaultButtonColor)),
        std::shared_ptr<Button>(new Button({430, 620}, {760, 40}, _defaultButtonColor)),
        std::shared_ptr<Button>(new Button({710, 690}, {200, 50}, RGBAColor(0, 0, 0, 0), RGBAColor(0, 195, 255, 255), RGBAColor(0, 153, 255, 255)))}),
    _defaultTextColor({13, 95, 151, 200}),
    _textFont(ClientProperties::_directPath + "/rsrc/font/SEASRN__.ttf"),
    _texts({
        std::shared_ptr<Text>(new Text(_textFont, L"Server Ip :", {430, 460}, 30, _defaultTextColor)),
        std::shared_ptr<Text>(new Text(_textFont, L"R-TYPE", {530, 30}, 150, _defaultTextColor)),
        std::shared_ptr<Text>(new Text(_textFont, L"R-TYPE", {525, 25}, 150, {0, 243, 255, 255})),
        std::shared_ptr<Text>(new Text(_textFont, L"Server Connection", {530, 250}, 50, _defaultTextColor)),
        std::shared_ptr<Text>(new Text(_textFont, L"Connected As :", {430, 350}, 30, _defaultTextColor)),
        std::shared_ptr<Text>(new Text(_textFont, L"Port Connection :", {430, 570}, 30, _defaultTextColor))}),
    _textsInput({
        std::shared_ptr<Text>(new Text(_textFont, L"Your Name", {430, 405}, 25, _defaultTextColor)),
        std::shared_ptr<Text>(new Text(_textFont, L"127.0.0.1", {430, 515}, 25, _defaultTextColor)),
        std::shared_ptr<Text>(new Text(_textFont, L"7171", {430, 625}, 25, _defaultTextColor))}),
    _animatedText(new AnimatedText(_textFont, {713, 700}, 25, _defaultTextColor, 0.2, {L"Connect"})),
    _animatedTextTexts({L"Connecting", L"Connecting .", L"Connecting ..", L"Connecting ...", L"Connecting ..", L"Connecting ."})
{
    for (auto background : _background)
        _activeEntity.push_back(background.get());
    for (auto sprite : _sprite)
        _activeEntity.push_back(sprite.get());
    for (auto button : _buttons)
        _activeEntity.push_back(button.get());
    for (auto text : _texts)
        _activeEntity.push_back(text.get());
    for (auto text : _textsInput)
        _activeEntity.push_back(text.get());
    _activeEntity.push_back(_animatedText.get());
    _activeEntity.push_back(_errorText.get());
}

size_t ServerConnection::handleUserEvent(const std::vector<std::shared_ptr<IUserEvent>> &userEvents)
{
    _nextLoopInterface = InterfaceManager::Interface::ServerConnection;
    _errorText->setPosition({690, 770});
    _errorText->setSize(25);
    *_errorText.get() += getDeltaTime();
    if (getConnectionState() == ConnectionState::Connected) {
        setConnectionState(ConnectionState::Disconnected);
        return _nextLoopInterface = InterfaceManager::Interface::Rooms;
    } else if (getConnectionState() == ConnectionState::Disconnected && ClientProperties::_client)
        ClientProperties::_client.reset();
    *_animatedText.get() += getDeltaTime();
    *_errorText.get() += getDeltaTime();
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

void ServerConnection::setConnectionState(ConnectionState state) noexcept
{
    NetworkInterface::setConnectionState(state);
    switch (state) {
    case ConnectionState::Disconnected:
        _animatedText->setTexts({L"Connect"});
        break;
    case ConnectionState::Connecting:
        _animatedText->setTexts(_animatedTextTexts);
        break;
    case ConnectionState::Connected:
        _animatedText->setTexts({L"Connected"});
        break;
    }
}

void ServerConnection::handleUserEvent(std::shared_ptr<MouseEvent> mouseEvent)
{
    if (mouseEvent->getButtonType() == MouseEvent::MouseButtonType::LEFT) {
        if (mouseEvent->getEventState() == StateEvent::EventState::PRESSED) {
            for (size_t i = 1; i < _buttons.size(); i++) {
                if ((i == 4 && getConnectionState() != ConnectionState::Connecting) || i != 4) {
                    if (ClientUtils::isPosInRect(_buttons[i].get(), getMousePos()))
                        _buttons[i]->selected();
                    else
                        _buttons[i]->idle();
                }
            }
        } else {
            if (ClientUtils::isPosInRect(_buttons[0].get(), getMousePos()))
                _nextLoopInterface = InterfaceManager::Interface::Menu;
            if (ClientUtils::isPosInRect(_buttons[4].get(), getMousePos()) &&
                getConnectionState() != ConnectionState::Connecting) {
                _buttons[4]->on();
                std::string name = ClientUtils::convertWstringInToString(_textsInput[0]->getText());
                std::string ip = ClientUtils::convertWstringInToString(_textsInput[1]->getText());
                int port = std::atoi(ClientUtils::convertWstringInToString(_textsInput[2]->getText()).c_str());
                ClientProperties::_client = std::unique_ptr<RTypeClient>(new RTypeClient(ip, port, name));
                setConnectionState(ConnectionState::Connecting);
                _animatedText->setTexts(_animatedTextTexts);
            }
        }
    }
}

void ServerConnection::handleUserEvent(std::shared_ptr<TextEvent> textEvent)
{
    for (size_t i = 1; i < _buttons.size() - 1; i++) {
        if (_buttons[i]->isSelected()) {
            if (textEvent->getCode() == 8)
                _textsInput[i - 1]->operator--();
            else if (_textsInput[i - 1]->getText().size() < 32) {
                if (i == 2 && (std::isdigit(textEvent->getCode()) || textEvent->getCode() == '.'))
                    *_textsInput[i - 1].get() += textEvent->getCode();
                else if (i == 3 && std::isdigit(textEvent->getCode()))
                    *_textsInput[i - 1].get() += textEvent->getCode();
                else if (i == 1 && (std::isalnum(textEvent->getCode()) != 0 || textEvent->getCode() == ' '))
                    *_textsInput[i - 1].get() += textEvent->getCode();
            }
        }
    }
}

void ServerConnection::setErrorText(const std::wstring &error) const noexcept
{
    _errorText->display(error);
}
