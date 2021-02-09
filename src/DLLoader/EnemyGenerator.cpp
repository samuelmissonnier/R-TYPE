/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** EnemyGenerator.cpp
*/

#include "EnemyGenerator.hpp"
#include "../FileReader/FileReader.hpp"
#include "../Utils/ServerUtils.hpp"
#include "../DirectoriesReader/DirectoriesReader.hpp"

EnemyGenerator::EnemyGenerator(const std::string &dynamicLibrariesFolder) :
    _libsPath(DirectoriesReaderCImpl().readDirectories(dynamicLibrariesFolder, "so")),
    _libLoader(_libsPath)
{}

Enemies EnemyGenerator::getEnemies(const std::string &mapPath) const
{
    Enemies enemies;
    FileReader fileReader;
    int id = 0;

    for (auto line : fileReader.readFile(mapPath)) {
        try {
            auto args = ServerUtils::readMap(line);
            if (args.size() != 3)
                continue;
            size_t enemyType = std::stoi(args[0]);
            Position pos = Position(std::stod(args[1]), std::stod(args[2]));
            AEnemy *enemy = _libLoader[enemyType]();
            enemies.push_back(std::shared_ptr<AEnemy>(enemy));
            enemy->setPosition(pos);
            enemy->setId(id++);
        } catch (const DLLoaderException &error) {
            throw error;
        } catch (...) {}
    }
    return enemies;
}
