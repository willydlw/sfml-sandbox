#pragma once 

#include <SFML/Graphics.hpp>

class Bubble
{
    public:

    Bubble() = default;

    Bubble(sf::Color color, sf::Vector2f position, float radius = 10.0f);

    void setFillColor(sf::Color color);
    void setPosition(sf::Vector2f position);

    uint32_t getColorKey()const;
    sf::Color getFillColor()const;
    sf::Vector2f getPosition()const;

    void draw(sf::RenderWindow& window);

    public:

    // attributes
    sf::Color m_color;
    uint32_t m_colorKey;

    sf::Vector2f m_target_position;

    sf::CircleShape m_circle;
};