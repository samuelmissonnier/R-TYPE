/*
** EPITECH PROJECT, 2020
** Parser
** File description:
** Parser
*/

#include "Parser.hpp"

Parser::Parser() {}

Parser::~Parser() {}

std::vector<std::string> Parser::findString
(const std::string &firstSeparator, const std::string &secondSeparator,
std::string command, std::vector<std::string> av)
{
    std::string actual;
    int first = command.find(firstSeparator);
    int last = command.find(secondSeparator);

    if (first == command.npos || last == command.npos) {
        return (av);
    }
    if (first < last) {
        actual = command.substr(first, (last - first + 1));
        av.push_back(actual);
    }
    command = command.substr(last + 1);
    return (findString(firstSeparator, secondSeparator, command, av));
}

std::vector<std::string> Parser::supprQuotes(std::vector<std::string> vect)
{
    for (int i = 0; i < vect.size(); i++) {
        vect[i] = vect[i].substr(1, vect[i].size() - 2);
    }
    return (vect);
}

// std::vector<std::string> getArgs(const std::string &command)
// {
//     Parser pars = Parser();
//     std::vector<std::string> av;

//     std::vector<std::string> args = pars.findString("\"", "\";", command, av);
//     return (pars.supprQuotes(args));
// }

// std::vector<std::vector<std::string>> getMap(const std::string &command)
// {
//     Parser pars = Parser();
//     std::vector<std::vector<std::string>> map;
//     std::vector<std::string> av;
//     av = pars.findString("{", "}", command, av);

//     for (int i = 0; i < av.size(); i ++) {
//         std::vector<std::string> args;
//         map.push_back(pars.supprQuotes(pars.findString("\"", "\";", av[i], args)));
//     }
//     return (map);
// }