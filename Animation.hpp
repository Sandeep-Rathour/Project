#include <SFML/Graphics.hpp>

class Animate
{
public:
    Animate(sf::Texture *texture, sf::Vector2u imageCount, float switchTime);
    void update(float deltaTime);

public:
    sf::IntRect uvRect;

private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;

    float switchTime;
    float totalTime = 0.0f;
};

Animate::Animate(sf::Texture *texture, sf::Vector2u imageCount, float switchTime)
{
    this->imageCount = imageCount;
    this->switchTime = switchTime;

    totalTime = 0.0f;
    currentImage.x = 0;
    currentImage.y = 0;

    uvRect.width = texture -> getSize().x / imageCount.x;
    uvRect.height = texture -> getSize().y / imageCount.y;
    uvRect.left = uvRect.width * currentImage.x;
}

void Animate::update(float deltaTime)
{
    totalTime =  totalTime + deltaTime;

    if(totalTime >= switchTime)
    {
        totalTime = totalTime - switchTime;
        currentImage.y = currentImage.y + 1;

        if(currentImage.y >= imageCount.y)
        {
            currentImage.y = 0;
        }
    }

    uvRect.top = uvRect.height * currentImage.y;
    std::cout<< "UVRect " << deltaTime << " " << switchTime <<" " << totalTime <<std::endl;
}