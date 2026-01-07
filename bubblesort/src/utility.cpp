#include "utility.h"

#include "randomGenerator.hpp"

#include <iomanip>
#include <iostream>

void init_Bubbles(std::vector<Bubble>& bubbles, int numBubbles, float radius, 
        sf::Vector2f windowSize)
{
    RandomGenerator<uint8_t> colorGenerator(static_cast<uint8_t>(0), static_cast<uint8_t>(255));
    RandomGenerator<float> xGenerator(radius, windowSize.x - radius);
    RandomGenerator<float> yGenerator(radius, windowSize.y - radius);

    std::cout << __func__ << ", numBubbles: " << numBubbles << "\n";

    float spacing = windowSize.x / numBubbles;

    for(int i = 0; i < numBubbles; i++){
        uint8_t red = colorGenerator.generate();
        uint8_t green = colorGenerator.generate();
        uint8_t blue = colorGenerator.generate();

        sf::Color color{red, green, blue};
        // sf::Vector2f position {xGenerator.generate(), yGenerator.generate()};

        float xPos = i * spacing + (spacing / 2.f);
        float yPos = windowSize.y / 2.f;    // center in the window
        sf::Vector2f position = {xPos, yPos};

        #if 0
        std::cout << "red: " << (int)red << ", green: " << (int)green 
            << ", blue: " << (int)blue << "\n";
        std::cout << "x: " << position.x << ", y: " << position.y << "\n";
        #endif
        
        bubbles.emplace_back(color, position);
    }
}



void bubbleSortCompareAndSwap(std::vector<Bubble>& bubbles, int j)
{
    if(bubbles[j].getColorKey() > bubbles[j+1].getColorKey()){
                sf::Vector2f tempPosition = bubbles[j].getPosition();
                bubbles[j].setPosition(bubbles[j+1].getPosition());
                bubbles[j+1].setPosition(tempPosition);
    }
}

void bubbleSort(std::vector<Bubble>& bubbles)
{
    std::cout << __func__ << "\n";
    size_t n = bubbles.size();

    for(size_t i = 0; i < n-1; i++){
        for(size_t j = 0; j < n-i-1; j++){

            #if 0
            std::cout << std::showbase          // add the "0x" prefix 
                << std::hex                     // set the base to hexadecimal
                << std::setfill('0')            // use 0 as the padding character
                << std::setw(8)
                << "colorKeys j: " << bubbles[i].getColorKey() 
                << ", j+1: " << bubbles[i].getColorKey() << "\n";
            #endif
            if(bubbles[j].getColorKey() > bubbles[j+1].getColorKey()){
                sf::Vector2f tempPosition = bubbles[j].getPosition();
                bubbles[j].setPosition(bubbles[j+1].getPosition());
                bubbles[j+1].setPosition(tempPosition);
            }
        }
    }
}