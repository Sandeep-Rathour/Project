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
    GameOver,
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
    std::uniform_int_distribution<int> randomNumber(-110, 110);

    /// All Textures are Created Here
    ///
    sf::Texture gameMsg;
    gameMsg.loadFromFile("Sprites/Ready.png");

    sf::Texture tapImg;
    tapImg.loadFromFile("Sprites/ReadyTap.png");

    sf::Texture greenPipe; // texture of a Single Pipe
    greenPipe.loadFromFile("Sprites/GreenPipe.png");

    sf::Texture flappyTexture; // texture of Sprite-Sheet of Bird
    flappyTexture.loadFromFile("Sprites/BlueBird.png");

    sf::Texture daySky; // Texture of Day Sky Background
    daySky.loadFromFile("Sprites/DaySky.png");

    sf::Texture bottom; // Texture of Ground
    bottom.loadFromFile("Sprites/Ground.png");

    sf::Texture playButton;
    playButton.loadFromFile("Sprites/Play.png");

    /// Variables for Game
    ///
    int currentScore;
    bool isScore = true;

    int PipeGroundSpeed = -120;
    // bool isGame = true;
    sf::Sprite Digits;
    Digits.setPosition(sf::Vector2f(118, 20));

    sf::Sprite getReady(gameMsg);
    sf::Sprite gameOver(gameMsg);

    getReady.setTextureRect(sf::IntRect(0, 0, 192, 50));
    gameOver.setTextureRect(sf::IntRect(192, 0, 192, 50));

    getReady.setPosition(sf::Vector2f(48.5, 100));
    gameOver.setPosition(sf::Vector2f(48.5, 100));

    sf::Sprite tap(tapImg);
    tap.setScale(1.2, 1.2);
    tap.setPosition(sf::Vector2f((288 - tap.getGlobalBounds().width), 300));
    tap.setOrigin(tap.getGlobalBounds().width / 2, tap.getGlobalBounds().height / 2);

    /// Most Constructor's are called here
    ///

    Play button(playButton);
    Score num; // Score class take score in update Function

    AnimateMove ground(bottom, 456, PipeGroundSpeed); // Ground
    AnimateMove backGround(daySky, 256, -60);         // Background

    Pipes green(greenPipe, PipeGroundSpeed); // Pipes (both upper and lower)
    Bird flappy(&flappyTexture, 27);          // Flappy Bird

    /// Using SFML Clock so that Objects will move acording to time,
    /// which will result in moving objects at same speed in all Computers
    ///
    sf::Clock clock;
    float deltaTime; // Storing clock time as Seconds in deltaTime

    GameState gameState = GameState::Menu;

    while (window.isOpen())
    {
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

            if (evnt.type == sf::Event::KeyPressed || evnt.type == sf::Event::MouseButtonPressed)
            {
                if (evnt.key.code == sf::Keyboard::Space && gameState == GameState::Menu)
                {
                    gameState = GameState::Ready;
                }
                else if (((evnt.type == sf::Event::MouseButtonPressed && evnt.mouseButton.button == sf::Mouse::Left)) && gameState == GameState::Ready)
                {
                    gameState = GameState::Game;
                }
                else if (evnt.key.code == sf::Keyboard::Escape && gameState == GameState::Ready)
                {
                    gameState = GameState::Menu;
                }
                else if (evnt.key.code == sf::Keyboard::Escape && gameState == GameState::Game)
                {
                    gameState = GameState::Pause;
                }
                else if ((evnt.type == sf::Event::MouseButtonPressed && evnt.mouseButton.button == sf::Mouse::Left) && gameState == GameState::Pause)
                {
                    gameState = GameState::Game;
                }
            }
        }

        /// Clear Function Clear's the RenderWindow
        /// if not Cleared it will not Work Prperly
        ///
        window.clear(sf::Color::White);

        switch (gameState)
        {
        case GameState::Menu:

            button.reset();

            if (button.isMouseOver(window) && evnt.type == sf::Event::MouseButtonPressed && evnt.mouseButton.button == sf::Mouse::Left)
            {
                button.play.move( 0, 5);
            }
            if (button.isMouseOver(window) && evnt.type == sf::Event::MouseButtonReleased && evnt.mouseButton.button == sf::Mouse::Left)
            {
                green.reset();
                gameState = GameState::Ready;
                
            }

            flappy.reset();


            // flappy.updateAnimation(deltaTime);

            backGround.Draw(window);
            green.Draw(window);
            ground.Draw(window);
            window.draw(flappy.bird);
            window.draw(getReady);
            window.draw(button.play);

            break;

        case GameState::Ready:


            

            flappy.reset();
            currentScore = 0;
            backGround.Draw(window);
            green.Draw(window);
            ground.Draw(window);
            window.draw(flappy.bird);
            window.draw(getReady);
            window.draw(tap);
            // window.draw(getReady);
            // window.draw(button.play);

            break;

        case GameState::Game:

            // flappy.bird.setTextureRect(flappy.wings.uvRect);
            flappy.updateAnimation(deltaTime);
            flappy.update(deltaTime);
            green.update(deltaTime, randomNumber(seed));
            backGround.update(deltaTime);
            ground.update(deltaTime);

            if ((flappy.checkCollision(green.collide) || flappy.checkCollision(green.collide2)) && isScore)
            {
                currentScore += 1;
                isScore = false;
            }
            else if (!isScore && !flappy.checkCollision(green.collide) & !flappy.checkCollision(green.collide2))
            {
                isScore = true;
            }
            if (flappy.checkCollision(green.upperPipe) || flappy.checkCollision(green.lowerPipe))
            {
                gameState = GameState::GameOver;
            }
            else if (flappy.checkCollision(green.lowerPipe2) || flappy.checkCollision(green.upperPipe2))
            {
                gameState = GameState::GameOver;
            }
            else if (flappy.checkCollision(ground.first) || flappy.checkCollision(ground.second))
            {
                gameState = GameState::GameOver;
            }

            num.update(currentScore);
            Digits.setTexture(num.currentScore);
            backGround.Draw(window); // 1
            green.Draw(window);      // 2
            window.draw(green.collide);
            window.draw(green.collide2);
            ground.Draw(window);      // 3
            window.draw(flappy.bird); // 4
            window.draw(Digits);

            break;

        case GameState::Pause:

            // flappy.update(deltaTime, isGame);
            // green.update(deltaTime, randomNumber(seed), isGame);
            // backGround.update(deltaTime, isGame);
            // ground.update(deltaTime, isGame);

            backGround.Draw(window);
            green.Draw(window);
            window.draw(green.collide);
            window.draw(green.collide2);
            ground.Draw(window);
            window.draw(tap);
            window.draw(flappy.bird);

            break;

        case GameState::GameOver:

            if (button.isMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                green.reset();
                gameState = GameState::Ready;
            }

            backGround.Draw(window);
            green.Draw(window);
            window.draw(green.collide);
            window.draw(green.collide2);
            ground.Draw(window);
            window.draw(flappy.bird);
            window.draw(button.play);
            window.draw(gameOver);
            window.draw(Digits);

            break;
        }
        // window.draw(Digits);

        /// Display Fuction is Used to Display Everything on RenderWindow
        ///
        window.display();
    }

    return 0;
}