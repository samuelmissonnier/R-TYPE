/*
** EPITECH PROJECT, 2020
** Tester
** File description:
** Tester.hpp
*/

#ifndef TESTER_HPP_
#define TESTER_HPP_

#include <string>
#include <map>
#include <vector>
#include "../Test/Test.hpp"

class Tester {
public:
    Tester(void);
    ~Tester(void) = default;

    int tests(ITest *test) const noexcept;
    void tests(void) const noexcept;

private:
    std::map<std::string, std::vector<ITest *>> _tests;
};

#endif /* TESTER_HPP_ */
