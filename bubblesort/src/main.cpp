#include <iostream>
#include <optional>
#include <string>


#include <SFML/Graphics.hpp>
#include "randomGenerator.hpp"
#include "utility.h"


constexpr int WINDOW_WIDTH  = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr float BUBBLE_RADIUS = 10.0f;

constexpr int NUM_BUBBLES = 50;


int main(void)
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Bubble Sort");
    window.setFramerateLimit(60);

    sf::Font font;
    if(!font.openFromFile("fonts/arial.ttf")){
        std::cerr << "Error loading font file\n";
        return -1;
    }

    std::vector<Bubble> bubbles;
    init_Bubbles(bubbles, NUM_BUBBLES, BUBBLE_RADIUS, {WINDOW_WIDTH, WINDOW_HEIGHT});

    bool sorted = false;
    bool isAnimating = false;

    sf::Clock clock;
    float animationTime = 0.5f;     // time for one swap animation
    float currentAnimationTime = 0.0f; 

    sf::Vector2f startPosJ, startPosJPlus1;
    sf::Vector2f endPosJ, endPosJPlus1;
    int swapIndexJ = -1;             // Index of the first circle being swapped
    
    int i = 0;           // i controls number of outer loop bubble sort executions
    int j = 0;           // j controls number of inner bubblesort executions

    while(window.isOpen())
    {
        sf::Time deltaTime = clock.restart();

        while(const std::optional event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
        }

        // update logic
        if(!sorted && !isAnimating){
            if(i < NUM_BUBBLES - 1){
                if(j < NUM_BUBBLES - i - 1){
                    if(bubbles[j].getColorKey() > bubbles[j+1].getColorKey()){
                        isAnimating = true;
                        swapIndexJ = j;
                        currentAnimationTime = 0.0f;
                        startPosJ = bubbles[j].getPosition();
                        startPosJPlus1 = bubbles[j+1].getPosition();

                        // Target positions are simple horizontal swaps
                        endPosJ = startPosJPlus1;
                        endPosJPlus1 = startPosJ;

                        // Vertically move them up slighlty during the swap
                        endPosJ.y -= 50.0f;
                        endPosJPlus1.y -= 50.0f;

                        // Move the one bubbling down 
                        startPosJ.y += 50.0f;
                        startPosJPlus1.y += 50.0f;
                    }
                    j++;
                } else{
                    j = 0;
                    i++;
                }
            }else{
                sorted = true;
                std::cout << "Array sorted!\n";
            }
        }

        if(isAnimating){
            currentAnimationTime += deltaTime.asSeconds();
            if(currentAnimationTime < animationTime){
                float t = currentAnimationTime / animationTime;
                // use a simple linear interpolation for smooth movement
                bubbles[swapIndexJ].setPosition(
                    {startPosJ.x + t * (endPosJ.x - startPosJ.x),
                     startPosJ.y + t * (endPosJ.y - startPosJ.y)}
                );
                bubbles[swapIndexJ+1].setPosition(
                    { startPosJPlus1.x + t * (endPosJPlus1.x - startPosJPlus1.x),
                      startPosJPlus1.y + t * (endPosJPlus1.y - startPosJPlus1.y)}
                );
            } else {
                // Animation finished, complete the data swap
                isAnimating = false;
                // Reset to correct horizontal positions immediately after animation
                bubbles[swapIndexJ].setPosition({endPosJ.x, window.getSize().y / 2.f});
                bubbles[swapIndexJ+1].setPosition({endPosJPlus1.x, window.getSize().y / 2.f});
                
                // Swap the underlying data in the vector
                std::swap(bubbles[swapIndexJ], bubbles[swapIndexJ+1]); 
            }
        }

        #if 0
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
        #endif

        window.clear(sf::Color::White);
        for(auto& b : bubbles){
            b.draw(window);
        }
        
        window.display();
    }

    return 0;
}