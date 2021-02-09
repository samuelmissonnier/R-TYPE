/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Player.hpp
*/

#ifndef SPRITE_DEF_HPP_
#define SPRITE_DEF_HPP_

#include "../Sprite.hpp"
#include "../Directional.hpp"

class Player : public AnimatedSprite, public Directional {
public:
    typedef AnimatedSprite Super;

    Player(const Position &pos, const size_t &playerType);
    Player(const std::vector<std::string> &data);
    ~Player(void) = default;

    virtual std::string toString(void) const noexcept override;

    virtual void nextAnim(void) noexcept override;

    virtual void setPosition(const Position &pos) noexcept override;

    void setPosition(const Position &pos, const Size &screenSize) noexcept;

    virtual void setDirection(const Direction &direction) noexcept override;

private:
    static const SpriteSheetRects _spriteSheet;
};

class PlayerFire : public AnimatedSprite {
public:
    PlayerFire(void);
    ~PlayerFire(void) = default;

    virtual void nextAnim(void) noexcept;

private:
    static const SpriteSheetRects _spriteSheet;
};

#endif /* SPRITE_DEF_HPP_ */
