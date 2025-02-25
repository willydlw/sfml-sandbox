#include <SFML/Graphics.hpp>

#include <iostream>
#include <optional>

#include "gameLife.hpp"

#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   800
#define GRID_ROWS       40
#define GRID_COLS       40
#define CELL_SIZE        SCREEN_WIDTH / GRID_COLS  


int main(void)
{
    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "Conway's Game of Life");

    GameLife game(GRID_ROWS, GRID_COLS, CELL_SIZE);
    game.initRandom(0,1);

    window.setFramerateLimit(2);

    while(window.isOpen())
    {
        // check all window events triggered since last loop iteration
        while(const std::optional event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        // call clear to erase contents of previous frame
        window.clear(GameLife::DEAD_COLOR);
        game.nextGeneration();
        game.draw(window);
        window.display();
    }

    return 0;
}