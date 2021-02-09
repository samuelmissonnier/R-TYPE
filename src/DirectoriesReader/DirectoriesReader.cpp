/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** DirectoriesReader.cpp
*/

#include "DirectoriesReader.hpp"
#include <sstream>
#include <algorithm>
#include <sys/stat.h>
#include <iostream>
#include <regex>

ADirectoriesReader::ADirectoriesReader(IDirectoriesManager *dm) :
    _dm(std::shared_ptr<IDirectoriesManager>(dm))
{}

DirectoriesReaderCImpl::DirectoriesReaderCImpl(void) :
    ADirectoriesReader(new DirectoriesManagerCImpl())
{}

std::vector<std::string> ADirectoriesReader::readDirectories(
    const std::string &name, const std::string &ext, const int &recDepth)
{
    std::vector<std::string> partResult = _dm->getDirContent(name);
    std::vector<std::string> result;
    struct stat s;

    for (auto it : partResult) {
        std::string path = getPath(name, it);
        stat(path.c_str(), &s);
        if (recDepth != 0 && s.st_mode & S_IFDIR) {
            try {
                std::vector<std::string> res = readDirectories(path, ext, recDepth - 1);
                result.insert(result.end(), res.begin(), res.end());
            } catch (const CouldNotOpenDirException &error) {
                std::cerr << error.what() << std::endl;
            }
        } else if (isFileType(it, ext))
            result.push_back(path);
    }
    return result;
}

std::vector<std::string> ADirectoriesReader::readDirectories(
    const std::vector<std::string> &names, const std::string &ext, const int &recDepth)
{
    std::vector<std::string> result;

    for (auto it : names) {
        try {
            std::vector<std::string> data = readDirectories(it, ext, recDepth);
            result.insert(result.end(), data.begin(), data.end());
        } catch (const CouldNotOpenDirException &error) {
            std::cerr << error.what() << std::endl;
        }
    }
    return result;
}

std::string &ADirectoriesReader::setProperExtension(std::string &ext) noexcept
{
    if (ext.size() > 0 && ext[0] != '.')
        ext.insert(ext.begin(), '.');
    return ext;
}

std::string &ADirectoriesReader::setProperFilepath(std::string &filepath) noexcept
{
    if (filepath == ".") {
        filepath.assign("./");
        return filepath;
    } else if (filepath == "..") {
        filepath.assign("../");
        return filepath;
    } else if (filepath == "")
        return filepath;
    filepath.assign(std::regex_replace(filepath, std::regex("/./"), "/"));
    std::string begin(filepath.substr(0, 2));
    if (begin != "./" && begin != "~/" && filepath.substr(0, 1) != "/")
        filepath.assign("./" + filepath);
    return filepath;
}

std::string ADirectoriesReader::
getPath(const std::string &dir, const std::string &file)
{
    if (dir[dir.size() - 1] != '/')
        return dir + "/" + file;
    return dir + file;
}

bool ADirectoriesReader::
isFileType(const std::string &name, const std::string &ext)
{
    auto it = name.find_last_of('.');
    std::string realExt(ext[0] == '.' ? ext.substr(1, ext.size()) : ext);

    if (it >= name.size())
        return false;
    return name.substr(it + 1, name.size()) == realExt;
}
