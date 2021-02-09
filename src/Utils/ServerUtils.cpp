/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** ServerUtils
*/

#include "ServerUtils.hpp"

std::vector<std::string> ServerUtils::readMap(std::string mapLine)
{
    std::vector<std::string> map;

    int i = 0;
    mapLine = mapLine.substr(mapLine.find('{') + 1, mapLine.find('}') - 1);
    while (mapLine.size() && i < 5) {
        i++;
        size_t it = mapLine.find('\"') + 1;
        if (it != std::string::npos) {
            size_t it2 = mapLine.substr(it).find('\"');
            if (it2 != std::string::npos) {
                map.push_back(mapLine.substr(it, it2));
                mapLine = mapLine.substr(it + it2 + 1);
            } else
                break;
        } else
            break;
    }
    return map;
}
