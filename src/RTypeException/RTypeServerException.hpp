/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** RTypeServerException.hpp
*/

#ifndef __RTYPE_SERVER_EXCEPTION_HPP__
#define __RTYPE_SERVER_EXCEPTION_HPP__

#include "RTypeException.hpp"

class RTypeServerException : public RTypeException
{
public:
    RTypeServerException(const std::string &str) :
        RTypeException("RTypeServerException", str) {}
    ~RTypeServerException(void) = default;
};

#endif /* __RTYPE_SERVER_EXCEPTION_HPP__ */
