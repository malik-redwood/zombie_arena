// Created by Malik Redwood on 8/8/26.
// Last updated by Malik Redwood on 8/8/26.

#ifndef ZOMBIE_PLAYER_H
#define ZOMBIE_PLAYER_H

#pragma once
#include <SFML/Graphics.hpp>

class Player
{
private:
    const float START_SPEED = 200.0;
    const float START_HEALTH = 100.0;
    // Where is the player
    sf::Vector2f m_Position;
    // And a texture
    // !!Watch this space - Changes here soon!!
    sf::Texture m_Texture;
    // The sprite
    sf::Sprite m_Sprite;
    // What is the screen resolution
    sf::Vector2f m_Resolution;
    // What size is the current arena
    sf::IntRect m_Arena;
    // How big is each tile of the arena
    int m_TileSize;
    // Which direction(s) the player is moving in
    bool m_UpPressed;
    bool m_DownPressed;
    bool m_LeftPressed;
    bool m_RightPressed;
    // How much health has the player got?
    int m_Health;
    // What is the max' health the player can have
    int m_MaxHealth;
    // When was the player last hit
    sf::Time m_LastHit;
    // Speed in pixels per second
    float m_Speed;
// All our public functions next
public:
    Player();

    // prepare the object ready for use
    // IntRect arena: the size and location of the current level
    // Vector2f resolution: which will contain the screen resolution
    // int tileSize: hold the size of a background tile
    void spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize);

    // Call this at the end of every game
    // we will need to be able to take away/reset player abilities at the start of the new game
    void resetPlayerStats();

    // Handle the player getting hit by a zombie
    bool hit(sf::Time timeHit);

    // How long ago was the player last hit
    // use this function when detecting collisions, and it will allow us to make sure that the player isn’t punished too frequently for making contact with a zombie.
    sf::Time getLastHitTime();

    // Where is the player
    // describes the horizontal and vertical floating-point coordinates of the rectangle
    // also useful for collision detection
    sf::FloatRect getPosition();

    // Where is the center of the player
    // contains just the x and y locations of the very center of the player graphic
    sf::Vector2f getCenter();

    // What angle is the player facing
    // know, in degrees, which way the player is currently facing. 3 o’clock is 0 degrees and increases clockwise
    sf::Angle getRotation();

    // Send a copy of the sprite to the main function
    // returns a copy of the sprite that represents the player
    sf::Sprite getSprite();

    // The next four functions move the player
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    // Stop the player moving in a specific direction
    void stopLeft();
    void stopRight();
    void stopUp();
    void stopDown();

    // We will call this function once every frame
    void update(float elapsedTime, sf::Vector2i mousePosition);

    // Give the player a speed boost
    void upgradeSpeed();

    // Give the player some health
    void upgradeHealth();

    // Increase the max' health the player can have
    void increaseHealthLevel(int amount);

    // How much health has the player currently got?
    int getHealth();
};

#endif //ZOMBIE_PLAYER_H
