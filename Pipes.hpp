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
    int currentScore;
    int highScore;

    sf::Sprite upperPipe, lowerPipe;
    sf::Sprite upperPipe2, lowerPipe2;

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

    upperPipe.setTexture(pipe);
    lowerPipe.setTexture(texture);
    lowerPipe.setTextureRect(sf::IntRect(52, 0, -52, 320));

    lowerPipe.setOrigin(52, 320);
    lowerPipe.setRotation(180);

    upperPipe.setPosition(800, randomY);
    lowerPipe.setPosition(800, randomY + pipeDifference);

    upperPipe2.setTexture(pipe);
    lowerPipe2.setTexture(texture);
    lowerPipe2.setTextureRect(sf::IntRect(52, 0, -52, 320));

    lowerPipe2.setOrigin(52, 320);
    lowerPipe2.setRotation(180);

    movement.x = speed;

    upperPipe2.setPosition(1000, randomY);
    lowerPipe2.setPosition(1000, randomY + pipeDifference);
    // height of pipe is 320 and width is 52
}

void Pipes::update(float deltaTime, int rd)
{

    
        if (upperPipe.getPosition().x < -52)
        {
            randomY = -abs(rd);
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