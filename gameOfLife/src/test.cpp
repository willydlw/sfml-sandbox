#include "gameLife.hpp"

#include <iostream>
#include <string>

static constexpr int SCREEN_WIDTH = 400;
static constexpr int SCREEN_HEIGHT = 400;

static const sf::Color TEST_CELL_COLOR(50, 50, 120);
static const sf::Color NEIGHBOR_COLOR(100, 100, 0);

static constexpr int TEST_GRID_ROWS = 10;
static constexpr int TEST_GRID_COLS = 10;
static constexpr int TEST_CELL_SIZE = 40;

void neighborTest(std::vector<Location>& testLocations, std::string& testName)
{
    GameLife game(TEST_GRID_ROWS, TEST_GRID_COLS, TEST_CELL_SIZE);
    game.setInitialPattern(testLocations);

    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), testName.c_str());
    window.setFramerateLimit(1);

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
        game.draw(window);
        window.display();
    }

}

void runTests(void)
{
    {   // test upper left corner
        Location upperLeft = {.row = 0, .col = 0};
        std::vector<Location> testLocation;
        testLocation.push_back(upperLeft);

        std::string testName = "Test Upper Left Neighbor";

        neighborTest(testLocation, testName);

    }
}

int main(void)
{
    runTests();
    return 0;
}