#include <SFML/Graphics.hpp>
#include <array>
#include <optional>

#include <iostream>

#include "arrow.hpp"
#include "vectorMath.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600 

int main(void)
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Vector with Arrow Tip");
    window.setFramerateLimit(60);

    // lines without thickness 
    std::array<sf::Vertex, 2> vertLine =
    {
        sf::Vertex{sf::Vector2f{WINDOW_WIDTH/2, 0}},
        sf::Vertex{sf::Vector2f{WINDOW_WIDTH/2, WINDOW_HEIGHT}}
    };

    std::array<sf::Vertex, 2> horzLine =
    {
        sf::Vertex{sf::Vector2f{0, WINDOW_HEIGHT/2}},
        sf::Vertex{sf::Vector2f{WINDOW_WIDTH, WINDOW_HEIGHT/2}}
    };


    sf::Vector2f dimensions{100.0f, 10.0f};
    sf::RectangleShape rect1(dimensions);
    rect1.setFillColor(sf::Color::Green);


    sf::Font font("fonts/arial.ttf");
    sf::Text text(font);
    text.setString("Origin Translated to Center");
    text.setFillColor(sf::Color::Green);

    float radius = 50.0f;
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::Green);
    // If you don't set origin, then set position is the top 
    // left corner of circle bounding box
    circle.setOrigin({circle.getRadius(), circle.getRadius()});
    circle.setPosition({radius, WINDOW_HEIGHT/2.0f});

    sf::Vector2f circlePosition = circle.getPosition();
    sf::Vector2f circleOrigin = circle.getOrigin();
    std::cerr << "circle origin, x: " << circleOrigin.x 
        << ", y: " << circleOrigin.y << "\n";
    std::cerr << "circle position, x: " << circlePosition.x 
        << ", y: " << circlePosition.y << "\n";

   
    #if 1
    ArrowShape arrow(circle.getPosition(), circle.getPosition() + sf::Vector2f(0.0f, 100.0f));
    arrow.setColor(sf::Color::Red);
    #endif

    while(window.isOpen())
    {
        while(const std::optional event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.draw(vertLine.data(), vertLine.size(), sf::PrimitiveType::Lines);
        window.draw(horzLine.data(), horzLine.size(), sf::PrimitiveType::Lines);
       
        window.draw(circle);
        window.draw(arrow);
        //window.draw(text);
        window.display();
    }
}
