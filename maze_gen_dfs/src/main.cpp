#include <SFML/Graphics.hpp>

#include <optional>
#include <cstdlib>

#include "maze.h"

#define MARGIN 8
#define WINDOW_WIDTH (400 + 2 * MARGIN) 
#define WINDOW_HEIGHT (400 + 2 * MARGIN)

#define CELLSIZE 100
#define NUM_ROWS WINDOW_HEIGHT / CELLSIZE
#define NUM_COLS WINDOW_WIDTH / CELLSIZE


int main(void)
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), 
        "Randomized Maze Generation - DFS Recursive Backtrack");

    window.setFramerateLimit(60);

    // grid cell size(pixels)
    Maze maze(NUM_ROWS, NUM_COLS, MARGIN, CELLSIZE);
   
   
    sf::RectangleShape windowRect({WINDOW_WIDTH, WINDOW_HEIGHT});
    windowRect.setPosition({0.0f, 0.0f});
    windowRect.setFillColor(sf::Color(150,50,250));

    sf::RectangleShape mazeRect({WINDOW_WIDTH - 2 * MARGIN, WINDOW_HEIGHT - 2 * MARGIN});
    mazeRect.setPosition(sf::Vector2f(MARGIN, MARGIN));
    mazeRect.setFillColor(sf::Color::Yellow);


    while(window.isOpen())
    {
        while(const std::optional event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        //window.draw(windowRect);
        //window.draw(mazeRect);
        maze.draw(window);
        
        window.display();
    }

    return 0;
}