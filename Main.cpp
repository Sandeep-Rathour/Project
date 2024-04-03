#include <SFML/Graphics.hpp>
#include <iostream>
#include <random> //Random Number Generation 
#include "Number.hpp" //Representing Scores
#include "AnimateMove.hpp" //Moving Images Backward Repeatedly. Mainly Ground and BackGround;
#include "Bird.hpp" //For our Flappy
#include "Pipes.hpp" //Pipes Rendered and Moved

enum class GameState
{
    Menu,
    Game,
};

//Main Function
int main()
{
    
    sf::RenderWindow window(sf::VideoMode(288, 512), "Testing Number System", sf::Style::Close);

    

    bool runGame = true;
    sf::Sprite Digits;
    Score num;
    
    std::random_device seed;
    std::uniform_int_distribution <int> randomNumber( -280, -60);

    sf::Texture bothPipes;
    bothPipes.loadFromFile("Sprites/GreenPipe.png");

    sf::Texture flappyTexture;
    flappyTexture.loadFromFile("Sprites/BlueBird.png");

    sf::Texture daySky;
    daySky.loadFromFile("Sprites/NightSky.png");
    // Background.setTexture(daySky);

    sf::Texture bottom;
    bottom.loadFromFile("Sprites/Ground.png");

    int PipeGroundSpeed = -120;

    Pipes green(bothPipes, PipeGroundSpeed);
    Bird flappy(flappyTexture, 27, runGame);
    AnimateMove ground(bottom, 400, PipeGroundSpeed, runGame);
    AnimateMove backGround(daySky, 0, -60, 1);

    sf::Clock clock;
    float deltaTime;

    sf::Clock tt;

    while(window.isOpen())
    {
        float ft = tt.getElapsedTime().asSeconds();
        
        // sf::Time dt = clock.restart();
        // deltaTime = dt.asSeconds();
        deltaTime = clock.restart().asSeconds();


        if(deltaTime > 1.0f / 20.0f)
        {
            deltaTime = 1.0f / 20.0f;
        }

        sf::Event evnt;
        while(window.pollEvent(evnt))
        {
            if(evnt.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        
        
        if(flappy.isCollide == true)
        {
            runGame = false;
        }
        num.update(ft);
        Digits.setTexture(num.currentScore);
        
        // std::cout << "Time: "<< double (deltaTime) << std::endl;

        flappy.update(deltaTime);
        green.update(deltaTime, randomNumber(seed));
        backGround.update(deltaTime);
        ground.update(deltaTime);
        
    // std::cout<< randomNumber(seed) << std::endl;

        window.clear(sf::Color::White);        

        backGround.Draw(window);

        green.Draw(window);
        ground.Draw(window);

        window.draw(flappy.bird);
        // window.draw(Digits);

        window.display();

    }

    return 0;
}