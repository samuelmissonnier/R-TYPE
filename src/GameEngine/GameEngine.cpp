/*
** EPITECH PROJECT, 2020
** GameEngine
** File description:
** GameEngine.cpp
*/

#include "GameEngine.hpp"
#include "../RTypeException/GameEngineExeption.hpp"
#include "../Properties/ClientProperties.hpp"
#include <chrono>

GameEngine::GameEngine(IGraphics *graphicsEngine, IInterfaceManager *interfaceManager) :
    _graphicsEngine(graphicsEngine), _interfaceManager(interfaceManager)
{
    ClientProperties::_interfaceManager = _interfaceManager.get();
}

double GameEngine::getDeltaTime(void)
{
    auto now = std::chrono::system_clock::now();
    double deltaTime = std::chrono::duration<double>(now - _lastLoop).count();
    _lastLoop = now;

    return deltaTime;
}

int GameEngine::loop(void)
{
    double timeBetweenFrame = (1000 / ClientProperties::_framerate) / 1000;
    double timeTillLastFrame = 0;

    _lastLoop = std::chrono::system_clock::now();
    while (_graphicsEngine->isWindowOpen()) {
        double deltaTime = getDeltaTime();
        timeTillLastFrame += deltaTime;
        size_t ret = _interfaceManager->updateActiveInterface(_graphicsEngine->getUserEvent(),
                                                 _graphicsEngine->getMousePos(),
                                                 deltaTime);
        if (!ret)
            _graphicsEngine->closeWindow();
        if (timeTillLastFrame >= timeBetweenFrame) {
            _graphicsEngine->display(_interfaceManager->getActiveEntity());
            timeTillLastFrame = 0;
        }
    }
    return 0;
}
