/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Interface.hpp
*/

#ifndef INTERFACE_HPP_
#define INTERFACE_HPP_

#include <vector>
#include <memory>
#include <iostream>
#include "../UserEvent/UserEvent.hpp"
#include "../Entity/Form/Form.hpp"
#include "../Entity/Sprite/Sprite.hpp"
#include "../Entity/Text/LimitedText.hpp"
#include "../Entity/Text/AnimatedText.hpp"
#include "../Entity/Sprite/Player/Player.hpp"
#include "../Entity/Sprite/Enemy/Enemy.hpp"
#include "../Entity/Sprite/Projectile/Projectile.hpp"
#include "../Entity/Sound/Sound.hpp"
#include "../UserEvent/KeyboardEvent/KeyboardEvent.hpp"
#include "../UserEvent/MouseEvent/MouseEvent.hpp"
#include "../UserEvent/ScreenEvent/ScreenEvent.hpp"
#include "../UserEvent/TextEvent/TextEvent.hpp"

class IInterfaceManager;

class IInterface {
public:
    virtual ~IInterface(void) = default;

    virtual const Entities &showActiveEntity(void) noexcept = 0;

    virtual size_t handleUserEvent(const std::vector<std::shared_ptr<IUserEvent>> &userEvents) = 0;

    virtual void setMousePos(const Position &pos) noexcept = 0;

    virtual void setDeltaTime(double deltaTime) noexcept = 0;

    virtual LimitedText *getErrorText(void) noexcept = 0;

protected:
    virtual const Position &getMousePos(void) const noexcept = 0;

    virtual double getDeltaTime(void) const noexcept = 0;

};

class AInterface : public IInterface {
public:
    AInterface(void);
    ~AInterface(void) = default;

    virtual size_t handleUserEvent(const std::vector<std::shared_ptr<IUserEvent>> &userEvents) = 0;

    virtual const Entities &showActiveEntity(void) noexcept final { return _activeEntity; }

    virtual void setMousePos(const Position &pos) noexcept final;

    virtual void setDeltaTime(double deltaTime) noexcept final;

    virtual LimitedText *getErrorText(void) noexcept { return _errorText.get(); }

protected:
    virtual const Position &getMousePos(void) const noexcept final { return _mousePos; }

    virtual double getDeltaTime(void) const noexcept final { return _deltaTime; }

protected:
    Entities _activeEntity;
    bool _closeWindow;
    Position _mousePos;
    double _deltaTime;
    const std::shared_ptr<LimitedText> _errorText;
};

#endif /* INTERFACE_MANAGER_HPP_ */
