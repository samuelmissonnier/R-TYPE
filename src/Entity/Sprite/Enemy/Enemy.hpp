/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Enemy.hpp
*/

#ifndef ENEMIES_HPP_
#define ENEMIES_HPP_

#include "../Sprite.hpp"
#include "../Projectile/Projectile.hpp"
#include "MovementEnemy.hpp"


class IEnemy {
public:
    virtual double getLife(void) const noexcept = 0;

    virtual void operator-=(double dmg) noexcept = 0;

    // virtual std::shared_ptr<Projectile> fire(void) const noexcept = 0;
};

class AEnemy : public IEnemy, public AnimatedSprite, public MovementEnemy {
public:
    AEnemy(const std::string &path, const SpriteSheetRects &spriteSheetRects,
           const Position &pos, double life, size_t nbAnim, const Size &scale,
           const std::string &movement, double timeBetweenAnim = 0.2,
           const size_t &lineIndex = 0, const size_t &animIndex = 0);

    AEnemy(const std::vector<std::string> &data);

    virtual std::string toString(void) const noexcept;

    void move(double deltaTime) noexcept;

    virtual double getLife(void) const noexcept { return _life; }

    virtual double getMove(void) const noexcept { return _life; }

    const Position &getInitPosition(void) const noexcept { return _initPos; }

    virtual void operator-=(double dmg) noexcept;

    virtual void nextAnim(void) noexcept;

    // virtual std::shared_ptr<Projectile> fire(void) const noexcept = 0;

private:
    double _life;
    double _speed;
    size_t _nbAnim;
    const Position _initPos;
};

#endif /* ENEMIES_HPP_ */
