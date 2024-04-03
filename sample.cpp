#include <SFML/Graphics.hpp>
#include <iostream>

enum class GameState
{
    Loading,
    Menu,
    Game,
    Pause
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Flappy Bird");

    GameState gameState = GameState::Loading;

    // Game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space && gameState == GameState::Menu)
                {
                    // Start the game
                    gameState = GameState::Game;
                }
                else if (event.key.code == sf::Keyboard::Escape && gameState == GameState::Game)
                {
                    // Pause the game
                    gameState = GameState::Pause;
                }
            }
        }

        window.clear();

        switch (gameState)
        {
            case GameState::Loading:
                // Display loading screen
                // Load game assets
                // Transition to Menu state when loading is complete
                gameState = GameState::Menu;
                break;

            case GameState::Menu:
                // Display menu with play button
                // Clicking play button will start the game
                window.draw(/* Menu elements */);
                break;

            case GameState::Game:
                // Game logic and rendering
                window.draw(/* Game elements */);
                break;

            case GameState::Pause:
                // Display pause menu
                // Resume game or go back to menu
                window.draw(/* Pause menu elements */);
                break;
        }

        window.display();
    }

    return 0;
}
