/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Entity.hpp
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include "Sprite/Directional.hpp"
#include "SharedEntity.hpp"

class IEntity;

typedef std::pair<double, double> Position;
typedef std::pair<double, double> Size;
typedef std::vector<IEntity *> Entities;

class IEntity {
public:
    enum EntityType {Sprite, Form, Text, Sound};

    virtual ~IEntity(void) = default;

    virtual EntityType getType(void) const noexcept = 0;

    virtual const Position &getPosition(void) const noexcept = 0;

    virtual void setPosition(const Position &pos) noexcept = 0;

    virtual void setPosition(double speed, const Direction &direction, double deltaTime) noexcept = 0;

    virtual const Size &getScale(void) const noexcept = 0;

    virtual void setScale(const Size &scale) noexcept = 0;
};

class AEntity : public IEntity, public SharedEntity {
public:
    AEntity(EntityType entityType, const Position &pos = Position(0, 0), const Size &scale = Size(1, 1));
    AEntity(EntityType entityType, size_t id, const Position &pos = Position(0, 0), const Size &scale = Size(1, 1));

    ~AEntity(void) = default;

    virtual std::string toString(void) const noexcept;

    virtual EntityType getType(void) const noexcept;

    virtual const Position &getPosition(void) const noexcept;

    virtual void setPosition(const Position &pos) noexcept;

    virtual void setPosition(double speed, const Direction &direction, double deltaTime) noexcept;

    virtual const Size &getScale(void) const noexcept;

    virtual void setScale(const Size &scale) noexcept;

private:
    const EntityType _type;
    Position _pos;
    Size _scale;
};

typedef std::tuple<int, int, int, int> RGBAColor;

class Color {
public:
    //enum Col {RED, YELLOW, GREEN, BLUE, WHITE, BLACK, PURPLE};

    Color(const RGBAColor &color);
    Color(const std::string &color);
    ~Color(void) = default;

    const RGBAColor &getColor(void) const noexcept;

    void setColor(const RGBAColor &color) noexcept;

private:
     RGBAColor _color;
     std::string _colors;
};

Position operator+(const Position &pos, const Position &pos2);
Position operator-(const Position &pos, const Position &pos2);
Position operator*(const Position &pos, const double &rat);
Position operator*(const Position &pos, const Position &pos2);
std::ostream &operator<<(std::ostream &os, const Position &pos);

#endif /* ENTITY_HPP_ */
