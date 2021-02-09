/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Test.cpp
*/

#include "Test.hpp"

ATest::ATest(const std::string &testName, const testFunction &func) :
    _testName(testName), _func(func)
{}

bool ATest::executeTest(void)
{
    return _func();
}

const std::string ATest::getTestName(void) const noexcept
{
    return _testName;
}
