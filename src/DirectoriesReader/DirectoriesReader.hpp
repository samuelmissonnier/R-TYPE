/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** arcade: directoriesReader.hpp
*/

#ifndef DIRECTORIES_READER_HPP
#define DIRECTORIES_READER_HPP

#include <string>
#include <vector>
#include "../DirectoriesManager/DirectoriesManager.hpp"
#include <memory>

/*
** Can throw during Construction when one or more provided file are empty
** Will also write in error output if empty file is find during recusivity
*/

class IDirectoriesReader {
public:
    ~IDirectoriesReader(void) = default;

    virtual std::vector<std::string> readDirectories(const std::string &names,
                                                     const std::string &ext,
                                                     const int &recDepth = 1) = 0;
    virtual std::vector<std::string> readDirectories(const std::vector<std::string> &names,
                                                     const std::string &ext,
                                                     const int &recDepth = 1) = 0;
};

class ADirectoriesReader : public IDirectoriesReader {
public:
    ADirectoriesReader(IDirectoriesManager *dm);
    ~ADirectoriesReader(void) = default;

    virtual std::vector<std::string> readDirectories(const std::string &names,
                                                     const std::string &ext,
                                                     const int &recDepth = 0) final;

    virtual std::vector<std::string> readDirectories(const std::vector<std::string> &names,
                                                     const std::string &ext,
                                                     const int &recDepth = 0) final;
    /* Static function */
    static bool isFileType(const std::string &name, const std::string &ext);
    static std::string getPath(const std::string &dir,
                               const std::string &file);
    static std::string &setProperExtension(std::string &ext) noexcept;
    static std::string &setProperFilepath(std::string &filepath) noexcept;

protected:
    const std::shared_ptr<IDirectoriesManager> _dm;
};

class DirectoriesReaderCImpl : public ADirectoriesReader {
public:
    DirectoriesReaderCImpl(void);
    ~DirectoriesReaderCImpl(void) = default;
};

#endif /* DIRECTORIES_READER_HPP */
