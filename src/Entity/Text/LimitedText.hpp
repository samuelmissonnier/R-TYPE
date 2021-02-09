/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** LimitedText.hpp
*/

#ifndef LIMITED_TEXT_HPP_
#define LIMITED_TEXT_HPP_

#include "Text.hpp"

class LimitedText : public Text {
public:
    LimitedText(const std::string &filepath, const Position &pos,
                const size_t &size, const RGBAColor &color = RGBAColor(255, 0, 0, 255));
    ~LimitedText(void) = default;

    void operator+=(double deltaTime) noexcept;

    void display(const std::wstring &str, double lifeTime = _defaultLifeTime) noexcept;

private:
    static const double _defaultLifeTime;
    const RGBAColor _displayColor;
    double _cumuDeltaTime;
    double _lifeTime;
};

#endif /* LIMITED_TEXT_HPP_ */
