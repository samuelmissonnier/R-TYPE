/*
** EPITECH PROJECT, 2020
** Sound
** File description:
** Sound.cpp
*/

#include "Sound.hpp"

Sound::Sound(const std::string &filepath, bool isLooping) :
    AEntity(IEntity::EntityType::Sound), _filepath(filepath),
    _isLooping(isLooping), _cumuDeltaTime(0)
{}

const std::string &Sound::getFilepath(void) const noexcept
{
    return _filepath;
}

bool Sound::isLooping(void) const noexcept
{
    return _isLooping;
}

void Sound::operator+=(double deltaTime)
{
    _cumuDeltaTime += deltaTime;
}
