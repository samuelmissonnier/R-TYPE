/*
** EPITECH PROJECT, 2020
** MapCreator
** File description:
** MapCreator.hpp
*/

#ifndef MAPCREATOR_HPP_
#define MAPCREATOR_HPP_

#include "../Interface.hpp"
#include "../../Utils/ClientUtils.hpp"
#include "../Game/Game.hpp"
#include "../../Entity/Sprite/Player/Player.hpp"

class MapCreator : public AInterface {
public:
    MapCreator(void);
    ~MapCreator(void) = default;

    virtual size_t handleUserEvent(const std::vector<std::shared_ptr<IUserEvent>> &userEvents);

    static std::shared_ptr<IInterface> getInstance(void)
        {
            return std::shared_ptr<IInterface>(new MapCreator);
        }

    static MapCreator *getInterface(void)
        {
            return ClientUtils::getInterface<MapCreator>(InterfaceManager::MapCreator).get();
        }

private:
    void handleUserEvent(const std::shared_ptr<IUserEvent> &userEvent);

    void handleUserEvent(const std::shared_ptr<KeyboardEvent> &keyboardEvent);

private:
    size_t _nextLoopInterface;
    std::shared_ptr<Player> _player;
    std::vector<Parrallax> _parrallaxes;
    short _direction;
    bool _playerDirection;
};

#endif /* MAPCREATOR_HPP_ */
