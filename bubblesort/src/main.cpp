#include <iostream>
#include <optional>
#include <string>


#include <SFML/Graphics.hpp>
#include "randomGenerator.hpp"
#include "utility.h"


constexpr int WINDOW_WIDTH  = 200;
constexpr int WINDOW_HEIGHT = 640;
constexpr float BUBBLE_RADIUS = 50;

constexpr int NUM_BUBBLES = 300;


int main(void)
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Bubble Sort");
    window.setFramerateLimit(10);

    sf::Font font;
    if(!font.openFromFile("fonts/arial.ttf")){
        std::cerr << "Error loading font file\n";
        return -1;
    }

    std::vector<Bubble> bubbles;
    

    init_Bubbles(bubbles, NUM_BUBBLES, BUBBLE_RADIUS, {WINDOW_WIDTH, WINDOW_HEIGHT});
    
    bool sorted = false;
    size_t n_minus_1 = bubbles.size() - 1;
    size_t i = 0;           // i controls number of outer loop bubble sort executions
    size_t j = 0;           // j controls number of inner bubblesort executions

    while(window.isOpen())
    {
        while(const std::optional event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
        }

        if(!sorted){
            if(i < n_minus_1)
            {
                if(j < n_minus_1 - i)
                {
                    bubbleSortCompareAndSwap(bubbles, j);
                    j++;
                }
                else
                {
                    j = 0;
                }
            i++;
            }
            else
            {
                sorted = true;
            }
        }
        

        window.clear(sf::Color::White);
        for(auto& b : bubbles){
            b.draw(window);
        }
        
        window.display();
    }

    return 0;
}