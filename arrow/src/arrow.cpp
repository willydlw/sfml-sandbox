#include <SFML/System/Angle.hpp>
#include <cmath>
#include "arrow.hpp"


ArrowShape::ArrowShape(sf::Vector2f start, sf::Vector2f end, float thickness, 
                float headSize, sf::Color color) 
: m_start(start), m_end(end), m_thickness(thickness), m_headSize(headSize)
{
    setColor(color);
    m_head.setPointCount(3);
    update(start, end);
}

void ArrowShape::update(sf::Vector2f start, sf::Vector2f end)
{
    m_start = start;
    m_end = end;

    // Calculate vector properties 
    sf::Vector2f direction = m_end - m_start;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    

    // arrow body properties 
    m_body.setSize(sf::Vector2f(length - m_headSize, m_thickness));
    m_body.setPosition(m_start);

    // sfml uses degrees as rotation argument
    float rotation = std::atan2(direction.y, direction.x) * 180.0f / 3.14159f;
    // function argument must be Angle type. degrees() converst float to angle type
    m_body.setRotation(sf::degrees(rotation));

    // arrow head properties 
    m_head.setPoint(0, sf::Vector2f(0.0f,0.0f));
    m_head.setPoint(1, sf::Vector2f(m_headSize, m_headSize / 2.0f));
    m_head.setPoint(2, sf::Vector2f(0.0f, m_headSize));
    m_head.setOrigin(sf::Vector2f{0, m_headSize / 2.0f});
    m_head.setPosition(m_end);
    m_head.setRotation(sf::degrees(rotation));    

}


void ArrowShape::setColor(sf::Color color)
{
    m_body.setFillColor(color);
    m_head.setFillColor(color);
}

   

void ArrowShape::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply transform and then draw components
    states.transform *= getTransform();
    target.draw(m_body, states);
    target.draw(m_head, states);
}