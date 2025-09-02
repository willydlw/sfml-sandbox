#include <SFML/Graphics.hpp>
#include <array>
#include <optional>

#include <iostream>

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


    sf::Font font("arrow/fonts/arial.ttf");
    sf::Text text(font);
    text.setString("Origin Translated to Center");
    text.setFillColor(sf::Color::Green);

    sf::Vector2f test({30.0f, 40.0f});
    float testMagnitude = calculateMagnitude(test);
    float testHeadingRad = calculateHeading(test);
    float testHeadingDegrees = radiansToDegrees(testHeadingRad);

    std::cout   << "test vector\n"
                << "position,  x: " << test.x  << ", y: " << test.y << "\n"
                << "magnitude   : " << testMagnitude << "\n"
                << "heading, rad: " << testHeadingRad << ", degrees: " << testHeadingDegrees
                << std::endl;

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
        window.draw(rect1);
        //window.draw(text);
        window.display();
    }
}
