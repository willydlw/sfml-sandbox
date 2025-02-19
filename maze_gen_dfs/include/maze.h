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
    bool rightWall;
    bool downWall;
    bool visited;
    sf::Color color;

    Cell(float x = 0.0f, float y = 0.0f) : x(x), y(y), rightWall(true), 
            downWall(true), visited(false), color(sf::Color::Black) {}
    Cell(float x, float y, bool right, bool down) :
        x(x), y(y), rightWall(right), downWall(down), visited(false) {}

    friend std::ostream& operator << (std::ostream& os, Cell& obj)
    {
        os << "x: " << obj.x << ", y: " << obj.y  
            << ", rightWall: " << (obj.rightWall ? "true" : "false")
            << ", downWall: " << (obj.downWall? "true" : "false")
             << ", visited: " << (obj.visited ? "true" : "false")
             << "\n"; 

        return os;
    }
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

    // cell state colors
    static constexpr sf::Color START_COLOR {sf::Color{11, 102, 35}};
    static constexpr sf::Color CURRENT_COLOR {sf::Color{255, 116, 23}};
    static constexpr sf::Color VISITED_COLOR {sf::Color::Red};
    static constexpr sf::Color STACK_COLOR {sf::Color{48, 148, 129}};

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