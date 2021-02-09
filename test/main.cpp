/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-killian.herbreteau
** File description:
** main.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <locale>
#include <codecvt>
#include <algorithm>

std::pair<std::pair<double, double>, std::vector<int>> convertStringInToPos(std::string toParse, size_t len, bool state)
{
    std::string getlol;
    std::string stock;
    std::pair<std::pair<double, double>, std::vector<int>> final;

    for (size_t i = 0; i != len; i++) {
        size_t found = toParse.find(':');
        if (found != std::string::npos) {
            getlol = toParse.substr(found + 1);
            size_t found2 = getlol.find(':');
            if (found2 != std::string::npos) {              
                stock = toParse.substr(found + 1, found2);
                state == true ? final.first.first = std::atof(stock.c_str()) : final.first.first = 0;
                state == false ? final.second.push_back(std::atoi(stock.c_str())) : final.second.push_back(0);
                toParse = getlol;
            }
        }
    }
    state == true ? final.first.second = std::atof(getlol.c_str()) : final.first.second = 0;
    state == false ? final.second.push_back(std::atoi(getlol.c_str())) : final.second.push_back(0);
    return final;
}

int main(int ac, char **av)
{
    std::string test = "pos:1.21:1.22";
    std::pair<double, double> test1;
    std::string getlol;
    std::string stock;
    size_t len = std::count(test.begin(), test.end(), ':');

    //std::cerr << len << std::endl;final.second.push_back(std::atoi(stock.c_str()))
    std::pair<std::pair<double, double>, std::vector<int>> final = convertStringInToPos(test, std::count(test.begin(), test.end(), ':'), true);

    /*std::cerr << final.second[0] << std::endl;
    std::cerr << final.second[1] << std::endl;
    std::cerr << final.second[2] << std::endl;
    std::cerr << final.second[3] << std::endl;
    std::cerr << final.second[4] << std::endl;*/
    /*for (size_t i = 0; i != len; i++) {
        size_t found = test.find(':');
        if (found != std::string::npos) {
            getlol = test.substr(found + 1);
            size_t found2 = getlol.find(':');
            if (found2 != std::string::npos) {              
                stock = test.substr(found + 1, found2);
                std::cerr << "stock = " << stock << std::endl;
                //test.substr(found + 1, found2);
                test = getlol;
                //test1.first = std::atof(test.substr(found + 1).c_str());
                //std::cerr << test1.first << std::endl;
                //std::cerr << getlol << std::endl;
                //getlol = test.substr((found2 + found) + 2);
                //std::cerr << getlol << std::endl;
                //test1.second = std::atof(getlol.c_str());
            }
        }
    }*/



    /*if (found!=std::string::npos) {
        getlol = test.substr(found + 1);
        size_t found2 = getlol.find(':');
            if (found2 != std::string::npos) {              
                getlol = test.substr(found + 1, found2);
                test1.first = std::atof(getlol.c_str());
                getlol = test.substr((found2 + found) + 2);
                test1.second = std::atof(getlol.c_str());
            }
    }*/
    std::cerr << final.first.first << std::endl;
    std::cerr << final.first.second << std::endl;
    return (0);
}