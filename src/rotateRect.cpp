#include <SFML/Graphics.hpp>

#include <iostream>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({600u, 600u}), "Rotate Rectangle");
    window.setFramerateLimit(60);

    int width = window.getSize().x;
    int height = window.getSize().y;

    std::cerr << "width: " << width << ", height: " << height << "\n";

    sf::RectangleShape rect({100.0f, 100.0f});
    rect.setSize({100.0f, 10.0f});

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
        window.draw(rect);
        window.display();
    }
}