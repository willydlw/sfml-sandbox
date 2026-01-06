#include "bubble.h"

Bubble::Bubble(sf::Color color) : 
    m_color(color),
    m_colorKey(m_color.toInteger())
{}

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
    m_position = position;
}

sf::Color Bubble::getFillColor()const
{
    return m_color;
}

sf::Vector2f Bubble::getPosition()const
{
    return m_position;
}