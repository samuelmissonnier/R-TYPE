/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Entity.cpp
*/

#include "Entity.hpp"

AEntity::AEntity(IEntity::EntityType entityType, const Position &pos, const Size &scale) :
    _type(entityType), _pos(pos), _scale(scale)
{}

AEntity::AEntity(IEntity::EntityType entityType, size_t id, const Position &pos, const Size &scale) :
    SharedEntity(id), _type(entityType), _pos(pos), _scale(scale)
{}

std::string AEntity::toString(void) const noexcept
{
    return "";
}

IEntity::EntityType AEntity::getType(void) const noexcept
{
    return _type;
}

const Position &AEntity::getPosition(void) const noexcept
{
    return _pos;
}

void AEntity::setPosition(const Position &pos) noexcept
{
    _pos = pos;
}

void AEntity::setPosition(double speed, const Direction &direction, double deltaTime) noexcept
{
    _pos = _pos + Position(speed * deltaTime, speed * deltaTime) * direction;
}

void AEntity::setScale(const Size &scale) noexcept
{
    _scale = scale;
}

const Size &AEntity::getScale(void) const noexcept
{
    return _scale;
}

Color::Color(const RGBAColor &color) :
    _color(color)
{}

Color::Color(const std::string &color) : 
    _colors(color)
{}

const RGBAColor &Color::getColor(void) const noexcept
{
    return _color;
}

void Color::setColor(const RGBAColor &color) noexcept
{
    _color = color;
}

Position operator+(const Position &pos, const Position &pos2)
{
    return Position(pos.first + pos2.first, pos.second + pos2.second);
}

Position operator-(const Position &pos, const Position &pos2)
{
    return Position(pos.first - pos2.first, pos.second - pos2.second);
}

Position operator*(const Position &pos, const double &rat)
{
    return Position(pos.first *rat, pos.second * rat);
}

Position operator*(const Position &pos1, const Position &pos2)
{
    return Position(pos1.first * pos2.first, pos1.second * pos2.second);
}

#include <iostream>
std::ostream &operator<<(std::ostream &os, const Position &pos)
{
    os << "[" << pos.first << ";" << pos.second << "]";
    return os;
}
