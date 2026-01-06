#include "utility.h"

#include "randomGenerator.hpp"

void init_Bubbles(std::vector<Bubble>& bubbles, int numBubbles, float radius, 
        sf::Vector2f windowSize)
{
    RandomGenerator<uint8_t> colorGenerator(static_cast<uint8_t>(0), static_cast<uint8_t>(255));
    RandomGenerator<float> xGenerator(radius, windowSize.x - radius);
    RandomGenerator<float> yGenerator(radius, windowSize.y - radius);

    for(int i = 0; i < numBubbles; i++){
        uint8_t red = colorGenerator.generate();
        uint8_t green = colorGenerator.generate();
        uint8_t blue = colorGenerator.generate();

        sf::Color color{red, green, blue};
        sf::Vector2f position {xGenerator.generate(), yGenerator.generate()};
        
        bubbles.emplace_back(color, position);
    }
}