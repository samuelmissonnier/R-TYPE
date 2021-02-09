/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Enemy.cpp
*/

#include "Enemy.hpp"
#include "../../../Utils/RTypeUtils.hpp"

AEnemy::AEnemy(const std::string &path, const SpriteSheetRects &spriteSheetRects,
           const Position &pos, double life, size_t nbAnim, const Size &scale,
           const std::string &movement, double timeBetweenAnim,
           const size_t &lineIndex, const size_t &animIndex) :
    AnimatedSprite(path, pos, lineIndex, spriteSheetRects,
                   timeBetweenAnim, scale, animIndex), MovementEnemy(movement),
    _life(life), _nbAnim(nbAnim), _initPos(pos)
{}

AEnemy::AEnemy(const std::vector<std::string> &data) :
    AnimatedSprite(data[1], std::stoi(data[0]), RTypeUtils::getPosition(data[3]),
                   std::stoi(data[6]), RTypeUtils::getRects(data[2]), std::stod(data[5]),
                   RTypeUtils::getPosition(data[4]), std::stoi(data[7])),
    MovementEnemy(data[10]), _life(std::stod(data[8])), _nbAnim(std::stoi(data[9])),
    _initPos(getPosition())
{}

std::string AEnemy::toString(void) const noexcept
{
    std::string str("Enemy:{\"" + std::to_string(getId()) + "\";\"" + getFilepath() + "\";\"");
    for (size_t i = 0; i < getRects().size(); i++) {
        str += std::to_string(getRects()[i].first.first) + ":" + std::to_string(getRects()[i].first.second) + ":" + std::to_string(getRects()[i].second.first) + ":" + std::to_string(getRects()[i].second.second);
        if (i + 1 < getRects().size())
            str += ":";
    }
    str += "\";\"" + std::to_string(getPosition().first) + ":" + std::to_string(getPosition().second) + "\";\"" + std::to_string(getScale().first) + ":" + std::to_string(getScale().second) + "\";\"" + std::to_string(getTimeBetweenAnim()) + "\";\"" + std::to_string(getAnimline()) + "\";\"" + std::to_string(getAnimIndex()) + "\"";
    return str + ";\"" + std::to_string(_life) + "\";\"" + std::to_string(_nbAnim) + "\";\"" + getMovementStr(getMovement()) + "\";}";
}

void AEnemy::move(double deltaTime) noexcept
{
    setPosition(movement(getMovement(), deltaTime, 50, getPosition(), getInitPosition()));
}

void AEnemy::operator-=(double dmg) noexcept
{
    _life -= dmg;
}


void AEnemy::nextAnim(void) noexcept
{
    if (getAnimIndex() < _nbAnim)
        setAnimIndex(getAnimIndex() + 1);
    else
        setAnimIndex(0);
}
