/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** EnemyGenerator.hpp
*/

#ifndef ENEMY_GENERATOR_HPP_
#define ENEMY_GENERATOR_HPP_

#include "DLLoader.cpp"
#include <vector>
#include "../Entity/Sprite/Enemy/Enemy.hpp"

typedef std::vector<std::shared_ptr<AEnemy>> Enemies;

class EnemyGenerator {
public:
    EnemyGenerator(const std::string &dynamicLibrariesFolder);
    ~EnemyGenerator(void) = default;

    Enemies getEnemies(const std::string &mapPath) const;

private:
    const std::vector<std::string> _libsPath;
    const DLLoader<AEnemy> _libLoader;
};

#endif /* ENEMY_GENERATOR_HPP_ */
