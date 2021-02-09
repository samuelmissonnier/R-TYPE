/*
** EPITECH PROJECT, 2020
** babel
** File description:
** DirectoriesManager.cpp
*/

#include "DirectoriesManager.hpp"
#include <dirent.h>
#include <sys/stat.h>

std::vector<std::string> DirectoriesManagerCImpl::
getDirContent(const std::string &path, bool takeHidden) const
{
    std::vector<std::string> result;
    DIR *dir = opendir(path.c_str());
    struct dirent *ent;

    if (dir) {
        while ((ent = readdir(dir))) {
            if (!takeHidden && std::string(ent->d_name)[0] == '.')
                continue;
            if (std::string(ent->d_name) == "." || std::string(ent->d_name) == "..")
                continue;
            result.push_back(ent->d_name);
        }
    }
    else
        throw CouldNotOpenDirException(path);
    closedir(dir);
    return result;
}

DirectoriesManagerException::DirectoriesManagerException(const std::string &str) :
    RTypeException("DirectoriesManager", str)
{}

CouldNotOpenDirException::CouldNotOpenDirException(const std::string &dirPath) :
    DirectoriesManagerException("Could not open dir: " + dirPath)
{}
