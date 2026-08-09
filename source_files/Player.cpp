// Created by Malik Redwood on 8/8/26.
// Last updated by Malik Redwood on 8/8/26.

#include <iostream>
#include "Player.h"

Player::Player()
    : m_Sprite(m_Texture)
{
    m_Speed = START_SPEED;
    m_Health = START_HEALTH;
    m_MaxHealth = START_HEALTH;

    // Associate a texture with the sprite
    // !!Watch this space!!
    if (!m_Texture.loadFromFile("graphics/player.png")) {
      // Handle error if texture fails to load
        std::cout << "Texture fails to load" << "\n";
    };

    // Set the origin of the sprite to the center,
    // for smooth rotation
    m_Sprite.setOrigin({25.f, 25.f});
}

void Player::spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize)
{
    // Place the player in the middle of the arena
    m_Position.x = arena.position.x + (arena.size.x / 2.0f);
    m_Position.y = arena.position.y + (arena.size.y / 2.0f);

    // Copy the details of the arena
    // to the player's m_Arena
    m_Arena.position.x = arena.position.x; // left
    m_Arena.position.y = arena.position.y; // top
    m_Arena.size.x     = arena.size.x;     // width
    m_Arena.size.y     = arena.size.y;     // height

    // Remember how big the tiles are in this arena
    m_TileSize = tileSize;

    // Store the resolution for future use
    m_Resolution.x = resolution.x;
    m_Resolution.y = resolution.y;
}

// When the player dies, we will use this to reset any upgrades they might have used.
void Player::resetPlayerStats()
{
    m_Speed = START_SPEED;
    m_Health = START_HEALTH;
    m_MaxHealth = START_HEALTH;
}

// What happens when the player is hit by a zombie
// to query the last time that the player was hit
sf::Time Player::getLastHitTime()
{
    return m_LastHit;
}

// what happens when the player is hit by a zombie
// pass it in the current game time
/*
First, the if statement checks to see whether the time that’s passed in as a parameter is 200 milliseconds further ahead than the time stored in m_LastHit.
If it is, m_LastHit is updated with the time passed in and m_Health has 10 deducted from its current value.
The last line of code in this if statement is return true.
Notice that the else clause simply returns false to the calling code.
*/
// EFFECT: Health points will only be deducted from the player up to five times per second.
bool Player::hit(sf::Time timeHit)
{
    if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 200)
    {
        m_LastHit = timeHit;
        m_Health -= 10;
        return true;
    }
    else
    {
        return false;
    }
}

// Getter functions
// Allow us to keep the data neatly encapsulated in the Player class at the same time as their values are being made available to the main fu__cpp_deleted_function
sf::FloatRect Player::getPosition()
{
    return m_Sprite.getGlobalBounds();
}
sf::Vector2f Player::getCenter()
{
    return m_Position;
}
sf::Angle Player::getRotation()
{
    return m_Sprite.getRotation();
}
sf::Sprite Player::getSprite()
{
    return m_Sprite;
}
int Player::getHealth()
{
    return m_Health;
}

// Eight functions to enable the keyboard controls
void Player::moveLeft()
{
    m_LeftPressed = true;
}
void Player::moveRight()
{
    m_RightPressed = true;
}
void Player::moveUp()
{
    m_UpPressed = true;
}
void Player::moveDown()
{
    m_DownPressed = true;
}
void Player::stopLeft()
{
    m_LeftPressed = false;
}
void Player::stopRight()
{
    m_RightPressed = false;
}
void Player::stopUp()
{
    m_UpPressed = false;
}
void Player::stopDown()
{
    m_DownPressed = false;
}

void Player::update(float elapsedTime, sf::Vector2i mousePosition)
{
    // moves the player sprite
    if (m_UpPressed)
    {
        m_Position.y -= m_Speed * elapsedTime;
    }
    if (m_DownPressed)
    {
        m_Position.y += m_Speed * elapsedTime;
    }
    if (m_RightPressed)
    {
        m_Position.x += m_Speed * elapsedTime;
    }
    if (m_LeftPressed)
    {
        m_Position.x -= m_Speed * elapsedTime;
    }
    // 2. Clamp player position within arena boundaries (SFML 3 syntax)
    auto minX = static_cast<float>(m_Arena.position.x + m_TileSize);
    auto maxX = static_cast<float>(m_Arena.position.x + m_Arena.size.x - m_TileSize);
    auto minY = static_cast<float>(m_Arena.position.y + m_TileSize);
    auto maxY = static_cast<float>(m_Arena.position.y + m_Arena.size.y - m_TileSize);

    m_Position.x = std::clamp(m_Position.x, minX, maxX);
    m_Position.y = std::clamp(m_Position.y, minY, maxY);

    // 3. Update sprite position AFTER position is clamped
    m_Sprite.setPosition(m_Position);

    // 4. Calculate facing angle and set rotation (SFML 3 sf::radians)
    float radians = std::atan2(static_cast<float>(mousePosition.y) - m_Resolution.y / 2.0f,
                               static_cast<float>(mousePosition.x) - m_Resolution.x / 2.0f);

    m_Sprite.setRotation(sf::radians(radians));
}

// Increase the player's speed by 20%
void Player::upgradeSpeed()
{
    // 20% speed upgrade
    m_Speed += (START_SPEED * .2);
}

// Increase the player's health by 20%
void Player::upgradeHealth()
{
    // 20% max health upgrade
    m_MaxHealth += (START_HEALTH * .2);
}

// Increase the player's health by the amount passed in
void Player::increaseHealthLevel(int amount)
{
    m_Health += amount;
    // But not beyond the maximum
    if (m_Health > m_MaxHealth)
    {
        m_Health = m_MaxHealth;
    }
}