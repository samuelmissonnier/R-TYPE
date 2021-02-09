/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** clientMain.cpp
*/

#include "GameEngine/GameEngine.hpp"
#include "GraphicsEngine/SFMLEngine/SFMLEngine.hpp"
#include "Utils/ClientUtils.hpp"
#include "Properties/ClientProperties.hpp"
#include "Interfaces/InterfaceManager.hpp"

int main(void)
{
    std::unique_ptr<GameEngine> gameEngine(new GameEngine(new SFMLGraphics, new InterfaceManager));

    return gameEngine->loop();
}
