/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** ServerConnexion.hpp
*/

#ifndef SERVER_CONNEXION_HPP_
#define SERVER_CONNEXION_HPP_

#include "../Interface.hpp"
#include "../NetworkInterface.hpp"
#include "../../Utils/ClientUtils.hpp"

class ServerConnection : public AInterface, public NetworkInterface {
public:
    ServerConnection(void);
    ~ServerConnection(void) = default;

public:
    virtual size_t handleUserEvent(const std::vector<std::shared_ptr<IUserEvent>> &userEvents) override;


    void setErrorText(const std::wstring &error) const noexcept;

    virtual void setConnectionState(ConnectionState state) noexcept override;

    static std::shared_ptr<IInterface> getInstance(void)
        {
            return std::shared_ptr<IInterface>(new ServerConnection);
        };

    static ServerConnection * getInterface(void) noexcept
        {
            return ClientUtils::getInterface<ServerConnection>(InterfaceManager::ServerConnection).get();
        }

private:
    void handleUserEvent(std::shared_ptr<MouseEvent> mouseEvent);

    void handleUserEvent(std::shared_ptr<TextEvent> textEvent);

private:
    size_t _nextLoopInterface;
    const std::vector<std::shared_ptr<IEntity>> _background;
    const std::vector<std::shared_ptr<IEntity>> _sprite;
    const TriStateColor _defaultButtonColor;
    const std::vector<std::shared_ptr<Button>> _buttons;
    const RGBAColor _defaultTextColor;
    const std::string _textFont;
    const std::vector<std::shared_ptr<Text>> _texts;
    const std::vector<std::shared_ptr<Text>> _textsInput;
    std::shared_ptr<AnimatedText> _animatedText;
    const std::vector<std::wstring> _animatedTextTexts;
};

#endif /* SERVER_CONNEXION_HPP_ */
