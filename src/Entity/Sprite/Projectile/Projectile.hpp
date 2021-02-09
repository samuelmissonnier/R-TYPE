/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Projectile.hpp
*/

#ifndef PROJECTILE_HPP_
#define PROJECTILE_HPP_

#include "../Sprite.hpp"
#include "../Directional.hpp"

class Projectile : public AnimatedSprite, public Directional{
public:
    Projectile(const std::string &path, const Position &pos, const SpriteSheetRects &rects,
               double timeBetweenAnim, const Direction &direction, double projectileSpeed,
               const Size &size = {1, 1}, const size_t &lineIndex = 0, const size_t &animIndex = 0);
    Projectile(const std::vector<std::string> &data);
    ~Projectile(void) = default;

    virtual std::string toString(void) const noexcept override;

    virtual void nextAnim(void) noexcept = 0;

    double getProjectileSpeed(void) const noexcept { return _projectileSpeed; }

private:
    double _projectileSpeed;
};

class PlayerProjectile : public Projectile {
public:
    PlayerProjectile(const Position &pos, double beamPower);
    ~PlayerProjectile(void) = default;

    virtual void nextAnim(void) noexcept;

    double getBeamPower(void) const noexcept;

private:
    static const SpriteSheetRects _spriteSheet;
    double _beamPower;
};

class DefaultEnemyProjectile : public Projectile {
public:
    DefaultEnemyProjectile(const Position &pos);
    ~DefaultEnemyProjectile(void) = default;

    virtual void nextAnim(void) noexcept;

private:
    static const SpriteSheetRects _spriteSheet;
};

#endif /* PROJECTILE_HPP_ */
