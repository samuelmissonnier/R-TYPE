/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** RTypeException.hpp
*/

#ifndef RTYPEEXCEPTION_HPP_
#define RTYPEEXCEPTION_HPP_

#include <string>
#include <exception>

class RTypeException : public std::exception {
public:
    RTypeException(const std::string &moduleName, const std::string &str);
    ~RTypeException(void) = default;

    virtual const char *what(void) const throw() override;

private:
    std::string _str;
};

#endif /* RTYPEEXCEPTION_HPP_ */
