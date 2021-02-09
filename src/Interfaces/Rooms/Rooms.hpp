/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** Rooms.hpp
*/

#ifndef ROOMS_HPP_
#define ROOMS_HPP_

#include "../Interface.hpp"
#include "../../Utils/ClientUtils.hpp"
#include "../NetworkInterface.hpp"

class Rooms : public AInterface, public NetworkInterface {
public:
    Rooms(void);
    ~Rooms(void) = default;

public:
    virtual size_t handleUserEvent(const std::vector<std::shared_ptr<IUserEvent>> &userEvents);

    void handleUserEvent(std::shared_ptr<MouseEvent> mouseEvent);

    void handleUserEvent(std::shared_ptr<KeyboardEvent> keyboardEvent);

    int getSelectedRoomIndex(void) const noexcept;

    void reloadRooms(const std::vector<std::string> &vector);

    void updateDisplay(void);

    virtual void setConnectionState(ConnectionState state) noexcept override;

    static std::shared_ptr<IInterface> getInstance(void)
        {
            return std::shared_ptr<IInterface>(new Rooms);
        }

    static Rooms *getInterface(void)
        {
            return ClientUtils::getInterface<Rooms>(InterfaceManager::Rooms).get();
        }

private:
    size_t _nextLoopInterface;
    const std::vector<std::shared_ptr<IEntity>> _background;
    const std::vector<std::shared_ptr<IEntity>> _sprite;
    const std::vector<std::shared_ptr<Square>> _squares;
    const TriStateColor _defaultButtonColor;
    const std::vector<std::shared_ptr<Button>> _buttons;
    const std::string _fontFilepath;
    const std::vector<std::shared_ptr<Text>> _roomsText;
    const std::vector<std::shared_ptr<Button>> _roomsButton;
    const std::vector<std::shared_ptr<Text>> _texts;
    std::vector<std::string> _roomsNames;
    size_t _roomsOffset;
};

#endif /* ROOMS_HPP_ */
