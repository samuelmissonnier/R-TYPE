/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** arcade: DLLoader.cpp
*/

#include "DLLoader.hpp"
#include "../Logger/Logger.hpp"

template<typename T>
DLLoader<T>::DLLoader(const std::string &path, const std::string &functionName)
{
    loadConstructor(path, functionName);
}


template<typename T>
DLLoader<T>::DLLoader(const std::vector<std::string> &paths, const std::string &functionName)
{
    loadConstructor(paths, functionName);
}

template<typename T>
DLLoader<T>::~DLLoader(void)
{
    for (auto lib : _libMap)
    if (dlclose(lib.second.first) != 0)
        Logger::log(LogLvl::ERROR, dlerror());
}

template<typename T>
DLLoader<T> &DLLoader<T>::loadConstructor(const std::string &path, const std::string &functionName)
{
    if (_libMap.find(path) != _libMap.end()) {
        dlclose(_libMap.at(path).first);
    }
    void *handle = dlopen(path.c_str(), RTLD_LOCAL | RTLD_LAZY | RTLD_NODELETE);
    if (!handle)
        throw DLLoaderException(dlerror());
    void *ret = dlsym(handle, functionName.c_str());
    if (!ret)
        throw DLLoaderException(dlerror());
    _libMap[path] = {handle, static_cast<std::function<T *()>>(reinterpret_cast<T *(*)()>(reinterpret_cast<long>(ret)))};
    return *this;
}

template<typename T>
DLLoader<T> & DLLoader<T>::loadConstructor(const std::vector<std::string> &paths, const std::string &functionName)
{
    for (auto path : paths)
        loadConstructor(path, functionName);
    return *this;
}

template<typename T>
std::function<T *()> DLLoader<T>::getConstructor(const std::string &path,
                                                 const std::string &functionName)
{
    if (_libMap.find(path) == _libMap.end())
        loadConstructor(path, functionName);
    return _libMap.at(path).second;
}

template<typename T>
std::function<T *()> DLLoader<T>::getConstructor(const std::string &path) const
{
    if (_libMap.find(path) == _libMap.end())
        throw DLLoaderException(path + " not initialized");
    return _libMap.at(path).second;
}

template<typename T>
std::function<T *()> DLLoader<T>::operator[](size_t nb) const
{
    if (nb < _libMap.size()) {
        auto it = _libMap.begin();
        while (nb--)
            it++;
        return (*it).second.second;
    } else if (_libMap.size())
        return (*_libMap.begin()).second.second;
    throw DLLoaderException("No contructor found and no default one");
}
