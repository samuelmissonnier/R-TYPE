/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** SFMLEngine.hpp
*/

#ifndef SFML_ENGINE_HPP_
#define SFML_ENGINE_HPP_

#include "../GraphicsEngine.hpp"
#include "SFML/Window.hpp"
#include <SFML/Audio.hpp>
#include "../../Entity/Form/Form.hpp"
#include "../../Entity/Sprite/Sprite.hpp"
#include "../../Entity/Text/Text.hpp"
#include "../../Entity/Sound/Sound.hpp"
#include "../../UserEvent/KeyboardEvent/KeyboardEvent.hpp"
#include "../../UserEvent/MouseEvent/MouseEvent.hpp"
#include "../../UserEvent/ScreenEvent/ScreenEvent.hpp"
#include "../../UserEvent/TextEvent/TextEvent.hpp"

class SFMLGraphics : public AGraphics {
public:
    SFMLGraphics(void);
    ~SFMLGraphics(void);

    virtual void display(const Entities &entity);

    void display(IEntity *entity);
    void display(Form *entity);
    void display(Square *entity);
    void display(Circle *entity);
    void display(Text *entity);
    void display(ASprite *entity);
    void display(Sound *entity);

    virtual bool isWindowOpen(void) const noexcept;

    virtual void closeWindow(void);

    /*
    ** Event Manager
    */
    virtual const std::vector<std::shared_ptr<IUserEvent>> &getUserEvent(void);

    virtual Position getMousePos(void) const noexcept;

private:
    static KeyboardEvent::Add createAdd(sf::Event::KeyEvent keyEvent) noexcept;

    static sf::Color getColor(const RGBAColor &test) noexcept;

private:
    sf::RenderWindow _window;
    sf::RectangleShape _rect;
    sf::CircleShape _circle;
    sf::Text _text;
    std::map<std::string, std::pair<sf::Texture, sf::Sprite>> _sprites;
    std::map<std::string, sf::Font> _font;
    std::map<std::string, std::pair<sf::SoundBuffer, sf::Sound>> _sounds;
};

#endif /* SFML_ENGINE_HPP_ */
