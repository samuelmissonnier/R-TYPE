/*
** EPITECH PROJECT, 2020
** GameEngine
** File description:
** GameEngine.hpp
*/

#ifndef GAMEENGINE_HPP_
#define GAMEENGINE_HPP_

#include "../GraphicsEngine/GraphicsEngine.hpp"
#include <functional>
#include "../Interfaces/InterfaceManager.hpp"
#include <chrono>

class GameEngine {
public:
    GameEngine(IGraphics * graphicsEngine, IInterfaceManager *interfaceManager);
    ~GameEngine(void) = default;

    double getDeltaTime(void);

    int loop(void);

private:
    std::unique_ptr<IGraphics> _graphicsEngine;
    std::unique_ptr<IInterfaceManager> _interfaceManager;
    std::chrono::time_point<std::chrono::system_clock> _lastLoop;
};

#endif /* GAMEENGINE_HPP_ */
