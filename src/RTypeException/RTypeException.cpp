/*
** EPITECH PROJECT, 2020
** RTypeException
** File description:
** RTypeException.cpp
*/

#include "RTypeException.hpp"

RTypeException::RTypeException(const std::string &moduleName, const std::string &str) :
    _str(moduleName + ": " + str)
{}

const char *RTypeException::what(void) const throw()
{
    return _str.c_str();
}
