/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Text.cpp
*/

#include "Text.hpp"
#include "../../Utils/RTypeUtils.hpp"

Text::Text(const std::string &filepath, const std::wstring &text,
           const Position &pos, const size_t &size, const RGBAColor &color) :
    AEntity(IEntity::EntityType::Text, pos), Color(color),
    _filepath(filepath), _text(text), _size(size)
{}

std::string Text::toString(void) const noexcept
{
    return "Text:{\"" + std::to_string(getId()) + "\"; \"" + _filepath + "\"; \"" +
        std::string(_text.begin(), _text.end()) + "\"; \"" +
        "\"" + std::to_string(_pos.first) + ":" + std::to_string(_pos.second) + "\"; " +
        "\"" + std::to_string(_size) + "\"; \"" +
        std::to_string(std::get<0>(_color)) + ":" + std::to_string(std::get<1>(_color)) + ":" +
        std::to_string(std::get<2>(_color)) + ":" + std::to_string(std::get<3>(_color)) + "\";}";
}

Text::Text(const std::vector<std::string> &data) :
    AEntity(IEntity::EntityType::Text, std::stoi(data[0]), RTypeUtils::getPosition(data[3])),
    Color(RTypeUtils::getColor(data[5])), _filepath(data[1]),
    _text(std::wstring(data[2].begin(), data[2].end())), _size(std::stoi(data[4]))
{}

const std::string &Text::getFilepath(void) const noexcept
{
    return _filepath;
}

const std::wstring &Text::getText(void) const noexcept
{
    return _text;
}

const size_t &Text::getSize(void) const noexcept
{
    return _size;
}

void Text::setText(const std::wstring &text) noexcept
{
    _text = text;
}

void Text::setSize(const size_t &size) noexcept
{
    _size = size;
}

void Text::operator+=(wchar_t code) noexcept
{
    _text += code;
}

void Text::operator--(void) noexcept
{
    if (_text.size())
        _text = _text.substr(0, _text.size() - 1);
}
