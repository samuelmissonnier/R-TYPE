/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-killian.herbreteau
** File description:
** EndGame.cpp
*/

#include "EndGame.hpp"  
#include "../../Properties/ClientProperties.hpp"
#include "../../Utils/ClientUtils.hpp"
#include "../InterfaceManager.hpp"

EndGame::EndGame(void) :
    _backgrounds({
        std::shared_ptr<IEntity>(new NotAnimatedSprite(ClientProperties::_directPath + "/rsrc/sprites/Background2.jpg", ClientProperties::_screenSize, {1, 1})),
        std::shared_ptr<Square>(new Square({(ClientProperties::_screenSize.first / 4), (ClientProperties::_screenSize.second / 4)}, {(ClientProperties::_screenSize.first / 2), 550}, {0, 243, 255, 140}))
    }),
    _defaultTextColor({13, 95, 151, 200}),
    _texts({
        std::shared_ptr<Text>(new Text(ClientProperties::_directPath + "/rsrc/font/SEASRN__.ttf", L"R-TYPE", {530, 30}, 150, _defaultTextColor)),
        std::shared_ptr<Text>(new Text(ClientProperties::_directPath + "/rsrc/font/SEASRN__.ttf", L"R-TYPE", {525, 25}, 150, {0, 243, 255, 255})),
        std::shared_ptr<Text>(new Text(ClientProperties::_directPath + "/rsrc/font/SEASRN__.ttf", L"Your score :", {520, 250}, 75, _defaultTextColor)),
        })

{
    //std::string test = "188999";
    //setScoreEndGame(test);
    for (auto background : _backgrounds)
        _activeEntity.push_back(background.get());
    for (auto text : _texts)
        _activeEntity.push_back(text.get());
}

size_t EndGame::handleUserEvent(const std::vector<std::shared_ptr<IUserEvent>> &userEvents)
{
    _nextLoopInterface = InterfaceManager::Interface::EndGame;
    return _nextLoopInterface;
}

void EndGame::setScoreEndGame(const std::string &endScoreGame)
{
    std::wstring test = ClientUtils::convertStringInToWtring(endScoreGame);
    _texts.push_back(std::shared_ptr<Text>(new Text(ClientProperties::_directPath + "/rsrc/font/SEASRN__.ttf", test, {700, 400}, 50, _defaultTextColor)));
}