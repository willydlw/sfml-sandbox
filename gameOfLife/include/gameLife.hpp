#ifndef GAMELIFE_HPP
#define GAMELIFE_HPP

#include <SFML/Graphics.hpp>

#include<iostream>
#include <random>
#include <vector>

class GameLife{
    public:

    static const sf::Color ALIVE_COLOR;
    static const sf::Color DEAD_COLOR;


    static constexpr int DEAD = 0;
    static constexpr int ALIVE = 1;

    static constexpr float OUTLINE_THICKNESS = 2.0f;

    // Random number generater seeded with std::random_device
    static std::mt19937 RAND_GEN;


    // constructors
    GameLife() = default;
    GameLife(int rows, int cols, int numCells);

    // destructor
    ~GameLife();

    void initRandom(int min = 0, int max = 1);
    void setInitialPattern();


    void nextGeneration(void);

    void draw(sf::RenderWindow& window);

    // overloaded operators
    friend std::ostream& operator << (std::ostream& os, const GameLife& obj);
    
    private:

    int m_rows;
    int m_cols;
    int m_num_cells;
    int m_cell_size;
    std::vector<std::vector<int>> m_grid;

    int countLiveNeighbors(int row, int col);

    
};


#endif