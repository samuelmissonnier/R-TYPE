/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Menu.cpp
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include "../Interface.hpp"
#include <map>

class Menu : public AInterface {
public:
    Menu(void);
    ~Menu(void) = default;

    virtual size_t handleUserEvent(const std::vector<std::shared_ptr<IUserEvent>> &userEvents);

    void handleUserEvent(std::shared_ptr<MouseEvent> mouseEvent);

    void handleUserEvent(std::shared_ptr<TextEvent> texteEvent);

    static std::shared_ptr<IInterface> getInstance()
        {
            return std::shared_ptr<IInterface>(new Menu);
        };

private:
    size_t _nextLoopInterface;
    const std::vector<std::shared_ptr<IEntity>> _backgrounds;
    const TriStateColor _defaultButtonColor;
    const std::vector<std::shared_ptr<Button>> _buttons;
    const RGBAColor _defaultTextColor;
    const std::vector<std::shared_ptr<Text>> _texts;
};

#endif /* MENU_HPP_ */