#ifndef NEIGHBOR_TEST_HPP
#define NEIGHBOR_TEST_HPP

#include "gameLife.hpp"

namespace neighborTest{

    static constexpr int SCREEN_WIDTH = 400;
    static constexpr int SCREEN_HEIGHT = 400;

    static const sf::Color TEST_CELL_COLOR(50, 50, 120);
    static const sf::Color NEIGHBOR_COLOR(100, 100, 0);

    static constexpr int TEST_GRID_ROWS = 10;
    static constexpr int TEST_GRID_COLS = 10;
    static constexpr int TEST_CELL_SIZE = 40;


     void runTests(void);
     void neighborTest(std::vector<Location>& testLocations, std::string& testName);

}

#endif 