#include <SFML/Graphics.hpp>

class AnimateMove
{
public:
    AnimateMove(sf::Texture &text, float height, float speed);
    void update(float deltaTime);
    void Draw(sf::RenderWindow &window);
    bool state;

    sf::RectangleShape first, second;
private:
    float time;
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

    second.setSize(sf::Vector2f(size.x, size.y));
    first.setSize(sf::Vector2f(size.x, size.y));

    second.setOrigin(second.getSize().x / 2, second.getSize().y / 2);
    first.setOrigin(first.getSize().x / 2, first.getSize().y / 2);

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

void AnimateMove::update(float deltaTime)
{ 
    time = deltaTime;
    firstX = first.getPosition().x;
    secondX = second.getPosition().x;

    if (firstX + size.x < 144)
    {
        first.setPosition(secondX + size.x, height);
    }
    else if (secondX + size.x < 144)
    {
        second.setPosition(firstX + size.x, height);
    }

    Move();
}

void AnimateMove::Draw(sf::RenderWindow &window)
{
    window.draw(first);
    window.draw(second);
}