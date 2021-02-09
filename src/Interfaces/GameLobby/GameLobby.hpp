/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** GameLobby.hpp
*/

#ifndef GAME_LOBBY_HPP_
#define GAME_LOBBY_HPP_

#include "../Interface.hpp"
#include "../NetworkInterface.hpp"
#include "../../Utils/ClientUtils.hpp"

class GameLobby : public AInterface, public NetworkInterface {
public:
    GameLobby(void);
    ~GameLobby(void) = default;

    enum RequestType {LEAVE, READY};

public:
    virtual size_t handleUserEvent(const std::vector<std::shared_ptr<IUserEvent>> &userEvents);

    void handleUserEvent(std::shared_ptr<MouseEvent> mouseEvent);

    void setRoomName(const std::string &str);

    void reloadPlayersName(const std::vector<std::string> &playersName);

    static std::shared_ptr<IInterface> getInstance()
        {
            return std::shared_ptr<IInterface>(new GameLobby);
        }

    static GameLobby *getInterface(void)
        {
            return ClientUtils::getInterface<GameLobby>(InterfaceManager::GameLobby).get();
        }

    void launchGame(void) noexcept { _isGameLaunched = true; }

private:
    size_t _nextLoopInterface;
    const std::vector<std::shared_ptr<IEntity>> _background;
    std::vector<std::shared_ptr<IEntity>> _sprite;
    const std::vector<std::shared_ptr<Square>> _squares;
    const TriStateColor _defaultButtonColor;
    const std::vector<std::shared_ptr<Button>> _buttons;
    const std::string _textFont;
    const RGBAColor _defaultTextColor;
    const std::vector<std::shared_ptr<Text>> _texts;
    std::vector<std::shared_ptr<Text>> _playersText;
    const std::shared_ptr<Text> _roomName;
    bool _isGameLaunched;
    bool _isReady;
    RequestType _requestType;
};

#endif /* GAME_LOBBY_HPP_ */
