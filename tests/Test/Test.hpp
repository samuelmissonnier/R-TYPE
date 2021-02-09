/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Test.hpp
*/

#ifndef TEST_HPP_
#define TEST_HPP_

#include <string>
#include <functional>

typedef std::function<bool(void)> testFunction;

class ITest {
public:
    virtual ~ITest(void) = default;

    virtual bool executeTest(void) = 0;

    virtual const std::string getTestName(void) const noexcept = 0;
};

class ATest : public ITest {
public:
    ATest(const std::string &testName, const testFunction &func);
    ~ATest(void) = default;

    virtual bool executeTest(void);

    virtual const std::string getTestName(void) const noexcept;

private:
    const std::string _testName;
    testFunction _func;
};

bool firstTest(void);

#endif /* TEST_HPP_ */
