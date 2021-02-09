/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Text.hpp
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include "../Entity.hpp"

class Text : public AEntity, public Color {
public:
    Text(const std::string &filepath, const std::wstring &text,
         const Position &pos, const size_t &size, const RGBAColor &color);
    Text(const std::vector<std::string> &data);
    ~Text(void) = default;

    const std::string &getFilepath(void) const noexcept;

    const std::wstring &getText(void) const noexcept;

    const size_t &getSize(void) const noexcept;

    virtual void setText(const std::wstring &text) noexcept;

    virtual std::string toString(void) const noexcept override;

    void setSize(const size_t &size) noexcept;

    void operator+=(wchar_t code) noexcept;

    void operator--(void) noexcept;

private:
    const std::string _filepath;
    std::wstring _text;
    size_t _size;
    Position _pos;
    RGBAColor _color;
};

#endif /* TEXT_HPP_ */
