/*
** EPITECH PROJECT, 2020
** ClientUtils
** File description:
** ClientUtils.cpp
*/

#include "ClientUtils.hpp"
#include "../Interfaces/Menu/Menu.hpp"
#include "../Interfaces/Game/Game.hpp"
#include "../Properties/ClientProperties.hpp"

bool ClientUtils::isPosInRect(Square *square, Position pos) noexcept
{
    return RTypeUtils::isPosInRect(Rect(square->getPosition(), square->getSize()), pos);
}

bool ClientUtils::isOutOfScreen(IEntity *entity) noexcept
{
    return !RTypeUtils::isPosInRect(Rect(Position(0, 0), ClientProperties::_screenSize), entity->getPosition() * entity->getScale());
}

std::string ClientUtils::convertWstringInToString(const std::wstring &str) noexcept
{
    std::string test = std::string(str.begin(), str.end());
    return (test);
}

std::pair<std::pair<double, double>, std::vector<int>> ClientUtils::convertStringInToPos(std::string toParse, size_t len, bool state)
{
    std::string getlol;
    std::string stock;
    std::pair<std::pair<double, double>, std::vector<int>> final;

    for (size_t i = 0; i != len; i++) {
        size_t found = toParse.find(':');
        if (found != std::string::npos) {
            getlol = toParse.substr(found + 1);
            size_t found2 = getlol.find(':');
            if (found2 != std::string::npos) { 
                stock = toParse.substr(found + 1, found2);
                state == true ? final.first.first = std::atof(stock.c_str()) : final.first.first = 0;
                state == false ? final.second.push_back(std::atoi(stock.c_str())) : final.second.push_back(0);
                toParse = getlol;
            }
        }
    }
    state == true ? final.first.second = std::atof(getlol.c_str()) : final.first.second = 0;
    state == false ? final.second.push_back(std::atoi(getlol.c_str())) : final.second.push_back(0);
    return final;
}

Entities ClientUtils::creatEntities(const std::vector<std::vector<std::string>> &map)
{
    Entities entities;
//     std::string type;

//     for (int y = 0; y < map.size(); y++) {
//         type = map[y][0];
//         if (type == "Player" && map[y].size() == 3)
//             entities.push_back(new Player(map[y][1],map[y][2]));
//         if (type == "Enemy" && map[y].size() == 9)
//             entities.push_back(new AEnemy(map[y][1],map[y][2],
// map[y][3],map[y][4],map[y][5],map[y][6],map[y][7],map[y][8]));
//         if (type == "Text" && map[y].size() == 6)
//             entities.push_back(new Text(map[y][1],map[y][2],
// map[y][3],map[y][4],map[y][5]));
//         if (type == "Projectile" && map[y].size() == 10)
//             entities.push_back(new Projectile(map[y][1],map[y][2],
// map[y][3],map[y][4],map[y][5],map[y][6],map[y][7],map[y][8], map[y][9]));
//     }
    return (entities);
}

std::wstring ClientUtils::convertStringInToWtring(const std::string &str) noexcept
{
    return (std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(str));
}
