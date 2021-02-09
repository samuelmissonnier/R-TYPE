/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** AnimatedText.hpp
*/

#ifndef ANIMATED_TEXT_HPP_
#define ANIMATED_TEXT_HPP_

#include "Text.hpp"

class AnimatedText : public Text {
public:
    AnimatedText(const std::string &filepath, const Position &pos,
                 const size_t &size, const RGBAColor &color,
                 double timeNextAnim, std::vector<std::wstring> texts);
    ~AnimatedText(void) = default;

    void operator+=(double deltaTime) noexcept;

    void setTexts(const std::vector<std::wstring> &texts) noexcept;

private:
    virtual void setText(const std::wstring &str) noexcept override;

private:
    std::vector<std::wstring> _texts;
    size_t _textsIndex;
    double _timeNextAnim;
    double _cumuDeltaTime;
};

#endif /* ANIMATED_TEXT_HPP_ */
