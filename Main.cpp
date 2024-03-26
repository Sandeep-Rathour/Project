#include <iostream>
#include <SFML/Graphics.hpp>

void Gravity(sf::RectangleShape & body, float & weight);

int main()
{   
///Main Window
///Video Size is Determine By Hit and Trial Method
///Screen Aspect Ratio is Close to 9:16
    sf::RenderWindow window(sf::VideoMode(370, 650), "Flappy", sf::Style::Close);

///Game view 
    sf::View gameView(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(370, 650));   

///Creating Rectangle for Background
    sf::RectangleShape BackGround;
    BackGround.setSize(sf::Vector2f(370.0f, 650.0f));
    BackGround.setPosition(0,0);

///Creating a Sprite named Bird, Our Main Character
    sf::RectangleShape Bird;
    Bird.setSize(sf::Vector2f(30, 30));
    Bird.setFillColor(sf::Color::Red);
    Bird.setOrigin(Bird.getSize().x / 2.0f, Bird.getSize().y / 2.0f);
    Bird.setPosition(100, 250);
    

///Creating Texture for BackGround
///Using If statement for error Management
    sf::Texture DaySky;
    if(!DaySky.loadFromFile("./Sprites/DaySky.png"))
    {
        std::cout<<"loading"<<std::endl;
        return 1;
    }
    BackGround.setTexture(&DaySky);

///Main Game Loop
///While Window is Open it will work
    while(window.isOpen())
    {     
        sf::Event evnt;
        while(window.pollEvent(evnt))
        {
            if(evnt.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i mos = sf::Mouse::getPosition(window);
            Bird.setPosition((float)mos.x , (float)mos.y);
        }

    ///Clearing Screen
        window.clear(sf::Color::White);
    
    ///Setting View
        // window.setView(gameView);
    
    ///Drawing Objects on Screen
        window.draw(BackGround);
        window.draw(Bird);
        
    ///Displaying all Objects on Window
        window.display();

    }

    return 0;
}

void Gravity(sf::RectangleShape & body, float & weight)
{
    
}

