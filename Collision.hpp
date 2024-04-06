#include <SFML/Graphics.hpp>

class Collision
{

public:
    Collision();
    bool checkCollision(const sf::Sprite & body, const sf::Sprite & body2 );
    bool checkCollision(const sf::Sprite & body, const sf::RectangleShape & body2 );

private:
    float deltaX, deltaY;
    float intersectX, intersectY;
    sf::Vector2f thisPosition,otherPosition ;
    sf::Vector2u thisHalfSize, otherHalfSize;

};

Collision::Collision()
{
    
}


bool Collision::checkCollision(const sf::Sprite & body,const  sf::Sprite & body2)
{
    thisPosition = body.getPosition();
    thisHalfSize.x = (body.getGlobalBounds().width / 2.0f);
    thisHalfSize.y = (body.getGlobalBounds().height / 2.0f);

    otherPosition = body2.getPosition();
    otherHalfSize.x = (body2.getGlobalBounds().width / 2.0f);
    otherHalfSize.y = (body2.getGlobalBounds().height / 2.0f);

    deltaX = otherPosition.x - thisPosition.x;
    deltaY = otherPosition.y - thisPosition.y;

    intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    return (intersectX < -3.0f && intersectY < -3.0f);   
}

bool Collision::checkCollision(const sf::Sprite & body, const sf::RectangleShape & body2)
{
    thisPosition = body.getPosition();
    thisHalfSize.x = (body.getGlobalBounds().width / 2.0f);
    thisHalfSize.y = (body.getGlobalBounds().height / 2.0f);

    otherPosition = body2.getPosition();
    otherHalfSize.x = (body2.getSize().x / 2.0f);
    otherHalfSize.y = (body2.getSize().y / 2.0f);

    deltaX = otherPosition.x - thisPosition.x;
    deltaY = otherPosition.y - thisPosition.y;

    intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    return (intersectX < 0.0f && intersectY < 0.0f);   
}

