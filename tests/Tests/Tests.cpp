/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Tests
*/

#include "Tests.hpp"

bool testsGetArgsNarmol(void) {
    std::string str = "100{\"ceci\";\"est\";\"un\";\"test\";}";
    std::vector<std::string> vect = {"ceci","un","est","test"};

    if (RTypeUtils::getArgs(str) == vect)
        return (true);
    return (false);
}

bool testsGetArgsVoidParam(void) {
    std::string str = "100{\"\";}";
    std::vector<std::string> vect = {""};

    if (RTypeUtils::getArgs(str) == vect)
        return (true);
    return (false);
}

bool testsGetArgsVoid(void) {
    std::string str = "";
    std::vector<std::string> vect = {""};

    if (RTypeUtils::getArgs(str) == vect)
        return (true);
    return (false);
}

bool testsGetMapVoidNarmol(void) {
    std::string str = "100{\"ceci\";\"est\";}{\"un\";\"test\";}";
    std::vector<std::vector<std::string>> vect = {{"ceic","est"},{"un","test"}};

    if (RTypeUtils::getMap(str) == vect)
        return (true);
    return (false);
}

bool testsGetMapVoid(void) {
    std::string str = "";
    std::vector<std::vector<std::string>> vect = {{""}};

    if (RTypeUtils::getMap(str) == vect)
        return (true);
    return (false);
}

bool testsStringSepNarmol(void) {
    std::string str = "bonjour a tous";
    std::string sep = " ";
    std::vector<std::string> vect = {"bonjour", "a", "tous"};

    if (RTypeUtils::getStringSep(str, sep) == vect)
        return (true);
    return (false);
}

bool testsStringSepVoidSep(void) {
    std::string str = "bonjour a tous";
    std::string sep = "";
    std::vector<std::string> vect = {"bonjour a tous"};

    if (RTypeUtils::getStringSep(str, sep) == vect)
        return (true);
    return (false);
}

bool testsStringSepVoidStr(void) {
    std::string str = "";
    std::string sep = "test";
    std::vector<std::string> vect = {""};

    if (RTypeUtils::getStringSep(str, sep) == vect)
        return (true);
    return (false);
}

bool testsGetPositionNarmol(void) {
    std::string str = "16:2";
    std::pair <double, double> vect = {16,2};

    if (RTypeUtils::getPosition(str) == vect)
        return (true);
    return (false);
}

bool testsGetPositionTest(void) {
    std::string str = "test";
    std::pair <double, double> vect = {};

    if (RTypeUtils::getPosition(str) == vect)
        return (true);
    return (false);
}

bool testsGetColorNarmol(void) {
    std::string str = "16:16:2:156";
    std::tuple <int, int, int, int> vect = {16,16,2,156};

    if (RTypeUtils::getColor(str) == vect)
        return (true);
    return (false);
}

bool testsGetColorTest(void) {
    std::string str = "test:a:r:v";
    std::tuple <int, int, int, int> vect = {};

    if (RTypeUtils::getColor(str) == vect)
        return (true);
    return (false);
}

bool testsSplitVectorNarmol(void) {
    std::vector<std::string> str = {"ceci","est","un","test"};
    std::vector<std::vector<std::string>> vect = {{"ceci","est"},{"un","test"}};

    if (RTypeUtils::splitVector(str, 2) == vect)
        return (true);
    return (false);
}

bool testsSplitVectorVoidStr(void) {
    std::vector<std::string> str = {""};
    std::vector<std::vector<std::string>> vect = {{""}};

    if (RTypeUtils::splitVector(str, 2) == vect)
        return (true);
    return (false);
}

bool testsSplitVectorVoidNb(void) {
    std::vector<std::string> str = {"ceci","est","un","test"};
    std::vector<std::vector<std::string>> vect = {{""}};

    if (RTypeUtils::splitVector(str, 0) == vect)
        return (true);
    return (false);
}