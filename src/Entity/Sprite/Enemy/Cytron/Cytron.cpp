/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-killian.herbreteau
** File description:
** Cytron.cpp
*/

#include "Cytron.hpp"  
#include "../../../../Properties/RTypeProperties.hpp"

Cytron::Cytron(const Position &pos) :
    AEnemy(RTypeProperties::_directPath + "/rsrc/sprites/r-typesheet3.gif",
           _spriteSheetRects, pos, 1, 11, Size(3, 3), "Red")
{}

const SpriteSheetRects Cytron::_spriteSheetRects = {
    Rect(Position(0, 0), Size(17, 18))
};

extern "C"
{
    AEnemy *getInstance(void)
    {
        return new Cytron({0, 0});
    }
}
