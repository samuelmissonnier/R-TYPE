/*
** EPITECH PROJECT, 2020
** Projectile
** File description:
** Projectile.cpp
*/

#include "Projectile.hpp"
#include "../../../Properties/RTypeProperties.hpp"
#include "../../../Utils/RTypeUtils.hpp"

Projectile::Projectile(const std::string &path, const Position &pos, const SpriteSheetRects &rects,
                       double timeBetweenAnim, const std::pair<double, double> &direction,
                       double projectileSpeed, const Size &size,
                       const size_t &lineIndex, const size_t &animIndex) :
    AnimatedSprite(path, pos, lineIndex, rects, timeBetweenAnim, size, animIndex),
    Directional(direction), _projectileSpeed(projectileSpeed)
{}

Projectile::Projectile(const std::vector<std::string> &data) :
    AnimatedSprite(data[1], std::stoi(data[0]), RTypeUtils::getPosition(data[3]),
                   std::stoi(data[6]), RTypeUtils::getRects(data[2]), std::stod(data[5]),
                   RTypeUtils::getPosition(data[4]), std::stoi(data[7])),
    Directional(RTypeUtils::getPosition(data[8])), _projectileSpeed(std::stod(data[9]))
{}

std::string Projectile::toString(void) const noexcept
{
    std::string str("\"" + std::to_string(getId()) + "\" \"" + getFilepath() + "\" \"");
    for (size_t i = 0; i< getRects().size(); i++) {
        str += std::to_string(getRects()[i].first.first) + ":" + std::to_string(getRects()[i].first.second) + ":" + std::to_string(getRects()[i].second.first) + ":" + std::to_string(getRects()[i].second.second);
        if (i + 1 < getRects().size())
            str += ":";
    }
    str += "\" \" " + std::to_string(getPosition().first) + ":" + std::to_string(getPosition().second) + "\" \"" + std::to_string(getScale().first) + ":" + std::to_string(getScale().second) + "\" \"" + std::to_string(getTimeBetweenAnim()) + "\" \"" + std::to_string(getAnimline()) + "\" \"" + std::to_string(getAnimIndex()) + "\"";
    return str + " \"" + std::to_string(getDirection().first) + ":" + std::to_string(getDirection().second) + "\" \"" + std::to_string(_projectileSpeed) + "\"";
}

PlayerProjectile::PlayerProjectile(const Position &pos, double beamPower) :
    Projectile(RTypeProperties::_directPath + "/rsrc/sprites/r-typesheet1.gif",
               pos, _spriteSheet, 0.08, {1, 0}, 200, Size(3, 3), beamPower * 5)
{}

void PlayerProjectile::nextAnim(void) noexcept
{
    switch (getAnimline()) {
    case 0:
        if (getAnimIndex() < 2)
            setAnimIndex(getAnimIndex() + 1);
        break;
    default:
        if (getAnimIndex() < 1)
            setAnimIndex(1);
        break;
    }
}

double PlayerProjectile::getBeamPower(void) const noexcept
{
    return _beamPower;
}

const SpriteSheetRects PlayerProjectile::_spriteSheet = {
    Rect(Position(211, 83), Size(229 - 211, 99 - 83)),
    Rect(Position(231, 103), Size(248 - 231, 115 - 103)),
    Rect(Position(199, 121), Size(232 - 199, 131 - 121)),
    Rect(Position(167, 137), Size(216 - 167, 149 - 137)),
    Rect(Position(135, 154), Size(200 - 135, 168 - 154)),
    Rect(Position(103, 171), Size(184 - 103, 185 - 171))
};

DefaultEnemyProjectile::DefaultEnemyProjectile(const Position &pos) :
    Projectile(RTypeProperties::_directPath + "/rsrc/sprites/r-typesheet43.gif", pos,
               _spriteSheet, 0.2, {-0.2, 0.6}, 50, Size(3, 3))
{}

void DefaultEnemyProjectile::nextAnim(void) noexcept
{
    if (getAnimIndex() < 3)
        setAnimIndex(getAnimIndex() + 1);
    else
        setAnimIndex(0);
}

const SpriteSheetRects DefaultEnemyProjectile::_spriteSheet = {
    Rect(Position(131, 6), Size(148 - 131, 12 - 6))
};
