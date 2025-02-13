#include "maze.h"

// Default constructor
Maze::Maze() : m_rows(0), m_cols(0), m_cellSize(0)
{

}

// Constructor
Maze::Maze(int rows, int cols, float cellSize) : m_rows(rows),
    m_cols(cols), m_cellSize(cellSize)
{
    m_grid = std::vector<Cell>(m_rows * m_cols);
    gridInit();
}

// copy constructor
Maze::Maze(const Maze& obj)
{
    this->m_rows = obj.m_rows;
    this->m_cols = obj.m_cols;
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

#if 0
Maze& Maze::operator= (Maze&& obj) noexcept
{
    if(this == &obj){
        return *this;
    }
}

#endif 


void Maze::gridInit(void)
{
    for(int r = 0; r < m_rows; r++){
        for(int c = 0; c < m_cols; c++){
            float x = c * m_cellSize;
            float y = r * m_cellSize;
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


void Maze::draw(sf::RenderWindow& window)
{
    sf::RectangleShape rect(sf::Vector2f{m_cellSize, m_cellSize});
    rect.setFillColor(sf::Color::White);
    rect.setOutlineColor(sf::Color::Green);
    rect.setOutlineThickness(4);

    static int count = 0;

    for(int r = 0; r < m_rows; r++){
        for(int c = 0; c < m_cols; c++){
            int idx = r * m_cols + c;
            if(count < 4){
            std::cout << "idx: " << idx << ", x: " << m_grid[idx].x 

            << ", y: " << m_grid[idx].y << "\n";

            count++;
            }
            rect.setPosition({m_grid[idx].x, m_grid[idx].y});
            window.draw(rect);
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
