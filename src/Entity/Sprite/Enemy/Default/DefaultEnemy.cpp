/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** DefaultEnemy.cpp
*/

#include "DefaultEnemy.hpp"
#include "../../../../Properties/RTypeProperties.hpp"

DefaultEnemy::DefaultEnemy(const Position &pos) :
    AEnemy(RTypeProperties::_directPath + "/rsrc/sprites/r-typesheet5.gif",
           _spriteSheetRects, pos, 1, 7, Size(3, 3), "Left")
{}

const SpriteSheetRects DefaultEnemy::_spriteSheetRects = {
    Rect(Position(0, 0), Size(33, 36))
};

// std::shared_ptr<Projectile> DefaultEnemy::fire(void) const noexcept
// {
//     return std::shared_ptr<Projectile>(new DefaultEnemyProjectile(getPosition()));
// }

extern "C"
{
    AEnemy *getInstance(void)
    {
        return new DefaultEnemy({0, 0});
    }
}
