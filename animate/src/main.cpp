#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode({960, 720}), "My window");

    // Construct the texture from an image
    sf::Texture santaTexture("images/Walk1.png", false, sf::IntRect{{0,0}, {100,200}});

    sf::Vector2u tSize = santaTexture.getSize();
    std::cerr << "texture size, x: " << tSize.x << ", y: " << tSize.y << "\n";

    

    sf::Sprite santaSprite(santaTexture);

    #if 1
    if(!santaTexture.resize({tSize.x / 2, tSize.y / 2}, true))
    {
        std::cerr << "resize failed\n";
    }


    sf::Vector2u newSize = santaTexture.getSize();
    std::cerr << "new size x: " << newSize.x << ", y: " << newSize.y << "\n";


    santaSprite.setTexture(santaTexture);
    #endif


    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Green);

        // draw everything here...
        // window.draw(...);
        window.draw(santaSprite);

        // end the current frame
        window.display();
    }
}