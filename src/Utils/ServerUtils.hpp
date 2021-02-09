/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** ServerUtils.hpp
*/

#ifndef SERVER_UTILS_HPP_
#define SERVER_UTILS_HPP_

#include "RTypeUtils.hpp"

class ServerUtils : public RTypeUtils {
public:
    static std::vector<std::string> readMap(std::string mapLine);
};

#endif /* SERVER_UTILS_HPP_ */
