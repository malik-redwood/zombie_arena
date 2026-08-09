// Contains the main function and the code that instantiates and controls all our classes.

#include <SFML/Graphics.hpp>
#include "Player.h"

int main()
{
        // Keeps track of and responds to the different states that the game can be in at any given time
        // The game will always be in one of four states
        enum class State { PAUSED, LEVELING_UP, GAME_OVER, PLAYING };

        // Start with the GAME_OVER state
        auto state = State::GAME_OVER;

        // Get the screen resolution and create an SFML window (SFML 3 syntax)
        sf::Vector2f resolution(sf::VideoMode::getDesktopMode().size);
        sf::RenderWindow window(sf::VideoMode(sf::Vector2u(resolution)), "Zombie Arena", sf::State::Fullscreen);

        // Create an SFML View for the main action
        sf::View mainView(sf::FloatRect({0.f, 0.f}, resolution));

        // Clock for timing everything
        sf::Clock clock;

        // How long has the PLAYING state been active
        sf::Time gameTimeTotal;

        // Mouse positions
        sf::Vector2f mouseWorldPosition;
        sf::Vector2i mouseScreenPosition;

        // Create an instance of the Player class
        Player player;

        // The boundaries of the arena
        sf::IntRect arena;

        // The main game loop
        while (window.isOpen())
        {

        }

        return 0;
}