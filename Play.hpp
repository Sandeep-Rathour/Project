#include <SFML/Graphics.hpp>
#include <iostream>

class Play
{

public:
    Play(sf::Texture & texture);
    // void update();
    bool isMouseOver(sf::RenderWindow & window);
    void reset();

    sf::Sprite play;

private:
    sf::Vector2i mouse;
    sf::Vector2f position;
};

Play::Play(sf::Texture & texture)
{   
    play.setTexture(texture);
    play.setPosition(sf::Vector2f( 144, 350));
    play.setOrigin( texture.getSize().x / 2, texture.getSize().y / 2 );
    
    position.x = play.getLocalBounds().width;
    position.y = play.getLocalBounds().height;
}

bool Play::isMouseOver(sf::RenderWindow & window)
{
    sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    return play.getGlobalBounds().contains(mouse);
}

void Play::reset()
{
    play.setPosition(144, 350);
}