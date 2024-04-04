#include <SFML/Graphics.hpp>

class AnimateMove
{
public:
    AnimateMove(sf::Texture &text, float height, float speed);
    void update(float deltaTime, bool state);
    void Draw(sf::RenderWindow &window);
    bool state;

private:
    float time;
    sf::RectangleShape first, second;
    sf::Vector2f movement;
    sf::Vector2f size;
    float height;
    float firstX;
    float secondX;

private:
    void Move();
};

AnimateMove::AnimateMove(sf::Texture &text, float height, float speed)
{
    this->state = state;
    this->height = height;
    first.setTexture(&text);
    second.setTexture(&text);

    size.x = text.getSize().x;
    size.y = text.getSize().y;

    first.setSize(sf::Vector2f(size.x, size.y));
    second.setSize(sf::Vector2f(size.x, size.y));

    movement.x = speed;
    movement.y = 0;

    first.setPosition(0, height);
    second.setPosition(size.x, height);
}

void AnimateMove::Move()
{
    first.move((movement.x * time), 0);
    second.move((movement.x * time), 0);
}

void AnimateMove::update(float deltaTime , bool state)
{ 
    time = deltaTime;
    firstX = first.getPosition().x;
    secondX = second.getPosition().x;
    
    if (state)
    {
        if (firstX + size.x < 0)
        {
            first.setPosition(secondX + size.x, height);
        }
        else if (secondX + size.x < 0)
        {
            second.setPosition(firstX + size.x, height);
        }

        Move();
    }
}

void AnimateMove::Draw(sf::RenderWindow &window)
{
    window.draw(first);
    window.draw(second);
}