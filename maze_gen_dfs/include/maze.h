#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <random>
#include <vector>
#include <SFML/Graphics.hpp>

#define RIGHT_WALL 1
#define DOWN_WALL  0

enum DIRECTION {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

struct Location{
    int row;
    int col;
    Location(int r, int c) : row(r), col(c) {}
};

struct Neighbor{
    Location location;
    DIRECTION direction;

    Neighbor(int r, int c, DIRECTION d) : location(r, c), direction(d) {}
};

struct Cell{
    float x;
    float y;
    int rightWall;
    int downWall;
    bool visited;

    Cell(): x(0.0f), y(0.0f), rightWall(0), downWall(0), visited(false) {}
    Cell(float x, float y) : x(x), y(y), rightWall(0), downWall(0), visited(false) {}
    Cell(float x, float y, int right, int down) :
        x(x), y(y), rightWall(right), downWall(down), visited(false) {}
};

class Maze{

public:
    Maze();
    Maze(int rows, int cols, int margin, float cellSize);

    // copy constructor 
    Maze(const Maze& obj);
    
    // copy assignment
    Maze& operator= (const Maze& obj);

    ~Maze();

    void draw(sf::RenderWindow& window);

    void generate(void);

    friend std::ostream& operator << (std::ostream& os, const Maze& obj);

private:
    int m_rows;
    int m_cols;
    float m_margin;
    float m_cellSize;
  
    std::random_device m_rand_device;
    std::mt19937 m_rand_engine;
    std::uniform_int_distribution<int> m_row_distribution; 
    std::uniform_int_distribution<int> m_col_distribution;


    std::vector<Cell> m_grid;

    int  calcIndex(int row, int col);
    void gridInit();
    bool inbounds(int r, int c);
    void getUnvisitedNeighbors(int row, int col, std::vector<Neighbor>& unvisited);
};

#endif 