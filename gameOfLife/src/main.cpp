#include <SFML/Graphics.hpp>

#include <iostream>
#include <optional>

#include "gameLife.hpp"

#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   800
#define GRID_ROWS       80
#define GRID_COLS       80
#define CELL_SIZE       (SCREEN_WIDTH / GRID_COLS)  


int main(void)
{
    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "Conway's Game of Life");
    sf::Font font;

    // TODO: correct copy path in cmake lists so this can be changed
    // to just "arial.ttf"
    if(!font.openFromFile("fonts/arial.ttf"))
    {
        std::cerr << "Error opening font file\n";
        return 1;
    }

    sf::Text text(font);
    text.setString("Generation");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);

    GameLife game(GRID_ROWS, GRID_COLS, CELL_SIZE);
    game.initRandom(0,1);

    std::cerr << "Game Info\n" << game << "\n";

    window.setFramerateLimit(5);

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
        window.draw(text);
        window.display();
    }

    return 0;
}