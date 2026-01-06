#pragma once 

#include <SFML/Graphics.hpp>

class Bubble
{
    public:

    Bubble() = default;

    Bubble(sf::Color color, sf::Vector2f position);

    void setFillColor(sf::Color color);
    void setPosition(sf::Vector2f position);

    sf::Color getFillColor()const;
    sf::Vector2f getPosition()const;

    void draw(sf::RenderWindow& window);

    private:

    // attributes
   
    sf::Color m_color;
    uint32_t m_colorKey;

    sf::Vector2f m_position;

    sf::CircleShape m_circle;
};