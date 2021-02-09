/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-killian.herbreteau
** File description:
** Sorbet.cpp
*/

#include "Sorbet.hpp"  
#include "../../../../Properties/RTypeProperties.hpp"

Sorbet::Sorbet(const Position &pos) :
    AEnemy(RTypeProperties::_directPath + "/rsrc/sprites/r-typesheet5.gif",
           _spriteSheetRects, pos, 1, 7, Size(3, 3), "Sin")
{}

const SpriteSheetRects Sorbet::_spriteSheetRects = {
    Rect(Position(0, 0), Size(33, 36))
};

extern "C"
{
    AEnemy *getInstance(void)
    {
        return new Sorbet({0, 0});
    }
}