#include <SFML/Graphics.hpp>

#include <iostream>
#include <optional>
#include <cmath>            // floor

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Santa Animation");

    sf::Vector2u windowSize = window.getSize();

    sf::RectangleShape ground{{800, 100}};
    ground.setPosition({0, 500});
    ground.setFillColor(sf::Color::Green);

    sf::Texture santaTexture;
    if(!santaTexture.loadFromFile("images/Walk1.png")){
        std::cerr << "Failed to load image\n";
    }

    santaTexture.setSmooth(false);

    sf::Sprite santaSprite(santaTexture);
 
    
    sf::Vector2u tsize = santaTexture.getSize();
    std::cerr << "texture size, x: " << tsize.x << ", y: " << tsize.y << "\n";

    // scale images to 15% of window size
    float scaleX = (windowSize.x * 0.15f) / tsize.x;
    float scaleY = (windowSize.y * 0.15f) / tsize.y;

    // to maintain aspect ratio and prevent stretching, use smaller of two scale factors 
    float scaleFactor = std::min(scaleX, scaleY);

    std::cerr << "scaleFactor: " << scaleFactor << ", scaleX: " << scaleX << ", scaleY: " << scaleY << "\n";

    float scaledWidth = floor(tsize.x * scaleFactor);
    float scaledHeight = floor(tsize.y * scaleFactor);

    std::cerr << "scaled width: " << scaledWidth << ", height: " << scaledHeight << "\n";


    santaSprite.setScale({scaleFactor, scaleFactor}); 

    santaSprite.setPosition({scaledWidth, 500-scaledHeight});
   

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
        window.clear(sf::Color::White);

        // draw everything here...
        window.draw(ground);
        window.draw(santaSprite);
       

        // end the current frame
        window.display();
    }
}