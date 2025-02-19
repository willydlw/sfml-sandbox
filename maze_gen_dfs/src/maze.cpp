#include "maze.h"

#include <algorithm>

// rand_device() generates random number to seed the engine
std::random_device Maze::rand_device;
std::mt19937 Maze::rand_engine(Maze::rand_device());


// Constructor
Maze::Maze(int rows, int cols, int margin, float cellSize) : m_rows(rows),
    m_cols(cols), m_margin(margin), m_cellSize(cellSize), m_state(Maze::GenerateState::START)
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
    m_state = Maze::GenerateState::START;

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
            m_grid[r * m_cols + c] = Cell (x, y);
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
    static std::stack<SearchInfo> searchStack;

    switch(m_state)
    {
        case START:
            startGeneration(searchStack);
            m_state = ANIMATE;
        break;

        case ANIMATE:
            if(!searchStack.empty()){
                animateGeneration(searchStack);
            }
            else{
                m_state = COMPLETE;
            }
        break;
        case COMPLETE:
        break;
    }
}

void Maze::startGeneration(std::stack<SearchInfo>& searchStack)
{
    // choose the initial cell
    Location startLocation = {0,0}; //selectInitialLocation();
    int idx = 0; //calcIndex(startLocation);

    SearchInfo current = {.cellptr = &m_grid[idx], .location = startLocation};

    // mark initial cell as visited and push it to the stack
    current.cellptr->visited = true;
    current.cellptr->color = Maze::START_COLOR;
    searchStack.push(current);

    std::cerr << __func__ << ", startLocation row: " << startLocation.row 
        << ", col: " << startLocation.col << "\n";
    std::cerr << "start cell " << *current.cellptr << "\n";
}

Location Maze::selectInitialLocation()
{
    std::uniform_int_distribution<int> row_distribution(0, m_rows);
    std::uniform_int_distribution<int> col_distribution(0, m_cols);

    int row = row_distribution(Maze::rand_engine);
    int col = col_distribution(Maze::rand_engine);

    return Location(row, col);
}

// Function should only be called when the search stack is not empty
void Maze::animateGeneration(std::stack<SearchInfo>& searchStack)
{   
    std::cerr << "\n" << __func__ << ", stack size: " << searchStack.size() << "\n";
    // pop a cell from the stack and mark it as current
    SearchInfo current = searchStack.top();
    searchStack.pop();

    current.cellptr->color = Maze::CURRENT_COLOR;

    std::cerr << "Current cell: " << *current.cellptr;
    std::cerr << "current location row: " << current.location.row 
        << ", col: " << current.location.col << "\n\n";

    // If the current cell has any neighbours which have not been visited
    std::vector<Neighbor> unvisited;
    getUnvisitedNeighbors(current.location, unvisited);

    std::cerr << "unvisited.size: " << unvisited.size() << "\n";
    
    if(unvisited.size() > 0){
        // Randomly choose one of the unvisited neighbours
        std::uniform_int_distribution<int> chosen_distribution(0, unvisited.size());
        int ci = chosen_distribution(Maze::rand_engine);
        Neighbor chosen = unvisited[ci];

        std::cerr << "Chosen neighbor location, row: " << chosen.location.row 
            << ", col: " << chosen.location.col 
            << ", direction: " << chosen.direction << "\n";

        ci = calcIndex(chosen.location.row, chosen.location.col);
        Cell* chosenCell = &m_grid[ci];
        chosenCell->color = Maze::CHOSEN_COLOR;
        
        // Remove walls between current and chosen neighbor 
        switch(chosen.direction){
            case LEFT:
                std::cerr << "chosen neighbor to LEFT of current, remove chosen's right wall\n";
                chosenCell->rightWall = false;
            break;
            case RIGHT:
                std::cerr << "chosen neighbor to RIGHT of current, remove current's right wall\n";
                current.cellptr->rightWall = false;
            break;
            case UP:
                std::cerr << "chosen neighbor to UP of current, remove chosen's down wall\n";
                chosenCell->downWall = false;
            break;
            case DOWN:
                std::cerr << "chosen neighbor to DOWN of current, remove current's down wall\n";
                current.cellptr->downWall = false;
            break;
            default:
                std::cerr << "ERROR, " << __func__ << ", unknown direction: " << chosen.direction << "\n";
                exit(EXIT_FAILURE);
        }

        //  Mark the chosen cell as visited and push it to the stack
        chosenCell->visited = true;
        searchStack.push(SearchInfo{.cellptr = chosenCell, .location = chosen.location});
    }
}

void Maze::getUnvisitedNeighbors(Location location, std::vector<Neighbor>& unvisited)
{
    // left, right, up, down
    const int dx[4] = {-1,  1, 0,  0};
    const int dy[4] = { 0,  0, -1, 1};

    if(location.row >= m_rows || location.row < 0 || location.col < 0 || location.col >= m_cols)
    {
        std::cerr << "ERROR, " << __func__ << ", invalid location. row: " << location.row 
        << ", col: " << location.col << "\n";
        exit(EXIT_FAILURE);
    }
   
    for(int i = 0; i < 4; i++){
        int r = location.row + dy[i];
        int c = location.col + dx[i];
        std::cerr << __func__ <<  ", location.row: " << location.row << ", location.col: " << location.col 
        << ", r: " << r << ", c: " << c << ", direction: " << i << "\n";
        if(inbounds(r, c)){
            if(!m_grid[calcIndex(r,c)].visited){
                Neighbor nb(Location(r,c),i);
                unvisited.push_back(nb);
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

    sf::RectangleShape rightWallLine(sf::Vector2f{(float)m_margin, (float)m_cellSize});
    rightWallLine.setFillColor(sf::Color::White);

    sf::RectangleShape downWallLine(sf::Vector2f{(float)m_cellSize, (float)m_margin});
    downWallLine.setFillColor(sf::Color::White);

    sf::RectangleShape inner(sf::Vector2f{m_cellSize - 2.0f * m_margin, 
                            m_cellSize - 2.0f * m_margin});

    for(int r = 0; r < m_rows; r++){
        for(int c = 0; c < m_cols; c++){
            int idx = r * m_cols + c;
            Cell cell = m_grid[idx];

            inner.setPosition(sf::Vector2f{(float)(cell.x + m_margin), (float)(cell.y + m_margin)});
            inner.setFillColor(cell.color);
            window.draw(inner);

            if(cell.rightWall){
                rightWallLine.setPosition(sf::Vector2f{(float)(cell.x + m_cellSize), 
                    (float)cell.y});
                window.draw(rightWallLine);
            }

            if(cell.downWall){
                downWallLine.setPosition(sf::Vector2f{(float)cell.x, (float)(cell.y + m_cellSize)});
                window.draw(downWallLine);
            }
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
