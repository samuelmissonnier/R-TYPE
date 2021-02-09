/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** GameEngineException.hpp
*/

#ifndef GAME_ENGINE_EXCEPTION_HPP_
#define GAME_ENGINE_EXCEPTION_HPP_

#include "RTypeException.hpp"

class GameEngineException : public RTypeException {
public:
    GameEngineException(const std::string &str) : RTypeException("GameEngine", str) {}
    ~GameEngineException(void) = default;
};

class InvalidInterfaceState : public GameEngineException {
public:
    InvalidInterfaceState(void) : GameEngineException("Invalid interface State") {}
    ~InvalidInterfaceState(void) = default;
};

#endif /* GAME_ENGINE_EXCEPTION_HPP_ */
