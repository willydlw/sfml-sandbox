#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <random>
#include <vector>
#include <SFML/Graphics.hpp>


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

    Cell(float x = 0.0f, float y = 0.0f) : x(x), y(y), rightWall(1), downWall(1), visited(false) {}
    Cell(float x, float y, int right, int down) :
        x(x), y(y), rightWall(right), downWall(down), visited(false) {}
};

struct SearchInfo{
    Cell* cellptr;
    Location location;
};

class Maze{

public:
    // class constant expressions, default values
    static constexpr int DEFAULT_ROWS = 4;
    static constexpr int DEFAULT_COLS = 4;
    static constexpr int DEFAULT_MARGIN = 8;
    static constexpr float DEFAULT_CELLSIZE = 20.0f;

    // random number device and engine
    static std::random_device rand_device;
    static std::mt19937 rand_engine;

    enum GenerateState{
        START,
        ANIMATE,
        COMPLETE
    };

    // Constructor
    explicit Maze(int rows = DEFAULT_ROWS, int cols = DEFAULT_COLS, 
                    int margin = DEFAULT_MARGIN, float cellSize = DEFAULT_CELLSIZE);

    // Desctructor
    ~Maze();

    Maze::GenerateState state() {return m_state;}
    void draw(sf::RenderWindow& window);

    void generate(void);

    friend std::ostream& operator << (std::ostream& os, const Maze& obj);

private:
    int m_rows;
    int m_cols;
    float m_margin;
    float m_cellSize;
    GenerateState m_state;
  
    std::vector<Cell> m_grid;

    // Copy constructor is private
    // Data member std::random_device should not be copied
    // Making copy constructor private will prevent the compiler from generating
    // a default constructor 
    Maze(const Maze& obj);
    
    // copy assignment
    Maze& operator= (const Maze& obj);

    int  calcIndex(int row, int col);
    int  calcIndex(Location loc);
    void gridInit();
    bool inbounds(int r, int c);
    void getUnvisitedNeighbors(Location location, std::vector<Neighbor>& unvisited);

    void startGeneration(std::stack<SearchInfo>& searchStack);
    Location selectInitialLocation();

    void animateGeneration(std::stack<SearchInfo>& searchStack);
};

#endif 