#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

int main()
{
    unsigned int windowWidth = 600U;
    unsigned int windowHeight = 600U;

    auto window = sf::RenderWindow(sf::VideoMode({windowWidth, windowHeight}), "Rotate Rectangle");
    window.setFramerateLimit(60);

    sf::RectangleShape vertLine({2.0f, static_cast<float>(windowHeight)});
    vertLine.setPosition({windowWidth/4.0f, 0.0f});

    sf::RectangleShape horzLine({static_cast<float>(windowWidth), 2.0f});
    horzLine.setPosition({0.0f, windowHeight/2.0f});

    std::vector<sf::RectangleShape> rects;
    sf::Angle ang = sf::degrees(-45);
    std::vector<sf::Color> colCodes;
    colCodes.push_back(sf::Color::Blue);
    colCodes.push_back(sf::Color::Green);
    colCodes.push_back(sf::Color::Red);
    colCodes.push_back(sf::Color::Yellow);

    for(size_t i = 0; i < 4; i++){
        sf::RectangleShape r({100.0f, 10.0f});
        r.setPosition({windowWidth/4.0f, windowHeight/2.0f - 5.0f});
        r.setRotation(ang);
        r.setFillColor(colCodes[i]);
        ang = ang + sf::Angle(sf::degrees(45));
        rects.push_back(r);
    }

    //rect.setOrigin({rect.getSize()});
    //rect.setRotation(sf::Angle(sf::degrees(45)));

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        window.draw(horzLine);
        window.draw(vertLine);
        for(size_t i = 0; i < rects.size(); i++){
            window.draw(rects[i]);
        }
       
        window.display();
    }
}