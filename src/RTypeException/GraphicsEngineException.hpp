/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** GraphicsEngineException.hpp
*/

#ifndef GRAPHICS_ENGINE_EXCEPTION_HPP_
#define GRAPHICS_ENGINE_EXCEPTION_HPP_

#include "RTypeException.hpp"

class GraphicsEngineException : public RTypeException {
public:
    GraphicsEngineException(const std::string &str) :
        RTypeException("GraphicsEngine", str) {}
    ~GraphicsEngineException(void) = default;
};

class WhisperedCases : public GraphicsEngineException {
public:
    WhisperedCases(const std::string &str) :
        GraphicsEngineException(str) {}
};

#endif /* GRAPHICS_ENGINE_EXCEPTION_HPP_ */
