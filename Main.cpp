#include <SFML/Graphics.hpp>
#include <iostream>
#include "Number.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 400), "Testing Number System", sf::Style::Close);

    sf::Sprite Digits;
    Score num;

    sf::Clock clock;
    sf::Time deltaTime;

    while(window.isOpen())
    {
        
        deltaTime = clock.getElapsedTime();
        sf::Event evnt;
        while(window.pollEvent(evnt))
        {
            if(evnt.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        num.update(deltaTime);
        Digits.setTexture(num.currentScore);
        
        std::cout << "Time:- "<< int (deltaTime.asSeconds()) << std::endl;
        
        window.clear(sf::Color::White);
        window.draw(Digits);
        window.display();
    }
    return 0;
}