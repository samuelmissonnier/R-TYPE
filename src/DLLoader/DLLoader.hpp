/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** arcade: DLLoader.hpp
*/

#ifndef DLLoader_HPP_
#define DLLoader_HPP_

#include <string>
#include <dlfcn.h>
#include "../RTypeException/DLLoaderException.hpp"
#include <functional>
#include <unordered_map>
#include <vector>

template<typename T>
class DLLoader {
public:
    DLLoader(const std::string &path,
             const std::string &functionName = "getInstance");
    DLLoader(const std::vector<std::string> &paths = {},
             const std::string &functionName = "getInstance");
    ~DLLoader(void);

    DLLoader<T> &loadConstructor(const std::string &path,
                                 const std::string &functionName = "getInstance");

    DLLoader<T> &loadConstructor(const std::vector<std::string> &paths,
                                 const std::string &functionName = "getInstance");

    std::function<T *()> getConstructor(const std::string &path,
                                        const std::string &functionName = "getInstance");

    std::function<T *()> getConstructor(const std::string &path) const;

    std::function<T *(void)> operator[](size_t nb) const;

    /* Attribute */
private:
    std::unordered_map<std::string, std::pair<void *, std::function<T *(void)>>> _libMap;
};
#endif /* DLLoader_HPP_ */
