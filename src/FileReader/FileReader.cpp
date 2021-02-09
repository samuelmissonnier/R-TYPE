/*
** EPITECH PROJECT, 2020
** FileReader
** File description:
** FileReader.cpp
*/

#include "FileReader.hpp"
#include <algorithm>
#include <functional>
#include <fstream>

std::vector<std::string> FileReader::readFile(const std::string &file) const
{
    std::vector<std::string> fileContent;
    std::ifstream fs(file);
    std::string line;

    if (!fs.is_open())
        throw CouldNotOpenFileException(file);
    while (std::getline(fs, line))
        fileContent.push_back(line);
    fs.close();
    return fileContent;
}

std::vector<std::string> FileReader::readFile(const std::vector<std::string> &files) const
{
    std::vector<std::string> filesContent;

    for (auto file : files) {
        std::vector<std::string> fileContent = readFile(file);
        filesContent.insert(filesContent.end(), fileContent.begin(), fileContent.end());
    }
    return filesContent;
}

FileReaderException::FileReaderException(const std::string &str) :
    RTypeException("FileReader", str)
{}

CouldNotOpenFileException::CouldNotOpenFileException(const std::string &filepath) :
    FileReaderException("Could not open: " + filepath)
{}
