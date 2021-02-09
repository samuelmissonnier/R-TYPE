/*
** EPITECH PROJECT, 2020
** Parser
** File description:
** Parser
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <string>
#include <vector>
#include <iostream>

class Parser {
    public:
        Parser();
        ~Parser();
        std::vector<std::string> findString
        (const std::string &firstSeparator, const std::string &secondSeparator,
        std::string users, std::vector<std::string> allUsers);
        std::vector<std::string> supprQuotes(std::vector<std::string> vect);
    protected:
    private:
};

// std::vector<std::string> getArgs(const std::string &command);
// std::vector<std::vector<std::string>> getMap(const std::string &command);

#endif /* !PARSER_HPP_ */
