/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Sprite.hpp
*/

#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include "../Entity.hpp"

typedef std::pair<Position, Size> Rect;

class ISprite {
public:
    virtual ~ISprite(void) = default;

    virtual const std::string &getFilepath(void) const noexcept = 0;

    virtual Rect getRect(void) const noexcept = 0;

    virtual bool isAnimated(void) const noexcept = 0;
};

class ASprite : public ISprite, public AEntity {
public:
    ASprite(const std::string &filepath, const Position &pos,
            bool isAnimated = false, const Size &scale = Size(1, 1));
    ASprite(const std::string &filepath, size_t id, const Position &pos,
            bool isAnimated = false, const Size &scale = Size(1, 1));

    ~ASprite(void) = default;

    virtual const std::string &getFilepath(void) const noexcept final { return _filepath; }

    virtual bool isAnimated(void) const noexcept final { return _isAnimated; }

    virtual Rect getRect(void) const noexcept = 0;

private:
    const std::string _filepath;
    const bool _isAnimated;
};

class NotAnimatedSprite : public ASprite {
public:
    NotAnimatedSprite(const std::string &filepath, const Size &imageSize,
                      const Position &pos = Position(0, 0), const Size &scale = Size(1, 1));

    ~NotAnimatedSprite(void) = default;

    virtual Rect getRect(void) const noexcept final;

private:
    const Size _imageSize;
    const Rect _rect;
};

typedef std::vector<Rect> SpriteSheetRects;

class AnimatedSprite : public ASprite {
public:
    AnimatedSprite(const std::string &filepath, const Position &pos,
                   const size_t &line, const SpriteSheetRects &rect,
                   double timeBetweenAnim, const Size &size = {1, 1}, const size_t &animIndex = 0);
    AnimatedSprite(const std::string &filepath, size_t id, const Position &pos,
                   const size_t &line, const SpriteSheetRects &rect,
                   double timeBetweenAnim, const Size &size = {1, 1}, const size_t &animIndex = 0);

    ~AnimatedSprite(void) = default;

    virtual Rect getRect(void) const noexcept final;

    const SpriteSheetRects &getRects(void) const noexcept { return _rect; }

    void operator+=(double deltaTime) noexcept;

    virtual void nextAnim(void) noexcept = 0;

    void setAnimIndex(const size_t &index) noexcept;

    void setAnimLine(const size_t &line) noexcept;

    const size_t &getAnimIndex(void) const noexcept { return _animIndex; }

    const size_t &getAnimline(void) const noexcept { return _lineIndex; }

    double getTimeBetweenAnim(void) const noexcept { return _timeBetweenAnim; }

    double getCumu(void) const noexcept { return _cumuDeltaTime; }

private:
    SpriteSheetRects _rect;
    size_t _lineIndex;
    size_t _animIndex;
    double _timeBetweenAnim;
    double _cumuDeltaTime;
};

std::ostream &operator<<(std::ostream &os, const Rect &rect);

#endif /* SPRITE_HPP_ */
