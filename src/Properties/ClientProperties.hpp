/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** ClientProperties.hpp
*/

#ifndef CLIENTPROPERTIES_HPP_
#define CLIENTPROPERTIES_HPP_

#include "../RTypeClient/RTypeClient.hpp"
#include "../Interfaces/InterfaceManager.hpp"
#include <string>
#include "RTypeProperties.hpp"

class ClientProperties : public RTypeProperties {
public:
    static std::pair<int, int> _screenSize;

    static double _framerate;

    static double _volume;

    static std::vector<KeyboardInput> _keys;

    static std::unique_ptr<RTypeClient> _client;

    static IInterfaceManager *_interfaceManager;
};

#endif /* CLIENTPROPERTIES_HPP_ */
