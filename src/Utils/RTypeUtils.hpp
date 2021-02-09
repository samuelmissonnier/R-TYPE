/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** RTypeUtils.hpp
*/

#ifndef R_TYPE_UTILS_HPP_
#define R_TYPE_UTILS_HPP_

#include <string>
#include <chrono>
#include <vector>
#include <memory>
#include <algorithm>
#include "../Parser/Parser.hpp"
#include "../Properties/RTypeProperties.hpp"
#include "../Entity/Entity.hpp"
#include "../Entity/Sprite/Sprite.hpp"

class RTypeUtils {
public:

    static bool isPosInRect(Rect rect, Position pos) noexcept;

    static bool isCollision(Rect rect1, Rect rect2) noexcept;

    template<typename T, typename C>
    static bool isCollision(const T *entity1, const C *entity2) noexcept
        {
            return isCollision(Rect(entity1->getPosition(), entity1->getRect().second),
                        Rect(entity2->getPosition(), entity2->getRect().second));
        }

    static std::string getRepoPath(const std::string &rootFile = RTypeProperties::_repoName);

    static bool isTimePassed(std::chrono::time_point<std::chrono::system_clock> &lastUpdate,
                             const double &range);

    template<typename T, typename C>
    static void removeFromList(std::vector<T *> &vector, const std::shared_ptr<C> &ref)
        {
            auto it = std::find(vector.begin(), vector.end(), ref.get());
            if (it != vector.end())
                vector.erase(it);
        }

    static std::vector<std::string> getArgs(const std::string &command);

    static std::vector<std::vector<std::string>> getMap(const std::string &command);

    static std::vector<std::string> getStringSep(std::string str, const std::string &sep);

    static std::pair<double, double> getPosition(const std::string &data);

    static std::tuple<int, int, int, int> getColor(const std::string &data);

    static std::vector<std::pair<std::pair<double, double>, std::pair<double, double>>> getRects(const std::string &data);

    static std::vector<std::vector<std::string>> splitVector(const std::vector<std::string> &data, int nb);
};

#endif /* R_TYPE_UTILS_HPP_ */
