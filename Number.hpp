#include <SFML/Graphics.hpp>

class Score
{
public:
    Score(void);
    void update(float time);

public:
    sf::Texture currentScore;

private:
    sf::IntRect uvRect;
    sf::Texture texture;
    sf::Sprite num1, num2;
    int score;
    int lastDigit;
    float scale = 1.0;
    sf::RenderTexture renderTexture;
};

Score::Score(void)
{
    texture.loadFromFile("Sprites/Numbers.png");
    num1.setTexture(texture);

    uvRect.width = texture.getSize().x / 10;
    uvRect.height = texture.getSize().y;
    uvRect.top = 0;

    num1.setScale(scale, scale);
    num2.setScale(scale, scale);

    num1.setTexture(texture);
    num2.setTexture(texture);

    
    num2.setPosition(0, 0);
}

void Score::update(float time)
{

    // score = int(time.asMilliseconds());
    score = time;

    renderTexture.create(52 * scale, 38 * scale);
    renderTexture.clear(sf::Color::Transparent);

    lastDigit = score % 10;
    uvRect.left = uvRect.width * lastDigit;

    num1.setTextureRect(uvRect);

    lastDigit = (score / 10) % 10;

    if(lastDigit != 0 )
    {
        uvRect.left = uvRect.width * lastDigit;
        num2.setTextureRect(uvRect);
        renderTexture.draw(num2);
        num1.setPosition(33, 0);
    }
    else{
        num1.setPosition(33, 0);
    }

    renderTexture.draw(num1);

    renderTexture.display();

    currentScore = renderTexture.getTexture();
}
