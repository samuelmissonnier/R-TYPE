/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Option.hpp
*/

#ifndef OPTION_HPP_
#define OPTION_HPP_

#include "../Interface.hpp"

class Option : public AInterface {
public:
    Option(void);
    ~Option(void) = default;

public:
    virtual size_t handleUserEvent(const std::vector<std::shared_ptr<IUserEvent>> &userEvents);

    void handleUserEvent(std::shared_ptr<MouseEvent> mouseEvent);

    void handleUserEvent(std::shared_ptr<KeyboardEvent> textEvent);

    static std::shared_ptr<IInterface> getInstance(void)
        {
            return std::shared_ptr<IInterface>(new Option);
        };

private:
    size_t _nextLoopInterface;
    const std::vector<std::shared_ptr<IEntity>> _background;
    const std::vector<std::shared_ptr<IEntity>> _sprite;
    const std::vector<std::shared_ptr<Square>> _squares;
    const TriStateColor _defaultButtonColor;
    const std::vector<std::shared_ptr<Button>> _buttons;
    const std::string _fontPath;
    const std::vector<std::shared_ptr<Text>> _texts;
    const std::vector<std::shared_ptr<Text>> _textsInput;
    std::vector<KeyboardInput> _keys;
};

#endif /* OPTION_HPP_ */
