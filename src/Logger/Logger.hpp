/*
** EPITECH PROJECT, 2020
** Logger
** File description:
** Logger.hpp
*/

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <string>

enum LogLvl {LOG, WARNING, ERROR};

class Logger {
public:
    static std::string log(LogLvl lvl, const std::string &str) noexcept;
};

#endif /* LOGGER_HPP_ */
