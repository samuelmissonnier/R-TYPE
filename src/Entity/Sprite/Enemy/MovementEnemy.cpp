/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** MovementEnemy.cpp
*/

#include "MovementEnemy.hpp"
#include <cmath>

MovementEnemy::MovementEnemy(const std::string &movement) :
    _movement(getMovement(movement))
{}

std::string MovementEnemy::getMovementStr(MovementEnemy::MovementType movement)
{
    switch (movement) {
    case MovementEnemy::MovementType::RED:
        return "Red";
        break;
    case MovementEnemy::MovementType::LEFT:
        return "Left";
        break;
    case MovementEnemy::MovementType::TAN:
        return "Tan";
        break;
    case MovementEnemy::MovementType::SIN:
        return "Sin";
        break;
    default:
        return getMovementStr(MovementType::DEFAULT);
        break;
    }
}

MovementEnemy::MovementType MovementEnemy::getMovement(const std::string &movement)
{
    if (movement == "Red")
        return MovementEnemy::MovementType::RED;
    if (movement == "Left")
        return MovementEnemy::MovementType::LEFT;
    if (movement == "Tan")
        return MovementEnemy::MovementType::TAN;
    if (movement == "Sin")
        return MovementEnemy::MovementType::SIN;
    return MovementEnemy::MovementType::DEFAULT;
}

Position MovementEnemy::movement(MovementEnemy::MovementType movementKind, double deltaTime, double speed, const Position &position, const Position &startPosition)
{
    if (movementKind == MovementEnemy::MovementType::LEFT)
        return leftMovement(deltaTime, speed, position);
    if (movementKind == MovementEnemy::MovementType::TAN)
        return tanMovement(deltaTime, speed, position, startPosition);
    if (movementKind == MovementEnemy::MovementType::SIN)
        return sinMovement(deltaTime, speed, position, startPosition);
    if (movementKind == MovementEnemy::MovementType::RED)
        return redMovement(deltaTime, speed, position, startPosition);
    return position;
}

Position MovementEnemy::leftMovement(double deltaTime, double speed,
                                     Position position)
{
    position.first -= (speed * deltaTime);
    return position;
}

Position MovementEnemy::tanMovement(double deltaTime, double speed,
                                    Position position, const Position &startPosition)
{
    position.first -= (speed * deltaTime);
    position.second = startPosition.second + std::tan(position.first / 50) * 50;
    return position;
}

Position MovementEnemy::sinMovement(double deltaTime, double speed, Position position, 
const Position &startPosition)
{
    position.first -= (speed * deltaTime);
    position.second = startPosition.second - std::sin(position.first / 10) * 10;
    return position;
}

Position MovementEnemy::redMovement(double deltaTime, double speed, Position position, 
const Position &startPosition)
{
    position.first -= (speed * deltaTime);
    //position.second += (speed * deltaTime);

    if (startPosition.first - position.first <= 50)
        position.second -= (speed * deltaTime);
    if (startPosition.first - position.first > 50 && startPosition.first - position.first <= 100) {
        position.second += (speed * deltaTime);
    }
    if (startPosition.first - position.first > 100 && startPosition.first - position.first <= 150) {
          position.second += (speed * deltaTime);
    }
    if (startPosition.first - position.first > 150 && startPosition.first - position.first <= 200) {
        position.second -= (speed * deltaTime);
    }
    /*if (startPosition.first - position.first > 200 && startPosition.first - position.first <= 250) {
          position.second += (speed * deltaTime);
    }
    if (startPosition.first - position.first > 250 && startPosition.first - position.first <= 300) {
        position.second -= (speed * deltaTime);
    }*/
    if (startPosition.first - position.first > 300 && startPosition.first - position.first <= 350) {
          position.second += (speed * deltaTime);
    }
    if (startPosition.first - position.first > 350 && startPosition.first - position.first <= 400) {
        position.second -= (speed * deltaTime);
    }
    if (startPosition.first - position.first > 400 && startPosition.first - position.first <= 450) {
          position.second += (speed * deltaTime);
    }
    if (startPosition.first - position.first > 450 && startPosition.first - position.first <= 500) {
        position.second -= (speed * deltaTime);
    }
    /*if (startPosition.first - position.first > 500 && startPosition.first - position.first <= 550) {
          position.second += (speed * deltaTime);
    }*/
    return position;
}
