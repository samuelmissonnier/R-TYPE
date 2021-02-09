/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Sound.hpp
*/

#ifndef SOUND_HPP_
#define SOUND_HPP_

#include "../Entity.hpp"

class Sound : public AEntity {
public:
    Sound(const std::string &filepath, bool isLooping = false);
    ~Sound(void) = default;

    const std::string &getFilepath(void) const noexcept;

    bool isLooping(void) const noexcept;

    void operator+=(double deltaTime);

private:
    const std::string _filepath;
    const bool _isLooping;
    double _cumuDeltaTime;
};

#endif /* SOUND_HPP_ */
