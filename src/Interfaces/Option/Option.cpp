/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Option.cpp
*/

#include "Option.hpp"
#include "../../Properties/ClientProperties.hpp"
#include "../../Utils/ClientUtils.hpp"
#include "../InterfaceManager.hpp"

Option::Option(void) :
    _background({
        std::shared_ptr<IEntity>(new NotAnimatedSprite(ClientProperties::_directPath + "/rsrc/sprites/Background2.jpg", ClientProperties::_screenSize, {1, 1})),
        std::shared_ptr<Square>(new Square({(ClientProperties::_screenSize.first / 4), (ClientProperties::_screenSize.second / 4)}, {(ClientProperties::_screenSize.first / 2), 550}, {0, 243, 255, 140}))}),
    _sprite({
            std::shared_ptr<IEntity>(new NotAnimatedSprite(ClientProperties::_directPath + "/rsrc/sprites/Back_Arrow.svg.png", {1024, 1024}, {8200, 4500}, {0.05, 0.05}))}),
    _squares({
        std::shared_ptr<Square>(new Square({750, 360}, {200, 30}, {0, 200, 255, 255})),
        std::shared_ptr<Square>(new Square({535, 400}, {(ClientProperties::_screenSize.first / 3), 225}, {0, 243, 255, 140}))}),
    _defaultButtonColor({RGBAColor(0, 230, 255, 255), RGBAColor(0, 195, 255, 255), RGBAColor(0, 153, 255, 255)}),
    _buttons({
        std::shared_ptr<Button>(new Button({410, 225}, {51, 51}, {0, 0, 0, 0})),
        std::shared_ptr<Button>(new Button({750, 360}, {325, 30}, {0, 220, 255, 255})),
        std::shared_ptr<Button>(new Button({630, 475}, {50, 50}, _defaultButtonColor)),
        std::shared_ptr<Button>(new Button({655, 540}, {50, 50}, _defaultButtonColor)),
        std::shared_ptr<Button>(new Button({785, 475}, {50, 50}, _defaultButtonColor)),
        std::shared_ptr<Button>(new Button({840, 540}, {50, 50}, _defaultButtonColor)),
        std::shared_ptr<Button>(new Button({1010, 475}, {50, 50}, _defaultButtonColor)),
        std::shared_ptr<Button>(new Button({730, 650}, {150, 50}, _defaultButtonColor))}),
    _fontPath(ClientProperties::_directPath + "/rsrc/font/SEASRN__.ttf"),
    _texts({
        std::shared_ptr<Text>(new Text(_fontPath, L"R-TYPE", {530, 30}, 150, {13, 95, 151, 200})),
        std::shared_ptr<Text>(new Text(_fontPath, L"R-TYPE", {525, 25}, 150, {0, 243, 255, 255})),
        std::shared_ptr<Text>(new Text(_fontPath, L"Options", {680, 250}, 50, {13, 95, 151, 200})),
        std::shared_ptr<Text>(new Text(_fontPath, L"Volume :", {535, 350}, 40, {13, 95, 151, 200})),
        std::shared_ptr<Text>(new Text(_fontPath, L"Save", {775, 662}, 25, {13, 95, 151, 200})),
        std::shared_ptr<Text>(new Text(_fontPath, L"Input :", {760, 425}, 25, {13, 95, 151, 200})),
        std::shared_ptr<Text>(new Text(_fontPath, L"Left :", {545, 485}, 25, {13, 95, 151, 200})),
        std::shared_ptr<Text>(new Text(_fontPath, L"Right :", {545, 550}, 25, {13, 95, 151, 200})),
        std::shared_ptr<Text>(new Text(_fontPath, L"Up :", {720, 485}, 25, {13, 95, 151, 200})),
        std::shared_ptr<Text>(new Text(_fontPath, L"Down :", {720, 550}, 25, {13, 95, 151, 200})),
        std::shared_ptr<Text>(new Text(_fontPath, L"Fire :", {875, 485}, 25, {13, 95, 151, 200}))}),
    _textsInput({
        std::shared_ptr<Text>(new Text(_fontPath, L"", {640, 485}, 25, {13, 95, 151, 200})),
        std::shared_ptr<Text>(new Text(_fontPath, L"", {675, 550}, 25, {13, 95, 151, 200})),
        std::shared_ptr<Text>(new Text(_fontPath, L"", {800, 485}, 25, {13, 95, 151, 200})),
        std::shared_ptr<Text>(new Text(_fontPath, L"", {858, 550}, 25, {13, 95, 151, 200})),
        std::shared_ptr<Text>(new Text(_fontPath, L"", {1025, 485}, 25, {13, 95, 151, 200}))}),
    _keys(ClientProperties::_keys)
{
    for (auto background : _background)
        _activeEntity.push_back(background.get());
    for (auto sprite : _sprite)
        _activeEntity.push_back(sprite.get());
    _activeEntity.push_back(_squares[1].get());
    for (auto button : _buttons)
        _activeEntity.push_back(button.get());
    _activeEntity.push_back(_squares[0].get());
    for (auto text : _texts)
        _activeEntity.push_back(text.get());
    for (size_t i = 0; i < _textsInput.size(); i++) {
        _textsInput[i]->setText(KeyboardEvent::getKey(_keys[i]));
        _activeEntity.push_back(_textsInput[i].get());
    }
    _activeEntity.push_back(_errorText.get());
}

size_t Option::handleUserEvent(const std::vector<std::shared_ptr<IUserEvent>> &userEvents)
{
    _nextLoopInterface = InterfaceManager::Interface::Option;
    _errorText->setPosition({620, 725});
    _errorText->setSize(25);
    *_errorText.get() += getDeltaTime();
    for (size_t i = 1; i < _buttons.size() - 1; i++) {
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
        case IUserEvent::EventType::KEYBOARD_EVENT:
            handleUserEvent(std::dynamic_pointer_cast<KeyboardEvent>(userEvent));
            break;
        default:
            break;
        }
    }
    return _nextLoopInterface;
}

void Option::handleUserEvent(std::shared_ptr<MouseEvent> mouseEvent)
{
    if (mouseEvent->getButtonType() == MouseEvent::MouseButtonType::LEFT) {
        if (mouseEvent->getEventState() == StateEvent::EventState::PRESSED) {
            for (size_t i = 1; i < _buttons.size() - 1; i++) {
                if (ClientUtils::isPosInRect(_buttons[i].get(), getMousePos()))
                    _buttons[i]->selected();
                else
                    _buttons[i]->idle();
            }
        } else {
            if (ClientUtils::isPosInRect(_buttons[0].get(), getMousePos())) {
                _nextLoopInterface = InterfaceManager::Interface::Menu;
            }
            if (ClientUtils::isPosInRect(_buttons[_buttons.size() - 1].get(), getMousePos())) {
                if (!ClientUtils::isDuplicateKey(_keys)) {
                    ClientProperties::_keys = _keys;
                    _nextLoopInterface = InterfaceManager::Interface::Menu;
                } else
                    _errorText->display(L"Duplicated key");
            }
            if (ClientUtils::isPosInRect(_buttons[1].get(), getMousePos())) {
                std::pair<const double, const double> size = {getMousePos().first - 750, 30.0};
                ClientProperties::_volume = (size.first / 325);
                _squares[0]->setSize(size);
            }
        }
    }
}

void Option::handleUserEvent(std::shared_ptr<KeyboardEvent> textEvent)
{
    for (size_t i = 2; i < _buttons.size() - 1; i++) {
        if (_buttons[i]->isSelected()) {
            _textsInput[i - 2]->setText(KeyboardEvent::getKey(textEvent->getKey()));
            _keys[i - 2] = textEvent->getKey();
            break;
        }
    }
}
