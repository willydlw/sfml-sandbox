#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#define RIGHT_WALL 1
#define DOWN_WALL  0

struct Cell{
    float x;
    float y;
    int rightWall;
    int downWall;

    Cell(): x(0.0f), y(0.0f), rightWall(0), downWall(0) {}
    Cell(float x, float y) : x(x), y(y), rightWall(0), downWall(0) {}
    Cell(float x, float y, int right, int down) :
        x(x), y(y), rightWall(right), downWall(down) {}
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

    friend std::ostream& operator << (std::ostream& os, const Maze& obj);

private:
    int m_rows;
    int m_cols;
    int m_margin;
    float m_cellSize;
    std::vector<Cell> m_grid;

    void gridInit();
};


void drawMaze(sf::RenderWindow& window);

#endif 