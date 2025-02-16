#include "maze.h"

#include <stack>

// Default constructor
Maze::Maze() : m_rows(0), m_cols(0), m_margin(0), m_cellSize(0),
    m_rand_engine(std::random_device{}())
{

}

// Constructor
Maze::Maze(int rows, int cols, int margin, float cellSize) : m_rows(rows),
    m_cols(cols), m_margin(margin), m_cellSize(cellSize),
    m_rand_engine(std::random_device{}()), m_row_distribution(0,rows-1),
    m_col_distribution(0,cols-1)
{
    m_grid = std::vector<Cell>(m_rows * m_cols);
    gridInit();
}

// copy constructor
Maze::Maze(const Maze& obj)
{
    this->m_rows = obj.m_rows;
    this->m_cols = obj.m_cols;
    this->m_margin = obj.m_margin;
    this->m_cellSize = obj.m_cellSize;
    m_grid = std::vector<Cell>(m_rows * m_cols);

    // perform deep copy
    for(int r = 0; r < m_rows; r++){
        for(int c = 0; c < m_cols; c++){
            m_grid[r*m_cols + c] = obj.m_grid[m_rows * m_cols];
        }
    }
}


// copy assignment 
Maze& Maze::operator= (const Maze& obj)
{
    if(this == &obj)
    {
        return *this;
    }

    if(m_grid.size() != obj.m_grid.size())
    {
        m_grid.resize(obj.m_rows * obj.m_cols);
    }

    m_rows = obj.m_rows;
    m_cols = obj.m_cols;
    m_cellSize = obj.m_cellSize;

    int n = m_rows * m_cols;
    for(int i = 0; i < n; i++){
        m_grid[i] = obj.m_grid[i];
    }

    return *this;
}


void Maze::gridInit(void)
{
    for(int r = 0; r < m_rows; r++){
        for(int c = 0; c < m_cols; c++){
            float x = c * m_cellSize + m_margin;
            float y = r * m_cellSize + m_margin;
            m_grid[r * m_cols + c] = Cell (x, y, 1, 1);
            std::cout << "[" << r << "][" 
                    << c << "] x: " 
                    << x << ", y: " << y << "\n";
        }
    }
}


Maze::~Maze()
{
    std::cerr << "~Maze bye bye\n";
}

Iterative implementation: https://en.wikipedia.org/wiki/Maze_generation_algorithm

Choose the initial cell, mark it as visited and push it to the stack
While the stack is not empty
Pop a cell from the stack and make it a current cell
If the current cell has any neighbours which have not been visited
Push the current cell to the stack
Choose one of the unvisited neighbours
Remove the wall between the current cell and the chosen cell
Mark the chosen cell as visited and push it to the stack


void Maze::generate(void)
{
    std::uniform_int_distribution<int> row_distribution(0, m_rows);
    std::stack<Cell> cellStack;
    int row = m_row_distribution(m_rand_engine);
    int col = m_col_distribution(m_rand_engine);
    Cell& current = m_grid[row * m_cols + col];
    current.visited = true;
    cellStack.push(current);
    while(!cellStack.empty()){
        current = cellStack.top();
        cellStack.pop();
        std::vector<Cell> unvisited;

        Correction required: choose one of the unvisited neighbors 
        getUnvisitedNeighborList(row, col, unvisited);
        for(auto u : unvisited){
            cellStack.push(u);
        }

        Remove walls between current and chosen neighbor 

    }
    
}

void Maze::getUnvisitedNeighborList(int row, int col, std::vector<Cell>& unvisited)
{
    // above, left, right, below
    const int dx[4] = {0, -1, 1, 0};
    const int dy[4] = {-1, 0, 0, 1};

    // randomize neighbor selection order
    int ri[4] = {0, 1, 2, 3};
    std::shuffle(ri, ri + 4, m_rand_engine);

    for(int i = 0; i < 4; i++){
        int r = row + dy[ri[i]];
        int c = col + dx[ri[i]];
        if(inbounds(r, c)){
            if(!m_grid[r * m_cols + c].visited){
                unvisited.push_back(m_grid[r * m_cols + c]);
            }
        }
    }
}

bool Maze::inbounds(int r, int c)
{
    return r >= 0 && r < m_rows && c >= 0 && c < m_cols;
}


void Maze::draw(sf::RenderWindow& window)
{
    /*sf::RectangleShape rect(sf::Vector2f{m_cellSize, m_cellSize});
    rect.setFillColor(sf::Color::White);
    rect.setOutlineColor(sf::Color::Green);
    rect.setOutlineThickness(4);
    */

    sf::RectangleShape rightWallLine(sf::Vector2f{m_margin, m_cellSize});
    rightWallLine.setFillColor(sf::Color::White);

    sf::RectangleShape downWallLine(sf::Vector2f{m_cellSize, m_margin});
    downWallLine.setFillColor(sf::Color::White);


    static int count = 0;

    for(int r = 0; r < m_rows; r++){
        for(int c = 0; c < m_cols; c++){
            int idx = r * m_cols + c;
            if(count < 4){
            std::cout << "idx: " << idx << ", x: " << m_grid[idx].x 

            << ", y: " << m_grid[idx].y << "\n";

            count++;
            }

            Cell cell = m_grid[idx];

            if(cell.rightWall){
                rightWallLine.setPosition(sf::Vector2f{cell.x + m_cellSize, 
                    cell.y});
                window.draw(rightWallLine);
            }

            if(cell.downWall){
                downWallLine.setPosition(sf::Vector2f{cell.x, cell.y + m_cellSize});
                window.draw(downWallLine);
            }
            //rect.setPosition({m_grid[idx].x, m_grid[idx].y});
            //window.draw(rect);
        }
    }
}

std::ostream& operator << (std::ostream& os, const Maze& obj)
{
    os  << "rows: " << obj.m_rows 
        << ", cols: " << obj.m_cols
        << "\n";
    return os;
}
