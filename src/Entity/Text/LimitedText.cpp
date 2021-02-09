/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** LimitedText.cpp
*/

#include "LimitedText.hpp"

LimitedText::LimitedText(const std::string &filepath, const Position &pos,
                         const size_t &size, const RGBAColor &color) :
    Text(filepath, L"error", pos, size, RGBAColor(0, 0, 0, 0)),
    _displayColor(color), _cumuDeltaTime(0), _lifeTime(-1)
{}

void LimitedText::operator+=(double deltaTime) noexcept
{
    if (_cumuDeltaTime < _lifeTime && _lifeTime != -1)
        _cumuDeltaTime += deltaTime;
    else {
        setColor(RGBAColor(0, 0, 0, 0));
    }
}

void LimitedText::display(const std::wstring &str, double lifeTime) noexcept
{
    _lifeTime = lifeTime;
    _cumuDeltaTime = 0;
    setColor(_displayColor);
    setText(str);
}

const double LimitedText::_defaultLifeTime = 3;
