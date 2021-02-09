/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Form.cpp
*/

#include "Form.hpp"
#include "../../Utils/ClientUtils.hpp"

Form::Form(const Position &pos, const RGBAColor &color, FormType type) :
    AEntity(IEntity::EntityType::Form, pos), Color(color), _type(type)
{}

Form::FormType Form::getFormType(void) const noexcept
{
    return _type;
}

Square::Square(const Position &pos, const Size &size, const RGBAColor &color) :
    Form(pos, color, Form::FormType::Square), _size(size)
{}

const Size &Square::getSize(void) const noexcept
{
    return _size;
}

void Square::setSize(const Size &size) noexcept
{
    _size = size;
}

Circle::Circle(const Position &pos, double rad, const RGBAColor &color) :
    Form(pos, color, Form::FormType::Circle), _rad(rad)
{}

double Circle::getRad(void) const noexcept
{
    return _rad;
}

void Circle::setRad(double radius) noexcept
{
    _rad = radius;
}

Button::Button(const Position &pos, const Size &size,
               const RGBAColor &idle, const RGBAColor &on,
               const RGBAColor &pressed) :
    Square(pos, size, idle), _colors({idle, on, pressed})
{}

Button::Button(const Position &pos, const Size &size,
               const RGBAColor &rgba) :
    Square(pos, size, rgba), _colors({rgba, rgba, rgba})
{}

Button::Button(const Position &pos, const Size &size,
               const TriStateColor &rgb) :
    Square(pos, size, std::get<0>(rgb)), _colors(rgb)
{}

void Button::selected(void) noexcept
{
    setColor(std::get<2>(_colors));
}

void Button::on(void) noexcept
{
    setColor(std::get<1>(_colors));
}

void Button::idle(void) noexcept
{
    setColor(std::get<0>(_colors));
}
