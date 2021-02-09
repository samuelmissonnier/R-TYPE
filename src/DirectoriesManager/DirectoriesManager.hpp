/*
** EPITECH PROJECT, 2020
** babel
** File description:
** DirectoriesManager.hpp
*/

#ifndef DIRECTORIES_MANAGER_HPP_
#define DIRECTORIES_MANAGER_HPP_

#include <string>
#include <vector>
#include "../RTypeException/RTypeException.hpp"

/*
** IDirectoriesManager is used to interface the way you travel through directories
**
** There's a default implementation done with dirent.h as a C implementation called :
** DirectoriesManagerCImpl
*/

class IDirectoriesManager {
public:
    virtual ~IDirectoriesManager(void) = default;

    virtual std::vector<std::string> getDirContent(const std::string &path, bool takeHidden = false) const = 0;
};

class DirectoriesManagerCImpl : public IDirectoriesManager {
public:
    DirectoriesManagerCImpl(void) = default;
    ~DirectoriesManagerCImpl(void) = default;

    virtual std::vector<std::string> getDirContent(const std::string &path, bool takeHidden = false) const;
};

/*
** Directories Manager exception :
**
** DirectoriesManagerException set the module name from where the exception is thrown
** CouldNotOpenDirException need a string to define which directory could not be opened
*/

class DirectoriesManagerException : public RTypeException {
public:
    DirectoriesManagerException(const std::string &str);
    ~DirectoriesManagerException(void) = default;
};

class CouldNotOpenDirException : public DirectoriesManagerException {
public:
    CouldNotOpenDirException(const std::string &dirPath);
    ~CouldNotOpenDirException(void) = default;
};

#endif /* DIRECTORIES_MANAGER_HPP_ */
