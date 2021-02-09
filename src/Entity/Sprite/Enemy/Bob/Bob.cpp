/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-killian.herbreteau
** File description:
** Bob.cpp
*/

#include "Bob.hpp"  
#include "../../../../Properties/RTypeProperties.hpp"

Bob::Bob(const Position &pos) :
    AEnemy(RTypeProperties::_directPath + "/rsrc/sprites/r-typesheet7.gif",
           _spriteSheetRects, pos, 1, 2, Size(3, 3), "Tan")
{}

const SpriteSheetRects Bob::_spriteSheetRects = {
    Rect(Position(0, 34), Size(33, 33))
};

extern "C"
{
    AEnemy *getInstance(void)
    {
        return new Bob({0, 0});
    }
}