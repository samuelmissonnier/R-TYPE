/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** movmentEnemy.hpp
*/

#ifndef MOVEMENTENEMY_HPP_
#define MOVEMENTENEMY_HPP_

#include <iostream>
#include <string>
#include "../../Entity.hpp"

class MovementEnemy {
    enum MovementType {RED, LEFT, TAN, SIN, DEFAULT = LEFT};

public:
    MovementEnemy(const std::string &movement);
    ~MovementEnemy(void) = default;

    static MovementType getMovement(const std::string &movement);

    static std::string getMovementStr(MovementType type);

    static Position movement(MovementType movementKind, double deltaTime, double speed,
                      const Position &position, const Position &startPosition);

    MovementType getMovement(void) const noexcept { return _movement; }

private:
    static Position leftMovement(double deltaTime, double speed, Position position);

    static Position tanMovement(double deltaTime, double speed, Position position,
                                          const Position &startPosition);

    static Position sinMovement(double deltaTime, double speed, Position position,
                                          const Position &startPosition);

    static Position redMovement(double deltaTime, double speed, Position position,
                                          const Position &startPosition);
private:
    MovementType _movement;
};

#endif /* MOVEMENTENEMY_HPP_ */
