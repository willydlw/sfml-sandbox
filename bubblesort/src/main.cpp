#include <iostream>
#include <optional>
#include <string>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

constexpr int WINDOW_WIDTH  = 640;
constexpr int WINDOW_HEIGHT = 480;
constexpr float RECT_WIDTH = 64;
constexpr float RECT_HEIGHT = 48;

constexpr int ASIZE = 5;

constexpr int RECT_SPACING = (WINDOW_WIDTH - (ASIZE * RECT_WIDTH)) / (ASIZE + 1);

constexpr int UNSORTED[5] = {7, 12, 9, 11, 3};

int main(void)
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Bubble Sort");
    window.setFramerateLimit(1);

    sf::Font font;
    if(!font.openFromFile("fonts/arial.ttf")){
        std::cerr << "Error loading font file\n";
        return -1;
    }

    std::cout << "RECT_SPACING: " << RECT_SPACING << "\n";

    std::vector<sf::RectangleShape> rects(ASIZE);
    std::vector<sf::Text> rectText;                 // sf::Text has no default constructor, so no size is specified

    // initialize rectangle shapes
    for(int i = 0; i < ASIZE; i++){
        rects[i].setSize({RECT_WIDTH, RECT_HEIGHT});
        rects[i].setPosition({static_cast<float>((i+1) * RECT_SPACING + i * RECT_WIDTH), 
                                static_cast<float>( (WINDOW_HEIGHT - RECT_HEIGHT)/2)});
        rects[i].setFillColor({150, 150, 150});
    }

    #if 1
    // initialize rectangle text objects
    for(int i = 0; i < ASIZE; i++){
        sf::Text text(font);

        text.setString(std::to_string(UNSORTED[i]));
        text.setCharacterSize(32);
        text.setFillColor(sf::Color::White);

        
        sf::FloatRect textBounds = text.getLocalBounds();
        sf::Vector2f tpos = textBounds.position;
        sf::Vector2f tsize = textBounds.size;

        std::cout << "i: " << i << " tpos, x: " << tpos.x << ", y: " << tpos.y << 
                ", tsize, x: " << tsize.x << ", y: " << tsize.y << "\n";
        
        text.setOrigin({tpos.x + tsize.x / 2.0f,
                        tpos.y + tsize.y / 2.0f });

        sf::Vector2f rectCenter = rects[i].getPosition() + rects[i].getSize() / 2.0f;
        text.setPosition(rectCenter);
        
        rectText.push_back(text);
    }

    #endif

    std::cout << "rectText.size() " << rectText.size() << "\n";



    while(window.isOpen())
    {
        while(const std::optional event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        for(int i = 0; i < ASIZE; i++){
            window.draw(rects[i]);
            window.draw(rectText[i]);
        }
        window.display();
    }

    return 0;
}