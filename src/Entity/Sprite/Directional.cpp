/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Directional.cpp
*/

#include "Directional.hpp"

Directional::Directional(const Direction &direction) :
    _direction(direction)
{}

const Direction &Directional::getDirection(void) const noexcept
{
    return _direction;
}

void Directional::setDirection(const Direction &direction) noexcept
{
    _direction = direction;
}
