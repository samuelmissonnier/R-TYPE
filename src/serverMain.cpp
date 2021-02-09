/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** serverMain.cpp
*/

#include <iostream>
#include "RTypeServer/RTypeServer.hpp"
#include "DLLoader/EnemyGenerator.hpp"
#include "Properties/ServerProperties.hpp"
#include "Utils/RTypeUtils.hpp"

int main(int ac, char **av)
{
    if (ac == 2 && std::atoi(av[1]) > 0 && std::atoi(av[1]) <= 65536) {
        boost::asio::io_context context;
        RTypeServer server(std::atoi(av[1]), context);

        context.run();
    } else {
        std::cout << "./r_type_server port\n\tport\t:\tnuméro du port (1 à 65536)" << std::endl;
    }
    return 0;
}
