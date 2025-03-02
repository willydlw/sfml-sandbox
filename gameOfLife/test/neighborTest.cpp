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
            window.clear(sf::Color::Black);
            game.draw(window);

            for(int i = 0; i < 1; i++)
            {
                int r = testLocations[i].row;
                int c = testLocations[i].col;
                std::vector<Location> neighborList = game.getNeighborList(r, c);
                game.drawNeighbors(window, testLocations[i], neighborList);
            }
            
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


}


