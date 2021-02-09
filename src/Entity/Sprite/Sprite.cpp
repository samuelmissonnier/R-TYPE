/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Sprite.cpp
*/

#include "Sprite.hpp"
#include <iostream>

ASprite::ASprite(const std::string &filepath, const Position &pos,
                 bool isAnimated, const Size &scale) :
    AEntity(IEntity::Sprite, pos, scale), _filepath(filepath),
    _isAnimated(isAnimated)
{}

ASprite::ASprite(const std::string &filepath, size_t id, const Position &pos,
                 bool isAnimated, const Size &scale) :
    AEntity(IEntity::Sprite, id, pos, scale), _filepath(filepath),
    _isAnimated(isAnimated)
{}

NotAnimatedSprite::NotAnimatedSprite(const std::string &filepath, const Size &imageSize,
                                     const Position &pos, const Size &scale) :
    ASprite(filepath, pos, false, scale), _rect(Position(0, 0), imageSize)
{}

Rect NotAnimatedSprite::getRect(void) const noexcept
{
    return _rect;
}

AnimatedSprite::AnimatedSprite(const std::string &filepath, const Position &pos,
                               const size_t &lineIndex, const SpriteSheetRects &rect,
                               double timeBetweenAnim, const Size &scale,
                               const size_t &animIndex) :
    ASprite(filepath, pos, true, scale), _rect(rect), _lineIndex(lineIndex),
    _animIndex(animIndex), _timeBetweenAnim(timeBetweenAnim), _cumuDeltaTime(0)
{}

AnimatedSprite::AnimatedSprite(const std::string &filepath, size_t id, const Position &pos,
                               const size_t &lineIndex, const SpriteSheetRects &rect,
                               double timeBetweenAnim, const Size &scale,
                               const size_t &animIndex) :
    ASprite(filepath, id, pos, true, scale), _rect(rect), _lineIndex(lineIndex),
    _animIndex(animIndex), _timeBetweenAnim(timeBetweenAnim), _cumuDeltaTime(0)
{}

Rect AnimatedSprite::getRect(void) const noexcept
{
    const Rect &rect = _rect[_lineIndex];
    Position start(rect.first.first + rect.second.first * _animIndex, rect.first.second);
    return Rect(start, Size(rect.second.first, rect.second.second));
}

void AnimatedSprite::operator+=(double deltaTime) noexcept
{
    _cumuDeltaTime += deltaTime;
    if (_cumuDeltaTime >= _timeBetweenAnim) {
        nextAnim();
        _cumuDeltaTime = 0;
    }
}

void AnimatedSprite::setAnimLine(const size_t &line) noexcept
{
    if (line < _rect.size()) {
        _lineIndex = line;
        _cumuDeltaTime = 0;
    }
}

void AnimatedSprite::setAnimIndex(const size_t &index) noexcept
{
    _animIndex = index;
    _cumuDeltaTime = 0;
}

std::ostream &operator<<(std::ostream &os, const Rect &rect)
{
    os << "{" << rect.first << ", " << rect.second << "}";
    return os;
}
