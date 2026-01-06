#pragma once

#include <vector>

#include "bubble.h"
#include <SFML/Graphics.hpp>

void init_Bubbles(std::vector<Bubble>& bubbles, int numBubbles, float radius, 
        sf::Vector2f windowSize);