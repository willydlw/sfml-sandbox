#ifndef GAMELIFE_HPP
#define GAMELIFE_HPP

#include <SFML/Graphics.hpp>

#include<iostream>
#include <random>
#include <vector>

struct Location{
    int row;
    int col;

    Location(int row = 0, int col = 0) : row(row), col(col) {}
};

class GameLife{
    public:
    // Drawing Constants
    static const sf::Color ALIVE_COLOR;
    static const sf::Color DEAD_COLOR;
    static const sf::Color TEST_COLOR;
    static const sf::Color NEIGHBOR_COLOR;

    static constexpr float OUTLINE_THICKNESS = 2.0f;

    // Cell States
    static constexpr int DEAD = 0;
    static constexpr int ALIVE = 1;

    // Random number generater seeded with std::random_device
    static std::mt19937 RAND_GEN;
    
    //  Neighbor offset pattern: NE, N, NW, E, W, SE, S, SW
    static constexpr int NUM_NEIGHBORS = 8;
    const int DR[NUM_NEIGHBORS] = {-1, -1, +1,  0,  0, +1, +1, +1};
    const int DC[NUM_NEIGHBORS] = {-1,  0, +1, -1, +1, -1,  0, +1};


    // constructors
    GameLife() = default;
    GameLife(int rows, int cols, int cellSize);

    // destructor
    ~GameLife();

    // accessor functions
    int getCellState (int row, int col) const;
    int getRows() const;
    int getCols() const;
    int getCellSize() const;

    // setter functions 
    void setCellState(int row, int col, int state);


    // Initialization
    void initRandom(int min = 0, int max = 1);
    void setInitialPattern(const std::vector<Location>& aliveLocations);

    // Process next generation
    Location calcNeighborLocation(int row, int col, int rowOffset, int colOffset);
    int countLiveNeighbors(int row, int col);
    std::vector<Location> getNeighborList(int row, int col);

    // Apply rules to generate the next generation
    void nextGeneration(void);


    // Draw Grid
    void draw(sf::RenderWindow& window);

    // Draws test cell and surrounding neigbhors
    // Used as a visual confirmation that neighbors are correctly identified
    void drawNeighbors(sf::RenderWindow& window, const Location& centerCell, 
            const std::vector<Location>& neighbors);

    // overloaded operators
    friend std::ostream& operator << (std::ostream& os, const GameLife& obj);


    private:

    int m_rows;
    int m_cols;
    int m_cell_size;
    std::vector<std::vector<int>> m_grid;
    
};


#endif