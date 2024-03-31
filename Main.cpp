#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 400), "Testing Number System", sf::Style::Close);

    sf::RectangleShape box(sf::Vector2f(100, 100));
    box.setPosition(0,0);
    box.setFillColor(sf::Color::Red);

    std::cout<<"hello"<<std::endl;

    while(window.isOpen())
    {
        sf::Event Evnt;
        if(window.pollEvent(Evnt) == sf::Event::Closed)
        {
            window.close();
        }

        window.clear();
        window.draw(box);
        window.display();
    }

    return 0;
}