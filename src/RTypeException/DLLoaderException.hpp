/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** DLLoaderException.hpp
*/

#ifndef DLLOADER_EXCEPTION_HPP_
#define DLLOADER_EXCEPTION_HPP_

#include "RTypeException.hpp"

class DLLoaderException : public RTypeException {
public:
    DLLoaderException(const std::string &str) :
        RTypeException("DLLoader", str) {}
    ~DLLoaderException(void) = default;
};

#endif /* DLLOADER_EXCEPTION_HPP_ */
