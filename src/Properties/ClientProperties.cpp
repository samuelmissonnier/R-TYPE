/*
** EPITECH PROJECT, 2020
** ClientProperties
** File description:
** ClientProperties.cpp
*/

#include "ClientProperties.hpp"

std::pair<int, int> ClientProperties::_screenSize{1620, 880};

double ClientProperties::_framerate = 30;

double ClientProperties::_volume = 0.5;

std::vector<KeyboardInput> ClientProperties::_keys = {
    KeyboardInput::Q, KeyboardInput::D, KeyboardInput::Z,
    KeyboardInput::S, KeyboardInput::SPACE};

std::unique_ptr<RTypeClient> ClientProperties::_client = nullptr;

IInterfaceManager *ClientProperties::_interfaceManager = nullptr;
