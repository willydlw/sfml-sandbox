#include <SFML/Graphics.hpp>

#include <iostream>
#include <optional>
#include <random>
#include <vector>

#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   800
#define GRID_ROWS       40
#define GRID_COLS       40
#define CELL_WIDTH       SCREEN_WIDTH / GRID_COLS  
#define CELL_HEIGHT      SCREEN_HEIGHT / GRID_ROWS 

// Random number generater seeded with std::random_device
static std::mt19937 RAND_GEN(std::random_device{}());

// Uniform distribution for integers between 0 and 1 (inclusive)
static std::uniform_int_distribution<int> RAND_DIST01(0, 1);


// Fill array with randomly generatred 1's and 0's
void initRandom(int *arr, int  rows, int cols)
{
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            arr[r * cols + c] = RAND_DIST01(RAND_GEN);
        }
    }
}

void update(int *arr, int rows, int cols)
{
    int temp[rows][cols];
}

void drawGrid(sf::RenderWindow& window, int *arr, int rows, int cols)
{
    sf::RectangleShape rect(sf::Vector2f{static_cast<float>(CELL_WIDTH), static_cast<float>(CELL_HEIGHT)});

    for(int r = 0; r < rows; r++)
    {
        for(int c = 0; c < cols; c++)
        {
            rect.setPosition(sf::Vector2f{static_cast<float>(c * CELL_WIDTH), static_cast<float>(r * CELL_HEIGHT)});
            if(arr[r * cols + c] == 1)
            {
                rect.setFillColor(sf::Color::White);
            }
            else 
            {
                rect.setFillColor(sf::Color::Black);
            }

            window.draw(rect);
        }
    }
}

int main(void)
{

    int grid[GRID_ROWS * GRID_COLS];
    initRandom(grid, GRID_ROWS, GRID_COLS);

    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "Conway's Game of Life");


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
        window.clear(sf::Color::Yellow);
        drawGrid(window, grid, GRID_ROWS, GRID_COLS);
        window.display();
    }

    return 0;
}