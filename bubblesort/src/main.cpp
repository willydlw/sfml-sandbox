#include <iostream>
#include <optional>
#include <string>


#include <SFML/Graphics.hpp>

#include "randomGenerator.hpp"


constexpr int WINDOW_WIDTH  = 640;
constexpr int WINDOW_HEIGHT = 480;
constexpr float BUBBLE_RADIUS = 20;

constexpr int NUM_CIRCLES = 10;


int main(void)
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Bubble Sort");
    window.setFramerateLimit(1);

    sf::Font font;
    if(!font.openFromFile("fonts/arial.ttf")){
        std::cerr << "Error loading font file\n";
        return -1;
    }

    // Generate unsigned 24 bit random values
    // Store result in 32-bite unsigned int
    RandomGenerator<uint32_t> colorGenerator(0x000000, 0xFFFFFF);

    uint32_t result = colorGenerator.generate();

    std::cout << "Random color generated: " << std::ios::hex << result << "\n";

    std::vector<sf::CircleShape> circles(NUM_CIRCLES);

    float offset = WINDOW_HEIGHT / NUM_CIRCLES;

    // initialize circle shapes
    for(int i = 0; i < NUM_CIRCLES; i++){
        circles[i].setRadius(BUBBLE_RADIUS);
        circles[i].setPosition({static_cast<float>(WINDOW_WIDTH/2), 
                                static_cast<float>( BUBBLE_RADIUS + i * offset)});
        circles[i].setFillColor({150, 150, 150});
    }


    while(window.isOpen())
    {
        while(const std::optional event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        for(int i = 0; i < NUM_CIRCLES; i++){
            window.draw(circles[i]);
            
        }
        window.display();
    }

    return 0;
}