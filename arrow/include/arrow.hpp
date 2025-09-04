#pragma once 

#include <SFML/Graphics.hpp>

class ArrowShape: public sf::Drawable, public sf::Transformable 
{
    public:
        ArrowShape(sf::Vector2f start, sf::Vector2f end, 
                float thickness = 2.0f, float headSize = 10.0f, sf::Color color = sf::Color::White);

        void update(sf::Vector2f start, sf::Vector2f end);
        
        void setColor(sf::Color color);

    private:

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        sf::RectangleShape m_shaft;
        sf::ConvexShape m_head;
        sf::Vector2f m_start;
        sf::Vector2f m_end;
        float m_thickness;
        float m_headSize;
};