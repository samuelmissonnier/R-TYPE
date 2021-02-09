/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Directional.hpp
*/

#ifndef DIRECTIONAL_HPP_
#define DIRECTIONAL_HPP_

#include <utility>

typedef std::pair<double, double> Direction;

class Directional {
public:
    Directional(const Direction &direction = Direction(0, 0));

    const Direction &getDirection(void) const noexcept;

    virtual void setDirection(const Direction &direction) noexcept;

private:
    Direction _direction;
};

#endif /* DIRECTIONAL_HPP_ */
