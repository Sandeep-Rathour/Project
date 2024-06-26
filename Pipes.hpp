#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>

class Pipes
{

public:
    Pipes(sf::Texture &texture, float speed);
    void update(float deltaTime, int randomPosition);
    void Draw(sf::RenderWindow &window);
    void reset();

public:

    sf::Sprite upperPipe, lowerPipe;
    sf::Sprite upperPipe2, lowerPipe2;

    sf::RectangleShape collide;
    sf::RectangleShape collide2;

private:
    int randomY2;
    int randomY;
    sf::Texture pipe;
    float pipeDistance = 180;
    float pipeDifference = 320 + 110;
    sf::Vector2f movement;
};

Pipes::Pipes(sf::Texture &texture, float speed)
{
    pipe = texture;
    randomY = -100;

    collide.setSize(sf::Vector2f( 16 , 110));
    collide.setFillColor(sf::Color::Transparent);
    // collide.setPosition( 800,  randomY + 160);
    collide.setOrigin( 8, 55);

    collide2.setSize(sf::Vector2f( 16 , 110));
    collide2.setFillColor(sf::Color::Transparent);
    // collide2.setPosition( 1000,  randomY + 160);
    collide2.setOrigin( 8, 55);

    upperPipe.setTexture(pipe);
    upperPipe.setPosition(800, randomY);
    upperPipe.setOrigin( 26, 160);

    lowerPipe.setTexture(texture);
    lowerPipe.setTextureRect(sf::IntRect(52, 0, -52, 320));
    lowerPipe.setOrigin( 26, 160);
    lowerPipe.setRotation(180);
    lowerPipe.setPosition(600, randomY + pipeDifference);

    upperPipe2.setPosition(1000, randomY);
    upperPipe2.setTexture(pipe);
    upperPipe2.setOrigin( 26, 160);

    lowerPipe2.setTexture(texture);
    lowerPipe2.setTextureRect(sf::IntRect(52, 0, -52, 320));
    lowerPipe2.setOrigin( 26, 160);
    lowerPipe2.setRotation(180);
    lowerPipe2.setPosition(800, randomY + pipeDifference);

    movement.x = speed;

    // height of pipe is 320 and width is 52
}

void Pipes::update(float deltaTime, int rd)
{
    collide.setPosition(upperPipe.getPosition().x + 26, upperPipe.getPosition().y + 215);
    collide2.setPosition(upperPipe2.getPosition().x + 26, upperPipe2.getPosition().y + 215);

    // std::cout<< "Position: " << upperPipe.getPosition().x << " "<< upperPipe.getPosition().y << std::endl;

    
    if (upperPipe.getPosition().x < -52)
    {
        randomY = (rd);
        upperPipe.setPosition(upperPipe2.getPosition().x + pipeDistance, randomY);
        lowerPipe.setPosition(upperPipe2.getPosition().x + pipeDistance, randomY + pipeDifference);
    }


    if (upperPipe2.getPosition().x < -52)
    {
        randomY = -abs(rd);
        upperPipe2.setPosition(upperPipe.getPosition().x + pipeDistance, randomY);
        lowerPipe2.setPosition(upperPipe.getPosition().x + pipeDistance, randomY + pipeDifference);
    }

    float mv = movement.x * deltaTime;

    upperPipe.move(mv, 0);
    lowerPipe.move(mv, 0);

    collide.move(mv, 0);
    collide2.move(mv, 0);

    upperPipe2.move(mv, 0);
    lowerPipe2.move(mv, 0);
    
}

void Pipes::Draw(sf::RenderWindow &window)
{
    window.draw(upperPipe);
    window.draw(lowerPipe);

    window.draw(upperPipe2);
    window.draw(lowerPipe2);
}

void Pipes::reset()
{
    upperPipe.setPosition(800, randomY);
    lowerPipe.setPosition(800, randomY + pipeDifference);

    upperPipe2.setPosition(1000, randomY);
    lowerPipe2.setPosition(1000, randomY + pipeDifference);
}