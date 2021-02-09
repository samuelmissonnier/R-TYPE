/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Player.cpp
*/

#include "Player.hpp"
#include "../../../Properties/RTypeProperties.hpp"
#include "../../../Utils/RTypeUtils.hpp"

Player::Player(const Position &pos, const size_t &playerType) :
    AnimatedSprite(RTypeProperties::_directPath + "/rsrc/sprites/r-typesheet42.gif",
                   pos, playerType, _spriteSheet, 0.3, Size(3, 3), 2)
{}

Player::Player(const std::vector<std::string> &data) :
    AnimatedSprite(RTypeProperties::_directPath + "/rsrc/sprites/r-typesheet42.gif",
                   std::stoi(data[0]), RTypeUtils::getPosition(data[1]), std::stoi(data[2]),
                   _spriteSheet, 0.3, Size(3, 3), 2)
{}

std::string Player::toString(void) const noexcept
{
    return "\"" + std::to_string(getId()) + "\" \"" +
        std::to_string(getPosition().first) + ":" + std::to_string(getPosition().second) + "\" \"" +
        std::to_string(getAnimline()) + "\"";
}

void Player::nextAnim(void) noexcept
{
    if (getDirection().second < 0) {
        if (getAnimIndex() > 0)
            setAnimIndex(getAnimIndex() - 1);
    } else if (!getDirection().second) {
        if (getAnimIndex() > 2)
            setAnimIndex(getAnimIndex() - 1);
        else if (getAnimIndex() < 2)
            setAnimIndex(getAnimIndex() + 1);
    } else {
        if (getAnimIndex() < 4)
            setAnimIndex(getAnimIndex() + 1);
    }
}

void Player::setDirection(const Direction &direction) noexcept
{
    Directional::setDirection(direction);
    nextAnim();
}

void Player::setPosition(const Position &pos, const Size &screenSize) noexcept
{
    Position newpos(pos.first, pos.second);
    if (pos.first * getScale().first < 0)
        newpos.first = 0;
    else if (pos.first * getScale().first > screenSize.first - 33 * getScale().first)
        newpos.first = screenSize.first / getScale().first - 33;
    if (pos.second * getScale().second < 0)
        newpos.second = 0;
    else if (pos.second * getScale().second > screenSize.second - 17 * getScale().second)
        newpos.second = screenSize.second / getScale().second - 17;
    setPosition(newpos);
}

void Player::setPosition(const Position &pos) noexcept
{
    Super::setPosition(pos);
}

const SpriteSheetRects Player::_spriteSheet = {
    Rect(Position(0, 0), Size(33, 17)),
    Rect(Position(0, 17), Size(33, 17)),
    Rect(Position(0, 34), Size(33, 17)),
    Rect(Position(0, 51), Size(33, 17)),
    Rect(Position(0, 68), Size(33, 17)),
};

PlayerFire::PlayerFire(void) :
    AnimatedSprite(RTypeProperties::_directPath + "/rsrc/sprites/r-typesheet1.gif",
                   Position(0, 0), 0, _spriteSheet, 0.08, Size(3, 3))
{}

void PlayerFire::nextAnim(void) noexcept
{
    if (getAnimIndex() < 7)
        setAnimIndex(getAnimIndex() + 1);
    else
        setAnimIndex(0);
}

const SpriteSheetRects PlayerFire::_spriteSheet = {
//    Rect(Position(143, 18), Size(166 - 143, 50 - 18)),
    Rect(Position(0, 51), Size(33, 83 - 51))
};
