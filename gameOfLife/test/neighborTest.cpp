#include "neighborTest.hpp"
#include "gameLife.hpp"

#include <iostream>
#include <string>
#include <optional>

namespace neighborTest
{
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
            Location upperLeft(0,0);
            std::vector<Location> testLocation;
            testLocation.push_back(upperLeft);

            std::string testName = "Test Upper Left Neighbor";

            neighborTest(testLocation, testName);

        }
    }



    // Visual confirmation of neighbors
    //      Test cell is located at row, col 
    //      Draw test cell's neighbors in neighbor color
    void showNeighbors(int row, int col, sf::Color& testCellColor, sf::Color& neighborColor)
    {
        std::cout << __func__ << " Under Construction ***\n";
        std::cout << "row: " << row << ", col: " << col << "\n";
    }


}


