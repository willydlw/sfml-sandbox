#include <SFML/Graphics.hpp>

#include <optional>
#include <cstdlib>

#include "maze.h"

#define MARGIN 10
#define WINDOW_WIDTH (400 + 2 * MARGIN) 
#define WINDOW_HEIGHT (400 + 2 * MARGIN)

#define CELLSIZE 100
#define NUM_ROWS WINDOW_HEIGHT / CELLSIZE
#define NUM_COLS WINDOW_WIDTH / CELLSIZE


int main(void)
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), 
        "Randomized Maze Generation - DFS Recursive Backtrack");

    window.setFramerateLimit(1);

    // grid cell size(pixels)
    Maze maze(NUM_ROWS, NUM_COLS, MARGIN/2, CELLSIZE);
   
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
        if(maze.state() != Maze::GenerateState::COMPLETE){
            maze.generate();
        }
        maze.draw(window);
        window.display();
    }

    return 0;
}