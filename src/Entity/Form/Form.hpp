/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Form.hpp
*/

#ifndef FORM_HPP_
#define FORM_HPP_

#include "../Entity.hpp"

class Form : public AEntity, public Color {
public:
    enum FormType {Square, Circle};

    Form(const Position &pos, const RGBAColor &color, FormType type);
    ~Form(void) = default;

    FormType getFormType(void) const noexcept;

private:
    const FormType _type;
};

class Square : public Form {
public:
    Square(const Position &pos, const Size &size, const RGBAColor &color);
    ~Square(void) = default;

    const Size &getSize(void) const noexcept;

    void setSize(const Size &size) noexcept;

private:
    Size _size;
};

typedef std::tuple<RGBAColor, RGBAColor, RGBAColor>  TriStateColor;

class Button : public Square {
public:
    Button(const Position &pos, const Size &size,
           const TriStateColor &rgb);
    Button(const Position &pos, const Size &size,
           const RGBAColor &rgb);
    Button(const Position &pos, const Size &size,
           const RGBAColor &idle, const RGBAColor &on,
           const RGBAColor &pressed);
    ~Button(void) = default;

    void selected(void) noexcept;

    void on(void) noexcept;

    void idle(void) noexcept;

    bool isIdle(void) const noexcept { return getColor() == std::get<0>(_colors); }

    bool isOn(void) const noexcept { return getColor() == std::get<1>(_colors); }

    bool isSelected(void) const noexcept { return getColor() == std::get<2>(_colors); }

    void operator[](const size_t &nb) noexcept;

private:
    const TriStateColor _colors;
};

class Circle : public Form {
public:
    Circle(const Position &pos, double rad, const RGBAColor &color);
    ~Circle(void) = default;

    double getRad(void) const noexcept;

    void setRad(double radius) noexcept;

private:
    double _rad;
};

#endif /* FORM_HPP_ */
