/*
** EPITECH PROJECT, 2020
** Logger
** File description:
** Logger.cpp
*/

#include "Logger.hpp"

std::string Logger::log(LogLvl lvl, const std::string &str) noexcept
{
    switch (static_cast<int>(lvl)) {
    case LOG:
        return "[\033[34mLOG\033[0m]: " +str;
        break;
    case WARNING:
        return "[\033[33mWARNING\033[0m]: " +str;
        break;
    case ERROR:
        return "[\033[31mERROR\033[0m]: " +str;
        break;
    };
    return "";
}
