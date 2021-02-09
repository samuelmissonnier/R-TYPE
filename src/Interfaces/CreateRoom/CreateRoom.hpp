/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** CreateRoom.hpp
*/

#ifndef CREATE_ROOM_HPP_
#define CREATE_ROOM_HPP_

#include "../Interface.hpp"
#include "../../Utils/ClientUtils.hpp"
#include "../NetworkInterface.hpp"

class CreateRoom : public AInterface, public NetworkInterface {
public:
    CreateRoom(void);
    ~CreateRoom(void) = default;

public:
    virtual size_t handleUserEvent(const std::vector<std::shared_ptr<IUserEvent>> &userEvents);

    void handleUserEvent(std::shared_ptr<MouseEvent> mouseEvent);

    void handleUserEvent(std::shared_ptr<TextEvent> textEvent);

    static std::shared_ptr<IInterface> getInstance(void)
        {
            return std::shared_ptr<IInterface>(new CreateRoom);
        }

    static CreateRoom * getInterface(void) noexcept
        {
            return ClientUtils::getInterface<CreateRoom>(InterfaceManager::CreateRoom).get();
        }

private:
    size_t _nextLoopInterface;
    const std::vector<std::shared_ptr<IEntity>> _background;
    const std::vector<std::shared_ptr<IEntity>> _sprite;
    const TriStateColor _defaultButtonColor;
    const std::vector<std::shared_ptr<Button>> _buttons;
    const RGBAColor _defaultTextColor;
    const std::string _fontPath;
    const std::vector<std::shared_ptr<Text>> _texts;
    const std::shared_ptr<Text> _textInput;
};

#endif /* CREATE_ROOM_HPP_ */
