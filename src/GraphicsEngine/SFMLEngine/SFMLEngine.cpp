/*
** EPITECH PROJECT, 2020
** R-Type
** File description:
** SFMLEngine.cpp
*/

#include "SFMLEngine.hpp"
#include <iostream>
#include "../../Properties/ClientProperties.hpp"

SFMLGraphics::SFMLGraphics(void) :
    _window(sf::VideoMode(ClientProperties::_screenSize.first, ClientProperties::_screenSize.second), "R-Type",
            sf::Style::Titlebar | sf::Style::Close)
{}

SFMLGraphics::~SFMLGraphics(void)
{
    if (_window.isOpen())
        _window.close();
}

void SFMLGraphics::display(const Entities &entity)
{
    _window.clear();
    for (auto it : entity)
        display(it);
    _window.display();
}

void SFMLGraphics::display(IEntity *entity)
{
    switch (entity->getType()) {
    case IEntity::EntityType::Form:
        display(dynamic_cast<Form *>(entity));
        break;
    case IEntity::EntityType::Text:
        display(dynamic_cast<Text *>(entity));
        break;
    case IEntity::EntityType::Sprite:
        display(dynamic_cast<ASprite *>(entity));
        break;
    case IEntity::EntityType::Sound:
        display(dynamic_cast<Sound *>(entity));
        break;
    }
}

void SFMLGraphics::display(Form *form)
{
    switch (form->getFormType()) {
    case Form::FormType::Square:
        display(dynamic_cast<Square *>(form));
        break;
    case Form::FormType::Circle:
        display(dynamic_cast<Circle *>(form));
        break;
    default:
        std::cerr << "Undefined Form Type" << std::endl;
        break;
    }
}

sf::Color SFMLGraphics::getColor(const RGBAColor &color) noexcept
{
    return sf::Color(std::get<0>(color), std::get<1>(color), std::get<2>(color), std::get<3>(color));
}

void SFMLGraphics::display(Square *entity)
{
    _rect.setOrigin(-entity->getPosition().first, -entity->getPosition().second);
    _rect.setSize(sf::Vector2f(entity->getSize().first * entity->getScale().first, entity->getSize().second * entity->getScale().second));
    // _rect.setScale(entity->getScale().first, entity->getScale().second);
    _rect.setFillColor(getColor(entity->getColor()));
    _window.draw(_rect);
}

void SFMLGraphics::display(Circle *entity)
{
    _circle.setOrigin(-entity->getPosition().first, -entity->getPosition().second);
    _circle.setRadius(entity->getRad());
    _circle.setScale(entity->getScale().first, entity->getScale().second);
    _circle.setFillColor(getColor(entity->getColor()));
    _window.draw(_circle);
}

void SFMLGraphics::display(Text *entity)
{
    if (_font.find(entity->getFilepath()) == _font.end()) {
        sf::Font &font = _font[entity->getFilepath()];
        if (!font.loadFromFile(entity->getFilepath()))
            return;
    }
    _text.setOrigin(-entity->getPosition().first, -entity->getPosition().second);
    _text.setFont(_font[entity->getFilepath()]);
    _text.setString(entity->getText());
    _text.setScale(entity->getScale().first, entity->getScale().second);
    _text.setCharacterSize(entity->getSize());
    _text.setFillColor(getColor(entity->getColor()));
    _window.draw(_text);
}

void SFMLGraphics::display(Sound *entity)
{
    if (_sounds.find(entity->getFilepath()) == _sounds.end()) {
        sf::SoundBuffer &soundBuffer = _sounds[entity->getFilepath()].first;
        if (!soundBuffer.loadFromFile(entity->getFilepath()))
            return;
        sf::Sound &sound = _sounds[entity->getFilepath()].second;
        sound.setBuffer(_sounds[entity->getFilepath()].first);
        sound.setLoop(entity->isLooping());
        sound.setVolume(ClientProperties::_volume * 100);
        sound.play();
    }
}

void SFMLGraphics::display(ASprite *entity)
{
    if (_sprites.find(entity->getFilepath()) == _sprites.end()) {
        std::pair<sf::Texture, sf::Sprite> &pair = _sprites[entity->getFilepath()];
        if (!pair.first.loadFromFile(entity->getFilepath()))
            return;
        pair.second.setTexture(pair.first);
        pair.second.setOrigin(-entity->getPosition().first, -entity->getPosition().second);
    }
    sf::Sprite &sprite = _sprites[entity->getFilepath()].second;
    sprite.setOrigin(-entity->getPosition().first, -entity->getPosition().second);
    sprite.setScale(entity->getScale().first, entity->getScale().second);
    sprite.setTextureRect(sf::IntRect(entity->getRect().first.first, entity->getRect().first.second, entity->getRect().second.first, entity->getRect().second.second));
    _window.draw(sprite);
}

bool SFMLGraphics::isWindowOpen(void) const noexcept
{
    return _window.isOpen();
}


void SFMLGraphics::closeWindow(void)
{
    _window.close();
}

Position SFMLGraphics::getMousePos(void) const noexcept
{
    sf::Vector2i v = sf::Mouse::getPosition(_window);

    return Position(v.x, v.y);
}

const std::vector<std::shared_ptr<IUserEvent>> &SFMLGraphics::getUserEvent(void)
{
    sf::Event event;
    _userEvents.clear();

    while (_window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::EventType::Closed:
            _window.close();
            break;
        case sf::Event::EventType::Resized:
            ClientProperties::_screenSize = {_window.getSize().x, _window.getSize().y};
            break;

            /*
            **  Screen Event
            */
        case sf::Event::EventType::LostFocus:
            _userEvents.push_back(std::shared_ptr<IUserEvent>(new ScreenEvent(ScreenEvent::ScreenEventType::LOST_FOCUS)));
            break;
        case sf::Event::EventType::GainedFocus:
            _userEvents.push_back(std::shared_ptr<IUserEvent>(new ScreenEvent(ScreenEvent::ScreenEventType::GAIN_FOCUS)));
            break;
        case sf::Event::EventType::MouseLeft:
            _userEvents.push_back(std::shared_ptr<IUserEvent>(new ScreenEvent(ScreenEvent::ScreenEventType::MOUSE_LEFT)));
            break;
        case sf::Event::EventType::MouseEntered:
            _userEvents.push_back(std::shared_ptr<IUserEvent>(new ScreenEvent(ScreenEvent::ScreenEventType::MOUSE_ENTERED)));
            break;

            /*
            ** Keyboard Event
            */
        case sf::Event::EventType::KeyPressed:
            _userEvents.push_back(std::shared_ptr<IUserEvent>(new KeyboardEvent(StateEvent::EventState::PRESSED,
static_cast<KeyboardInput>(event.key.code), createAdd(event.key))));
            break;
        case sf::Event::EventType::KeyReleased:
            _userEvents.push_back(std::shared_ptr<IUserEvent>(new KeyboardEvent(StateEvent::EventState::RELEASED,
static_cast<KeyboardInput>(event.key.code), createAdd(event.key))));
            break;
        case sf::Event::EventType::TextEntered:
            _userEvents.push_back(std::shared_ptr<IUserEvent>(new TextEvent(event.text.unicode)));
            break;

            /*
            ** Mouse Event
            */
        case sf::Event::EventType::MouseButtonPressed:
            _userEvents.push_back(std::shared_ptr<IUserEvent>(new MouseEvent(static_cast<MouseEvent::MouseButtonType>(event.mouseButton.button), StateEvent::EventState::PRESSED)));
            break;
        case sf::Event::EventType::MouseButtonReleased:
            _userEvents.push_back(std::shared_ptr<IUserEvent>(new MouseEvent(static_cast<MouseEvent::MouseButtonType>(event.mouseButton.button), StateEvent::EventState::RELEASED)));
            break;
        case sf::Event::EventType::MouseWheelMoved:
            // _userEvents.push_back(UserEvent(IUserEvent::EventType::MouseWheel));
            break;
        case sf::Event::EventType::MouseWheelScrolled:
            break;
        case sf::Event::EventType::MouseMoved:
            // _userEvents.push_back(UserEvent(IUserEvent::EventType::MouseMove));
            break;
        default:
            std::cerr << "Some events were vanished" << std::endl;
            break;
        }
    }
    return _userEvents;
}

KeyboardEvent::Add SFMLGraphics::createAdd(sf::Event::KeyEvent key) noexcept
{
    size_t add = 0;
    if (key.alt)
        add |= KeyboardEvent::Add::ALT;
    if (key.control)
        add |= KeyboardEvent::Add::CTRL;
    if (key.shift)
        add |= KeyboardEvent::Add::SHIFT;
    if (key.system)
        add |= KeyboardEvent::Add::SYS;
    return static_cast<KeyboardEvent::Add>(add);
}
