#include <SFML/Graphics.hpp>

#include <optional>
#include <cstdlib>

#define MARGIN 8
#define WINDOW_WIDTH (800 + 2 * MARGIN) 
#define WINDOW_HEIGHT (800 + 2 * MARGIN)


struct Maze{
    int width;
    int height;
    bool* rightWalls;
    bool* downWalls;
};

int main(void)
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), 
        "Randomized Maze Generation - DFS Recursive Backtrack");

    window.setFramerateLimit(60);

    // grid cell width
    int cellWidth = 10;
    int cellHeight = 10;
    int numCells = cellWidth * cellHeight;
    bool* rightWalls = (bool*)calloc(numCells, sizeof(bool));
    bool* downWalls = (bool*) calloc(numCells, sizeof(bool));

    for(int i = 0; i < numCells; i++)
    {
        rightWalls[i] = true;
        downWalls[i] = true;
    }

    Maze maze = {
        .width = cellWidth,
        .height = cellHeight,
        .rightWalls = rightWalls,
        .downWalls = downWalls
    };

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
        window.draw(windowRect);
        window.draw(mazeRect);
        window.display();
    }

    free(rightWalls);
    free(downWalls);

    return 0;
}