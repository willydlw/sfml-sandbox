#include "bubble.h"

Bubble::Bubble(sf::Color color, sf::Vector2f position, float radius) : 
    m_color(color),
    m_colorKey(m_color.toInteger()),
    m_target_position(position)
{
    m_circle.setFillColor(m_color);
    m_circle.setOutlineColor(sf::Color::Black);
    m_circle.setOutlineThickness(1);
    m_circle.setPosition(position);
    m_circle.setRadius(radius);
}

void Bubble::draw(sf::RenderWindow& window)
{
    window.draw(m_circle);
}


void Bubble::setFillColor(sf::Color color)
{
    m_color = color;
}

void Bubble::setPosition(sf::Vector2f position)
{
    m_circle.setPosition(position);
}

uint32_t Bubble::getColorKey()const
{
    return m_colorKey;
}

sf::Color Bubble::getFillColor()const
{
    return m_color;
}

sf::Vector2f Bubble::getPosition()const
{
    return m_circle.getPosition();
}