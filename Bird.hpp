#include <SFML/Graphics.hpp>
#include <math.h>

class Bird
{

public:
    Bird(sf::Texture &texture, float jumpHeight);
    void update(float deltaTime);
    void reset();

public:
    sf::Sprite bird;

private:
    sf::Vector2f velocity;
    bool canJump = true;
    float jumpHeight;
    float gravity;
};

void Bird::reset()
{
    bird.setPosition(sf::Vector2f(55, 180));
}

Bird::Bird(sf::Texture &texture, float jumpHeight)
{
    gravity = 981.0f;
    velocity.y = 0;
    
    this->canJump = canJump;
    this->jumpHeight = jumpHeight;
    
    bird.setTexture(texture);
    bird.setPosition(sf::Vector2f(55, 180));
    bird.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y / 4));
}

void Bird::update(float deltaTime)
{
    if(velocity.y >= -30 && velocity.y <= 30)
    {
        velocity.y = 40;
    }

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left)))
    {
        velocity.y = -sqrt(2.0f * gravity * jumpHeight );
    }
    else if(canJump)
    {
        velocity.y = velocity.y + gravity * deltaTime;
    }

    if(canJump)
    {
        bird.move(velocity.x, velocity.y * deltaTime);
    }
    
    std::cout<< velocity.y <<std::endl;

    if(bird.getPosition().y < 0)
    {
        bird.setPosition( 55, 0);
    }
  
}
