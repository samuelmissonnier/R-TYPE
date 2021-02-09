/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** ClientUtils.hpp
*/

#ifndef CLIENTUTILS_HPP_
#define CLIENTUTILS_HPP_

#include "../Entity/Entity.hpp"
#include "../Entity/Sprite/Sprite.hpp"
#include "../Interfaces/Interface.hpp"
#include "RTypeUtils.hpp"
#include "../Interfaces/InterfaceManager.hpp"
#include "../Properties/ClientProperties.hpp"
#include <locale>
#include <codecvt>

class ClientUtils : public RTypeUtils {
public:

    static bool isPosInRect(Square *square, Position pos) noexcept;

    static bool isOutOfScreen(IEntity *entity) noexcept;

    static Entities creatEntities(const std::vector<std::vector<std::string>> &map);

    static std::string convertWstringInToString(const std::wstring &str) noexcept;

    static std::wstring convertStringInToWtring(const std::string &str) noexcept;

    static std::pair<std::pair<double, double>, std::vector<int>> convertStringInToPos(std::string toParse, size_t len, bool state);

    template<typename T>
    static bool isDuplicateKey(const std::vector<T> &keys) noexcept
        {
            for (size_t j = 0; j != keys.size(); j++) {
                for (size_t i = j + 1; i != keys.size(); i++) {
                    if (keys[j] == keys[i])
                        return true;
                }
            }
            return false;
        }

    template<typename T>
    static std::shared_ptr<T> getInterface(InterfaceManager::Interface index)
        {
            return std::dynamic_pointer_cast<T>(ClientProperties::_interfaceManager->getInterface(static_cast<size_t>(index) - 1));
        }
};

#endif /* CLIENTUTILS_HPP_ */
