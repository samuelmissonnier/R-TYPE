/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** AnimatedText.cpp
*/

#include "AnimatedText.hpp"

AnimatedText::AnimatedText(const std::string &filepath, const Position &pos,
                           const size_t &size, const RGBAColor &color,
                           double timeNextAnim, std::vector<std::wstring> texts) :
    Text(filepath, texts.size() ? texts[0] : L"", pos, size, color), _texts(texts),
     _textsIndex(0), _timeNextAnim(timeNextAnim), _cumuDeltaTime(0)
{}

void AnimatedText::operator+=(double deltaTime) noexcept
{
    _cumuDeltaTime += deltaTime;
    if (_cumuDeltaTime > _timeNextAnim) {
        _cumuDeltaTime = 0;
        _textsIndex++;
        _textsIndex %= _texts.size();
        setText(_texts[_textsIndex]);
    }
}

void AnimatedText::setText(const std::wstring &text) noexcept
{
    Text::setText(text);
}

void AnimatedText::setTexts(const std::vector<std::wstring> &texts) noexcept
{
    _texts = texts;
}
