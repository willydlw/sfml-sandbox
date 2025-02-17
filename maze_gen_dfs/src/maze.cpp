#include "maze.h"

#include <stack>
#include <algorithm>

std::random_device Maze::rand_device;

// rand_device() generates random number to seed the engine
std::mt19937 Maze::rand_engine(Maze::rand_device());

// Constructor
Maze::Maze(int rows, int cols, int margin, float cellSize) : m_rows(rows),
    m_cols(cols), m_margin(margin), m_cellSize(cellSize)
{
    m_grid = std::vector<Cell>(m_rows * m_cols);
    gridInit();
}

// copy constructor
Maze::Maze(const Maze& obj)
{
    m_rows = obj.m_rows;
    m_cols = obj.m_cols;
    m_margin = obj.m_margin;
    m_cellSize = obj.m_cellSize;


    int numCells = m_rows * m_cols;
    m_grid = std::vector<Cell>(numCells);

    // perform deep copy
    for(int i = 0; i < numCells; i++){
        m_grid[i] = obj.m_grid[i];
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

/*
Iterative implementation: https://en.wikipedia.org/wiki/Maze_generation_algorithm

Choose the initial cell, mark it as visited and push it to the stack
While the stack is not empty
    Pop a cell from the stack and make it a current cell
    If the current cell has any neighbours which have not been visited
        Push the current cell to the stack
        Choose one of the unvisited neighbours
        Remove the wall between the current cell and the chosen cell
        Mark the chosen cell as visited and push it to the stack
*/

void Maze::generate(void)
{
    // Local variables
    std::stack<SearchInfo> searchStack;

    // choose the initial cell
    Location startLocation = selectInitialLocation();
    int idx = calcIndex(startLocation);

    SearchInfo current = {.cellptr = &m_grid[idx], .location = startLocation};

    // mark initial cell as visited and push it to the stack
    current.cellptr->visited = true;
    searchStack.push(current);

    // while stack is not empty
    while(!searchStack.empty()){
        // pop a cell from the stack and mark it as current
        current = searchStack.top();
        searchStack.pop();

        // If the current cell has any neighbours which have not been visited
        std::vector<Neighbor> unvisited;
        getUnvisitedNeighbors(current.location, unvisited);

        if(unvisited.size() > 0){
            // Choose one of the unvisited neighbours
            std::uniform_int_distribution<int> chosen_distribution(0, unvisited.size());
            int ci = chosen_distribution(Maze::rand_engine);
            Neighbor chosen = unvisited[ci];

            Cell* chosenCell = &m_grid[chosen.location.row * m_cols + chosen.location.col];
            
            // Remove walls between current and chosen neighbor 
            switch(chosen.direction){
                case LEFT:
                    chosenCell->rightWall = false;
                break;
                case RIGHT:
                    current.cellptr->rightWall = false;
                break;
                case UP:
                    chosenCell->downWall = false;
                break;
                case DOWN:
                    current.cellptr->downWall = false;
                break;
            }

            //  Mark the chosen cell as visited and push it to the stack
            chosenCell->visited = true;
            searchStack.push(SearchInfo{.cellptr = chosenCell, .location = chosen.location});
        }
    }
}

Location Maze::selectInitialLocation()
{
    std::uniform_int_distribution<int> row_distribution(0, m_rows);
    std::uniform_int_distribution<int> col_distribution(0, m_cols);

    int row = row_distribution(Maze::rand_engine);
    int col = col_distribution(Maze::rand_engine);

    return Location(row, col);
}

void Maze::getUnvisitedNeighbors(Location location, std::vector<Neighbor>& unvisited)
{
    // left, right, up, down
    const int dx[4] = {-1,  1, 0,  0};
    const int dy[4] = { 0,  0, -1, 1};

    // randomize neighbor selection order
    int ri[4] = {0, 1, 2, 3};
   
    for(int i = 0; i < 4; i++){
        int r = location.row + dy[ri[i]];
        int c = location.col + dx[ri[i]];
        if(inbounds(r, c)){
            if(!m_grid[calcIndex(r,c)].visited){
                unvisited.push_back(Neighbor(r,c, static_cast<DIRECTION>(i)));
            }
        }
    }
}

int  Maze::calcIndex(int row, int col)
{
    return row * m_cols + col;
}

int Maze::calcIndex(Location loc)
{
    return loc.row * m_cols + loc.col;
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
