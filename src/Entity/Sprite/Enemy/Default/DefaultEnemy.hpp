/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** DefaultEnemy.hpp
*/

#ifndef DEFAULTENEMY_HPP_
#define DEFAULTENEMY_HPP_

#include "../Enemy.hpp"

class DefaultEnemy : public AEnemy {
public:
    DefaultEnemy(const Position &pos);
    ~DefaultEnemy(void) = default;

    // virtual std::shared_ptr<Projectile> fire(void) const noexcept override;

private:
    static const SpriteSheetRects _spriteSheetRects;
};

extern "C"
{
    AEnemy *getInstance(void);
}

#endif /* DEFAULTENEMY_HPP_ */
