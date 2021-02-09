/*
** EPITECH PROJECT, 2020
** MapCreator
** File description:
** MapCreator.cpp
*/

#include "MapCreator.hpp"

MapCreator::MapCreator(void) :
    _nextLoopInterface(InterfaceManager::Interface::MapCreator),
    _player(std::shared_ptr<Player>(new Player({100, 350 / 3.0}, 1))),
    _parrallaxes({Parrallax(ParrallaxSprite(
        std::shared_ptr<NotAnimatedSprite>(new NotAnimatedSprite(ClientProperties::_directPath + "/rsrc/sprites/Background-start-parrlax.jpg", ClientProperties::_screenSize)),
        std::shared_ptr<NotAnimatedSprite>(new NotAnimatedSprite(ClientProperties::_directPath + "/rsrc/sprites/Background-start-parrlax-flip.jpg", ClientProperties::_screenSize))), false),
        Parrallax(ParrallaxSprite(
        std::shared_ptr<NotAnimatedSprite>(new NotAnimatedSprite(ClientProperties::_directPath + "/rsrc/sprites/Background-planet-parralax.png", ClientProperties::_screenSize)),
        std::shared_ptr<NotAnimatedSprite>(new NotAnimatedSprite(ClientProperties::_directPath + "/rsrc/sprites/transparence.png", ClientProperties::_screenSize))), false)}),
    _direction(0), _playerDirection(true)
{
    _player->setDirection(std::pair<short, short>(0, _playerDirection ? -1 : 1));
    for (auto parrallaxe : _parrallaxes) {
        _activeEntity.push_back(parrallaxe.first.first.get());
        _activeEntity.push_back(parrallaxe.first.second.get());
    }
    _activeEntity.push_back(_player.get());
}

size_t MapCreator::handleUserEvent(const std::vector<std::shared_ptr<IUserEvent> > &userEvents)
{
    _nextLoopInterface = InterfaceManager::Interface::MapCreator;

    *_player += getDeltaTime();
    for (auto userEvent : userEvents)
        handleUserEvent(userEvent);
    _player->setPosition(_player->getPosition() - _player->getDirection() * getDeltaTime() * 50);
    if (_playerDirection) {
        if (_player->getPosition().second * _player->getScale().second > 600) {
            _playerDirection = false;
            _player->setDirection(std::pair<short, short>(0, _playerDirection ? -1 : 1));
        }
    } else {
        if (_player->getPosition().second * _player->getScale().second < 200) {
            _playerDirection = true;
            _player->setDirection(std::pair<short, short>(0, _playerDirection ? -1 : 1));
        }
    }
    Game::handleParrallax(_parrallaxes[0], -300 * _direction, getDeltaTime());
    Game::handleParrallax(_parrallaxes[1], -380 * _direction, getDeltaTime());
    return _nextLoopInterface;
}

void MapCreator::handleUserEvent(const std::shared_ptr<IUserEvent> &userEvent)
{
    switch (userEvent->getEventType()) {
    case IUserEvent::EventType::KEYBOARD_EVENT:
        handleUserEvent(std::dynamic_pointer_cast<KeyboardEvent>(userEvent));
        break;
    default:
        break;
    }
}

void MapCreator::handleUserEvent(const std::shared_ptr<KeyboardEvent> &keyboardEvent)
{
    switch (keyboardEvent->getKey()) {
    case KeyboardInput::LEFT:
        if (keyboardEvent->getEventState() == StateEvent::PRESSED)
            _direction = 1;
        else
            _direction = 0;
        break;
    case KeyboardInput::RIGHT:
        if (keyboardEvent->getEventState() == StateEvent::PRESSED)
            _direction = -1;
        else
            _direction = 0;
        break;
    default:
        break;
    }
}
