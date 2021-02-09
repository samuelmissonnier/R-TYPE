/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** SharedEntity.hpp
*/

#ifndef SHARED_ENTITY_HPP_
#define SHARED_ENTITY_HPP_

#include <string>

class SharedEntity {
public:
    SharedEntity(void);
    SharedEntity(size_t id);
    ~SharedEntity(void) = default;

    virtual std::string toString(void) const noexcept = 0;

    size_t getId(void) const noexcept { return _id; }

    void setId(size_t id) noexcept;

    bool isShared(void) const noexcept { return _isShared; }

private:
    size_t _id;
    bool _isShared;
    static size_t _idCount;
};

#endif /* SHARED_ENTITY_HPP_ */
