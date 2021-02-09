/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** SharedEntity.cpp
*/

#include "SharedEntity.hpp"

SharedEntity::SharedEntity(void) :
    _isShared(false)
{}

SharedEntity::SharedEntity(size_t id) :
    _id(id), _isShared(true)
{
    _idCount++;
}

void SharedEntity::setId(size_t id) noexcept
{
    _id = id;
}

size_t SharedEntity::_idCount = 0;
