#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>          //Random Number Generation
#include "Number.hpp"      //Representing Scores
#include "AnimateMove.hpp" //Moving Images Backward Repeatedly. Mainly Ground and BackGround;
#include "Bird.hpp"        //For our Flappy
#include "Pipes.hpp"       //Pipes Rendered and Moved
#include "Play.hpp"        //For Play Button

/// Using enum class named GameState
/// To change States of game based on Gameplay
///
enum class GameState
{
    Menu,
    Ready,
    Game,
    Pause,
};

/// Main Function
int main()
{

/// Built in SFML library, RenderWindow to create a new Window
///
    sf::RenderWindow window(sf::VideoMode(288, 512), "Testing Number System", sf::Style::Close);

/// using Random Fuction for Pipes
///
    std::random_device seed;
    std::uniform_int_distribution<int> randomNumber(-280, -60);

/// All Textures are Created Here
///
    sf::Texture greenPipe; // texture of a Single Pipe
    greenPipe.loadFromFile("Sprites/GreenPipe.png");

    sf::Texture flappyTexture; // texture of Sprite-Sheet of Bird
    flappyTexture.loadFromFile("Sprites/BlueBird.png");

    sf::Texture daySky; // Texture of Day Sky Background
    daySky.loadFromFile("Sprites/NightSky.png");

    sf::Texture bottom; // Texture of Ground
    bottom.loadFromFile("Sprites/Ground.png");

    sf::Texture playButton;
    playButton.loadFromFile("Sprites/Play.png");

/// Variables for Game
///
    int PipeGroundSpeed = -120;
    bool isGame = true;
    sf::Sprite Digits;
    Digits.setPosition(sf::Vector2f(144, 20));

/// Most Constructor's are called here
///
    Play button(playButton);
    Score num; // Score class take score in update Function

    AnimateMove ground(bottom, 400, PipeGroundSpeed); // Ground
    AnimateMove backGround(daySky, 0, -60);           // Background

    Pipes green(greenPipe, PipeGroundSpeed); // Pipes (both upper and lower)
    Bird flappy(flappyTexture, 27);          // Flappy Bird

    /// Using SFML Clock so that Objects will move acording to time,
    /// which will result in moving objects at same speed in all Computers
    ///
    sf::Clock clock;
    float deltaTime; // Storing clock time as Seconds in deltaTime

    sf::Clock tt;

    GameState gameState = GameState::Menu;

    while (window.isOpen())
    {
        float ft = tt.getElapsedTime().asSeconds();
        /// Time from last reset is Stored and then Clock is restarted
        deltaTime = clock.restart().asSeconds();

        /// if out Time goes more than we need, we set it manually
        if (deltaTime > 1.0f / 20.0f)
        {
            deltaTime = 1.0f / 20.0f;
        }

        

        /// Using evnt to Close window and Minimize it
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            if (evnt.type == sf::Event::Closed)
            {
                window.close(); // Closing Fuction
            }

            if (evnt.type == sf::Event::KeyPressed)
            {
                if (evnt.key.code == sf::Keyboard::Space && gameState == GameState::Menu)
                {
                    gameState = GameState::Game;
                }
                else if (evnt.key.code == sf::Keyboard::Escape && gameState == GameState::Game )
                {
                    gameState = GameState::Pause;
                }
                else if (evnt.key.code == sf::Keyboard::Space && gameState == GameState::Pause )
                {
                    gameState = GameState::Game;
                }
            }
        }

        // std::cout << "Time: "<< double (deltaTime) << std::endl;

        // std::cout<< randomNumber(seed) << std::endl;

        /// Clear Function Clear's the RenderWindow
        /// if not Cleared it will not Work Prperly
        ///
        window.clear(sf::Color::White);

        switch (gameState)
        {
        case GameState::Menu:
            
            if(button.isMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                gameState = GameState::Game;
            }
            backGround.Draw(window);
            window.draw(button.play);
            ground.Draw(window);
            window.draw(flappy.bird);

            break;

        case GameState::Game:

            if (flappy.isCollide == true)
            {
                isGame = false;
            }
            isGame = true;

            num.update(ft);
            Digits.setTexture(num.currentScore);

            flappy.update(deltaTime, isGame);
            green.update(deltaTime, randomNumber(seed), isGame);
            backGround.update(deltaTime, isGame);
            ground.update(deltaTime, isGame);

            backGround.Draw(window);
            green.Draw(window);
            ground.Draw(window);
            window.draw(flappy.bird);

            break;

        case GameState::Pause:
            isGame = false;

            flappy.update(deltaTime, isGame);
            green.update(deltaTime, randomNumber(seed), isGame);
            backGround.update(deltaTime, isGame);
            ground.update(deltaTime, isGame);

            backGround.Draw(window);
            green.Draw(window);
            ground.Draw(window);
            window.draw(flappy.bird);

            break;
        }

        // window.draw(Digits);

        /// Display Fuction is Used to Display Everything on RenderWindow
        ///
        window.display();
    }

    return 0;
}