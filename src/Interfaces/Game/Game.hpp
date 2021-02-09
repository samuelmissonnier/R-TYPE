/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Game.hpp
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include "../Interface.hpp"
#include <functional>
#include "../../Utils/ClientUtils.hpp"

typedef std::pair<std::shared_ptr<NotAnimatedSprite>, std::shared_ptr<NotAnimatedSprite>> ParrallaxSprite;
typedef std::pair<ParrallaxSprite, bool> Parrallax;

class Game : public AInterface {
public:
    Game(void);
    ~Game(void) = default;

    virtual size_t handleUserEvent(const std::vector<std::shared_ptr<IUserEvent>> &userEvents);

    void updateEntites(const std::vector<AEntity *> &entites);

    static std::shared_ptr<IInterface> getInstance(void)
        {
            return std::shared_ptr<IInterface>(new Game);
        }

    static Game *getInterface(void)
        {
            return ClientUtils::getInterface<Game>(InterfaceManager::Game).get();
        }

    static void handleParrallax(Parrallax &parrallax, double speed, double deltaTime);

    void setPlayerIndex(size_t index);

    void addPlayers(size_t nbPlayers);

private:
    void handleParrallax(Parrallax &parrallax, double speed);

    void handleUserEvent(std::shared_ptr<KeyboardEvent> userEvent);

    void handleProjectile(void);

    void handleEnemies(void);

    void handleHud(void);

    void handlePlayers(void);

    void handleUpMove(const std::shared_ptr<KeyboardEvent> &keyEvent);

    void handleDownMove(const std::shared_ptr<KeyboardEvent> &keyEvent);

    void handleLeftMove(const std::shared_ptr<KeyboardEvent> &keyEvent);

    void handleRightMove(const std::shared_ptr<KeyboardEvent> &keyEvent);

    void handleFire(const std::shared_ptr<KeyboardEvent> &keyEvent);


private:
    std::vector<std::shared_ptr<Player>> _players;
    std::vector<std::shared_ptr<IEntity>> _hud;
    std::shared_ptr<Square> _beamPower;
    double _beamRate;
    std::shared_ptr<PlayerFire> _beam;
    std::shared_ptr<Sound> _audio;
    std::vector<std::shared_ptr<Projectile>> _projectiles;
    std::vector<std::function<void(const std::shared_ptr<KeyboardEvent> &)>> _handleEvent;
    std::vector<Parrallax> _parrallaxes;
    std::vector<std::shared_ptr<AEntity>> _sharedEntity;
    size_t _playerIndex;
};

#endif /* GAME_HPP_ */
