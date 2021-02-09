/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Game.cpp
*/

#include "Game.hpp"
#include "../../Properties/ClientProperties.hpp"
#include <algorithm>
#include "../InterfaceManager.hpp"
#include "../../Utils/ClientUtils.hpp"
#include "../../Entity/Sprite/Enemy/Default/DefaultEnemy.hpp"

using std::placeholders::_1;

Game::Game(void) :
    _hud({std::shared_ptr<IEntity>(new Text(ClientProperties::_directPath + "/rsrc/font/SEASRN__.ttf", L"BEAM",
                                            {ClientProperties::_screenSize.first * 0.23,
                                             ClientProperties::_screenSize.second *  0.9},
                                            40, {0, 0, 255, 255}))}),
    _beamPower(std::shared_ptr<Square>(new Square({ClientProperties::_screenSize.first * 0.35,
                    ClientProperties::_screenSize.second *  0.92},
                {ClientProperties::_screenSize.first * 0.3,
                 ClientProperties::_screenSize.second * 0.02}, {0, 0, 255, 255}))),
    _beamRate(0), _beam(std::shared_ptr<PlayerFire>(new PlayerFire)),
    _audio(std::shared_ptr<Sound>(new Sound(ClientProperties::_directPath + "/rsrc/audio/Stage1.ogg"))),
    _handleEvent({
            std::bind(&Game::handleLeftMove, this, _1),
            std::bind(&Game::handleRightMove, this, _1),
            std::bind(&Game::handleUpMove, this, _1),
            std::bind(&Game::handleDownMove, this, _1),
            std::bind(&Game::handleFire, this, _1)}),
    _parrallaxes({Parrallax(ParrallaxSprite(
        std::shared_ptr<NotAnimatedSprite>(new NotAnimatedSprite(ClientProperties::_directPath + "/rsrc/sprites/Background-start-parrlax.jpg", ClientProperties::_screenSize)),
        std::shared_ptr<NotAnimatedSprite>(new NotAnimatedSprite(ClientProperties::_directPath + "/rsrc/sprites/Background-start-parrlax-flip.jpg", ClientProperties::_screenSize))), false),
        Parrallax(ParrallaxSprite(
        std::shared_ptr<NotAnimatedSprite>(new NotAnimatedSprite(ClientProperties::_directPath + "/rsrc/sprites/Background-planet-parralax.png", ClientProperties::_screenSize)),
        std::shared_ptr<NotAnimatedSprite>(new NotAnimatedSprite(ClientProperties::_directPath + "/rsrc/sprites/transparence.png", ClientProperties::_screenSize))), false)})
{
    for (auto it : _parrallaxes) {
        _activeEntity.push_back(it.first.first.get());
        _activeEntity.push_back(it.first.second.get());
    }
    for (auto it : _hud)
        _activeEntity.push_back(it.get());
    _activeEntity.push_back(_beamPower.get());
    _activeEntity.push_back(_audio.get());
    for (auto it : _projectiles)
        _activeEntity.push_back(it.get());
}

size_t Game::handleUserEvent(const std::vector<std::shared_ptr<IUserEvent>> &userEvents)
{
    *_players[_playerIndex] += getDeltaTime();
    for (auto userEvent : userEvents) {
        switch (userEvent->getEventType()) {
        case IUserEvent::EventType::KEYBOARD_EVENT:
            handleUserEvent(std::dynamic_pointer_cast<KeyboardEvent>(userEvent));
            break;
        default:
            break;
        }
    }
    handleProjectile();
    handleEnemies();
    handleHud();
    handlePlayers();
    handleParrallax(_parrallaxes[0], 100);
    handleParrallax(_parrallaxes[1], 150);
    return InterfaceManager::Interface::Game;
}

void Game::handleParrallax(Parrallax &parrallax, double speed)
{
    handleParrallax(parrallax, speed, getDeltaTime());
}

void Game::handleParrallax(Parrallax &parrallax, double speed, double deltaTime)
{
    ParrallaxSprite sprites(parrallax.second ? parrallax.first : ParrallaxSprite{parrallax.first.second, parrallax.first.first});
    if (sprites.first->getPosition().first <= -ClientProperties::_screenSize.first)
        parrallax.second ^= 1;
    sprites.first->setPosition(sprites.first->getPosition() + Position(-speed * deltaTime, 0));
    if (sprites.first->getPosition().first < 0)
        sprites.second->setPosition(sprites.first->getPosition() + Position(ClientProperties::_screenSize.first, 0));
    else
        sprites.second->setPosition(sprites.first->getPosition() - Position(ClientProperties::_screenSize.first, 0));
}

void Game::handleProjectile(void)
{
    for (auto proj = _projectiles.begin(); proj != _projectiles.end();) {
        *(*proj) += getDeltaTime();
        (*proj)->setPosition((*proj)->getProjectileSpeed(), (*proj)->getDirection(), getDeltaTime());
        if (ClientUtils::isOutOfScreen((*proj).get())) {
            ClientUtils::removeFromList(_activeEntity, (*proj));
            _projectiles.erase(proj);
        } else
            proj++;
    }
}

void Game::handleHud(void)
{
    _beamPower->setScale(Size(_beamRate, 1));
    if (_beamRate != 0) {
        *_beam += getDeltaTime();
        _beam->setPosition(_players[_playerIndex]->getPosition() + Position(33, -4));
        if (_beamRate < 1) {
            _beamRate += 0.001 * 1000 * getDeltaTime();
            if (_beamRate > 1)
                _beamRate = 1;
        }
    }
}

void Game::handlePlayers(void)
{
    _players[_playerIndex]->setPosition(_players[_playerIndex]->getPosition() + (_players[_playerIndex]->getDirection() * -1) * 100 * getDeltaTime(), ClientProperties::_screenSize);
}

void Game::handleEnemies(void)
{
    for (auto it : _sharedEntity) {
        if (std::dynamic_pointer_cast<AnimatedSprite>(it)) {
            *(std::dynamic_pointer_cast<AnimatedSprite>(it)) += getDeltaTime();
            if (std::dynamic_pointer_cast<AEnemy>(it)) {
                std::shared_ptr<AEnemy> enemy(std::dynamic_pointer_cast<AEnemy>(it));
                enemy->move(getDeltaTime());
            }
        }
    }
}

void Game::handleUpMove(const std::shared_ptr<KeyboardEvent> &keyEvent)
{
    if (keyEvent->getEventState() == StateEvent::EventState::PRESSED)
        _players[_playerIndex]->setDirection(std::pair<short, short>(_players[_playerIndex]->getDirection().first, 1));
    else
        _players[_playerIndex]->setDirection(std::pair<short, short>(_players[_playerIndex]->getDirection().first, 0));
}

void Game::handleDownMove(const std::shared_ptr<KeyboardEvent> &keyEvent)
{
    if (keyEvent->getEventState() == StateEvent::EventState::PRESSED)
        _players[_playerIndex]->setDirection(std::pair<short, short>(_players[_playerIndex]->getDirection().first, -1));
    else
        _players[_playerIndex]->setDirection(std::pair<short, short>(_players[_playerIndex]->getDirection().first, 0));
}

void Game::handleLeftMove(const std::shared_ptr<KeyboardEvent> &keyEvent)
{
    if (keyEvent->getEventState() == StateEvent::EventState::PRESSED)
        _players[_playerIndex]->setDirection(std::pair<short, short>(1, _players[_playerIndex]->getDirection().second));
    else
        _players[_playerIndex]->setDirection(std::pair<short, short>(0, _players[_playerIndex]->getDirection().second));
}

void Game::handleRightMove(const std::shared_ptr<KeyboardEvent> &keyEvent)
{
    if (keyEvent->getEventState() == StateEvent::EventState::PRESSED)
        _players[_playerIndex]->setDirection(std::pair<short, short>(-1, _players[_playerIndex]->getDirection().second));
    else
        _players[_playerIndex]->setDirection(std::pair<short, short>(0, _players[_playerIndex]->getDirection().second));
}

void Game::handleFire(const std::shared_ptr<KeyboardEvent> &keyEvent)
{
    switch (keyEvent->getEventState()) {
    case StateEvent::EventState::PRESSED:
        if (_beamRate == 0) {
            _activeEntity.push_back(_beam.get());
            _beam->setPosition(_players[_playerIndex]->getPosition() + Position(33, -4));
            _beamRate = 0.00001;
        }
        break;
    case StateEvent::EventState::RELEASED:
        ClientUtils::removeFromList(_activeEntity, _beam);
        _projectiles.push_back(std::shared_ptr<PlayerProjectile>(new PlayerProjectile(_players[_playerIndex]->getPosition() + Position(30, 6), _beamRate)));
        _activeEntity.push_back(_projectiles[_projectiles.size() - 1].get());
        _beamRate = 0;
        _beam->setAnimIndex(0);
        break;
    }
}

void Game::handleUserEvent(std::shared_ptr<KeyboardEvent> userEvent)
{
    for (size_t i = 0; i < ClientProperties::_keys.size(); i++) {
        if (userEvent->getKey() == ClientProperties::_keys[i]) {
            _handleEvent[i](userEvent);
        }
    }
}

void Game::updateEntites(const std::vector<AEntity *> &entites)
{
    for (auto newEntity : entites) {
        if (newEntity->isShared()) {
            bool found = false;
            for (auto currentEntity : _sharedEntity) {
                if (newEntity->getId() == currentEntity->getId()) {
                    found = true;
                    currentEntity->setPosition(newEntity->getPosition());
                }
            }
            if (!found) {
                _sharedEntity.push_back(std::shared_ptr<AEntity>(newEntity));
                _activeEntity.push_back(newEntity);
            } else
                delete newEntity;
        } else
            delete newEntity;
    }
}

void Game::setPlayerIndex(size_t index)
{
    _playerIndex = index;
}

void Game::addPlayers(size_t nbPlayers)
{
    for (size_t i = 0; i < nbPlayers; i++) {
        _players.push_back(std::shared_ptr<Player>(new Player({20, 100 + i * 40}, i)));
        _activeEntity.push_back(_players[i].get());
    }
}
