#include <iostream>
#include <optional>
#include <string>


#include <SFML/Graphics.hpp>
#include "randomGenerator.hpp"
#include "utility.h"


constexpr int WINDOW_WIDTH  = 640;
constexpr int WINDOW_HEIGHT = 480;
constexpr float BUBBLE_RADIUS = 20;

constexpr int NUM_BUBBLES = 10;


int main(void)
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Bubble Sort");
    window.setFramerateLimit(60);

    sf::Font font;
    if(!font.openFromFile("fonts/arial.ttf")){
        std::cerr << "Error loading font file\n";
        return -1;
    }

    std::vector<Bubble> bubbles(NUM_BUBBLES);
    

    init_Bubbles(bubbles, NUM_BUBBLES, BUBBLE_RADIUS, {WINDOW_WIDTH, WINDOW_HEIGHT});
    


    while(window.isOpen())
    {
        while(const std::optional event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        for(int i = 0; i < NUM_BUBBLES; i++){
            bubbles[i].draw(window);
        }
        window.display();
    }

    return 0;
}