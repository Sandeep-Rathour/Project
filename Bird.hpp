#include <SFML/Graphics.hpp>
#include <math.h>

class Bird
{

public:
    Bird(sf::Texture &texture, float jumpHeight);
    void update(float deltaTime);
    void reset();
    bool checkCollision(const sf::RectangleShape & otherBody);
    bool checkCollision(const sf::Sprite & otherSprite);

public:
    sf::Sprite bird;

private:
    sf::RectangleShape otherBody;
    sf::Sprite otherSprite;
    sf::Vector2f velocity;
    float jumpHeight;
    float gravity;


    ///Variable for Collision checking
    float deltaX, deltaY;
    float intersectX, intersectY;
    sf::Vector2f thisPosition, otherPosition;
    sf::Vector2f thisHalfSize, otherHalfSize;
};

void Bird::reset()
{
    bird.setPosition(sf::Vector2f(55, 180));
    velocity.y = 0;
}

Bird::Bird(sf::Texture &texture, float jumpHeight)
{
    gravity = 981.0f;
    velocity.y = 0;
    
    this->jumpHeight = jumpHeight;
    
    bird.setTexture(texture);
    bird.setPosition(sf::Vector2f(55, 180));
    bird.setOrigin( texture.getSize().x / 2, (texture.getSize().y / 4) / 2 );
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
    else
    {
        velocity.y = velocity.y + gravity * deltaTime;
    }

    bird.move(velocity.x, velocity.y * deltaTime);

    if(bird.getPosition().y < 0)
    {
        bird.setPosition( 55, 0);
    }
  
}

bool Bird::checkCollision(const sf::RectangleShape & otherBody)
{
    this->otherBody = otherBody;
    thisPosition = bird.getPosition();
    thisHalfSize.x = bird.getGlobalBounds().getSize().x / 2.0f;
    thisHalfSize.y = bird.getGlobalBounds().getSize().y / 2.0f;

    otherPosition = otherBody.getPosition();
    otherHalfSize.x = otherBody.getGlobalBounds().getSize().x / 2.0f;
    otherHalfSize.y = otherBody.getGlobalBounds().getSize().y / 2.0f;

    deltaX = thisPosition.x - otherPosition.x;
    deltaY = thisPosition.y - otherPosition.y;

    intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    if(intersectX < -2.0f && intersectY < -2.0f)
    {
        return true;
    }
    else
    {
        return false;
    }

}

bool Bird::checkCollision(const sf::Sprite & otherSprite)
{
    this->otherSprite = otherSprite;
    thisPosition = bird.getPosition();
    thisHalfSize.x = bird.getGlobalBounds().getSize().x / 2.0f;
    thisHalfSize.y = bird.getGlobalBounds().getSize().y / 2.0f;

    otherPosition = otherSprite.getPosition();
    otherHalfSize.x = otherSprite.getGlobalBounds().getSize().x / 2.0f;
    otherHalfSize.y = otherSprite.getGlobalBounds().getSize().y / 2.0f;

    deltaX = thisPosition.x - otherPosition.x;
    deltaY = thisPosition.y - otherPosition.y;

    intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    std::cout<< "Intersect Sprite " << intersectX << " "<< intersectY << std::endl;

    if(intersectX < -2.0f && intersectY < -2.0f)
    {
        return true;
    }
    else
    {
        return false;
    }

}