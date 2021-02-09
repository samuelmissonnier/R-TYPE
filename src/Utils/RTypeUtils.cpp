/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** RTypeUtils.cpp
*/

#include "RTypeUtils.hpp"
#include "../Properties/RTypeProperties.hpp"

bool RTypeUtils::isPosInRect(Rect rect, Position pos) noexcept
{
    if (pos.first < rect.first.first || pos.first > rect.first.first + rect.second.first)
        return false;
    if (pos.second < rect.first.second || pos.second > rect.first.second + rect.second.second)
        return false;
    return true;
}

bool RTypeUtils::isCollision(Rect rect1, Rect rect2) noexcept
{
    if (isPosInRect(rect1, rect2.first))
        return true;
    if (isPosInRect(rect1, rect2.first + Position(0, rect2.second.second)))
        return true;
    if (isPosInRect(rect1, rect2.first + Position(rect2.second.first, 0)))
        return true;
    if (isPosInRect(rect1, rect2.first + Position(rect2.second.first, rect2.second.second)))
        return true;
    return false;
}

std::string RTypeUtils::getRepoPath(const std::string &rootFile)
{
    std::string path(getenv("PWD"));
    size_t find = path.find(rootFile);
    if (find == std::string::npos)
        return "";
    return path.substr(0, find + rootFile.size());
}

bool RTypeUtils::isTimePassed(std::chrono::time_point<std::chrono::system_clock> &lastUpdate,
                         const double &range)
{
    auto now = std::chrono::system_clock::now();

    if (std::chrono::duration<double>(now - lastUpdate).count() >= range) {
        lastUpdate = now;
        return true;
    }
    return false;
}

std::vector<std::string> RTypeUtils::getArgs(const std::string &command)
{
    Parser pars = Parser();
    std::vector<std::string> av;

    std::vector<std::string> args = pars.findString("\"", "\";", command, av);
    return (pars.supprQuotes(args));
}

std::vector<std::vector<std::string>> RTypeUtils::getMap(const std::string &command)
{
    Parser pars = Parser();
    std::vector<std::vector<std::string>> map;
    std::vector<std::string> av;
    av = pars.findString("{", "}", command, av);

    for (size_t i = 0; i < av.size(); i ++) {
        std::vector<std::string> args;
        map.push_back(pars.supprQuotes(pars.findString("\"", "\";", av[i], args)));
    }
    return (map);
}

std::vector<std::string> RTypeUtils::getStringSep(std::string str, const std::string &sep)
{
    std::vector<std::string> res;
    size_t find;

    while ((find = str.find(sep)) != std::string::npos) {
        res.push_back(str.substr(0, find));
        str = str.substr(find + sep.size());
    }
    res.push_back(str);
    return res;
}

std::pair<double, double> RTypeUtils::getPosition(const std::string &data)
{
    auto pos = getStringSep(data, ":");

    return std::pair<double, double>(std::stod(pos[0]), std::stod(pos[1]));
}


std::tuple<int, int, int, int> RTypeUtils::getColor(const std::string &data)
{
    auto color = getStringSep(data, ":");

    if (color.size() != 4)
        return {0, 0, 0, 0};
    return {std::stoi(color[0]), std::stoi(color[1]), std::stoi(color[2]), std::stoi(color[3])};
}

std::vector<std::pair<std::pair<double, double>, std::pair<double, double>>> RTypeUtils::getRects(const std::string &data)
{
    std::vector<std::pair<std::pair<double, double>, std::pair<double, double>>> res;
    auto rect = getStringSep(data, ":");

    if (rect.size() % 4 != 0)
        return res;
    for (size_t i = 0; i < rect.size() / 4; i++) {
        std::pair<double, double> p1(std::stod(rect[i * 4]), std::stod(rect[i * 4 + 1]));
        std::pair<double, double> p2(std::stod(rect[i * 4 + 2]), std::stod(rect[i * 4 + 3]));
        res.push_back({p1, p2});
    }
    return res;
}

std::vector<std::vector<std::string>> RTypeUtils::splitVector(const std::vector<std::string> &data, int nb)
{
    std::vector<std::vector<std::string>> res;

    if (data.size() % nb != 0)
        return res;
    for (size_t i = 0; i < data.size() / nb; i++)
        res.push_back(std::vector<std::string>(data.begin() + i * nb, data.begin() + (i + 1) * nb));
    return res;
}
