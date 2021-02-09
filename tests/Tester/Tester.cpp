/*
** EPITECH PROJECT, 2020
** Tester
** File description:
** Tester.cpp
*/

#include "Tester.hpp"
#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
#include <sys/errno.h>
#include <string.h>
#include "../Tests/Tests.hpp"

Tester::Tester(void)
{
}

int Tester::tests(ITest *test) const noexcept
{
    int status;
    size_t pid = fork();
    if (pid) {
        waitpid(pid, &status, WUNTRACED | WCONTINUED);
        return status;
    }
    exit(test->executeTest() ? 0 : 1);
}

void Tester::tests(void) const noexcept
{
    int count = 0;
    int countFailed = 0;
    int countCrashed = 0;
    int countPassed = 0;
    for (auto module : _tests) {
        for (auto test : module.second) {
            count++;
            int status = tests(test);
            std::cout << "[";
            if (WIFEXITED(status)) {
                int ret = status >> 8;
                if (ret) {
                    std::cout << "\033[31mFailed\033[0m";
                    countFailed++;
                } else {
                    countPassed++;
                    std::cout << "\033[32mSuccess\033[0m";
                }
            } else if (WIFSIGNALED(status)) {
                countCrashed++;
                int sig = WTERMSIG(status);
                if (sig == SIGFPE)
                    std::cout << "\033[31mFloating exception\033[0m";
                else
                    std::cout << "\033[31m" << strsignal(sig) << "\033[0m";
            }
            std::cout << "] " << module.first << "::" << test->getTestName() << std::endl;
        }
    }
    std::cout << "[\033[34m======\033[0m] Synthesis: Tested: \033[34m" << count << "\033[0m | ";
    std::cout << "Passed: " << (countPassed ? "\033[32m" : "\033[31m") << countPassed << "\033[0m | ";
    std::cout << "Failed: " << (countFailed ? "\033[31m" : "\033[32m") << countFailed << "\033[0m | ";
    std::cout << "Crashed: " << (countCrashed ? "\033[31m" : "\033[32m") << countCrashed << "\033[0m" << std::endl;
}
