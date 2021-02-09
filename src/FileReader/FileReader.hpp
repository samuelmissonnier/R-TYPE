/*
** EPITECH PROJECT, 2020
** FileReader
** File description:
** FileReader.hpp
*/

#ifndef FILEREADER_HPP_
#define FILEREADER_HPP_

#include <string>
#include <vector>
#include "../RTypeException/RTypeException.hpp"

class IFileReader {
public:
    virtual std::vector<std::string> readFile(const std::string &file) const = 0;
    virtual std::vector<std::string> readFile(const std::vector<std::string> &files) const = 0;
};

class FileReader : public IFileReader {
public:
    FileReader(void) = default;
    ~FileReader(void) = default;

    virtual std::vector<std::string> readFile(const std::string &file) const;
    virtual std::vector<std::string> readFile(const std::vector<std::string> &files) const;
};

class FileReaderException : public RTypeException {
public:
    FileReaderException(const std::string &str);
    ~FileReaderException(void) = default;
};

class CouldNotOpenFileException : public FileReaderException {
public:
    CouldNotOpenFileException(const std::string &filePath);
    ~CouldNotOpenFileException(void) = default;
};

#endif /* FILEREADER_HPP_ */
