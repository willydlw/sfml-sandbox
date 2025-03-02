#include "gameLife.hpp"

// Define Class Constants
const sf::Color GameLife::ALIVE_COLOR(sf::Color::White);
const sf::Color GameLife::DEAD_COLOR (sf::Color{128, 128, 128});
const sf::Color GameLife::TEST_COLOR(sf::Color{0, 159, 74});        // green
const sf::Color GameLife::NEIGHBOR_COLOR(sf::Color{255, 92, 0});    // orange

// Random Number Generator
std::mt19937 GameLife::RAND_GEN(std::random_device{}());


// Constructor
GameLife::GameLife(int rows, int cols, int cellSize) : 
                    m_rows(rows), 
                    m_cols(cols), 
                    m_cell_size(cellSize),
                    m_grid(rows, std::vector<int>(cols, 0)) {}


// Destructor
GameLife::~GameLife()
{
    std::cerr << __func__ << " bye-bye\n";
}


// accessor functions
int GameLife::getCellState (int row, int col) const 
{
    return m_grid[row][col];
}

int GameLife::getRows() const {return m_rows;}
int GameLife::getCols() const {return m_cols;}
int GameLife::getCellSize() const {return m_cell_size;}


void GameLife::setCellState(int row, int col, int state)
{
    m_grid[row][col] = state;
}

// Fill array with randomly generatred 1's and 0's
void GameLife::initRandom(int min, int max)
{
    // Uniform distribution for integers between min and max (inclusive)
    std::uniform_int_distribution<int> RAND_DIST01(min, max);

    for(int r = 0; r < m_rows; r++){
        for(int c = 0; c < m_cols; c++){
            m_grid[r][c] = RAND_DIST01(RAND_GEN);
        }
    }
}


void GameLife::setInitialPattern(const std::vector<Location>& aliveLocations)
{
    for(auto loc : aliveLocations)
    {
        m_grid[loc.row][loc.col] = GameLife::ALIVE;
    }
}


void GameLife::nextGeneration(void)
{
    std::vector<std::vector<int>> nextGen(m_rows, std::vector<int>(m_cols));
    for(int r = 0; r < m_rows; r++)
    {
        for(int c = 0; c < m_cols; c++)
        {
            int liveNeighbors = countLiveNeighbors(r, c);

            // Any live cell with fewer than two live neighbours dies, as if by underpopulation.
            // Any live cell with more than three live neighbours dies, as if by overpopulation.
            if(m_grid[r][c] == ALIVE)
            {
                if(liveNeighbors < 2 || liveNeighbors > 3){
                    nextGen[r][c] = DEAD;
                }
                else{ // Any live cell with two or three live neighbours lives on to the next generation.
                    nextGen[r][c] = ALIVE;
                }
            }
            else { // m_grid[r][c] = DEAD
                // Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
                if(liveNeighbors == 3){
                    nextGen[r][c] = ALIVE;
                }
                else{
                    nextGen[r][c] = DEAD;
                }
            }   
        }
    }

    m_grid = nextGen;
}

/*  For neighbors on the grid edges, we will wrap around and 
    consider the neighbor on the opposite edge.

    Example: current cell column is 0. East neighbor is one column
    to the left, which is -1, an invalid index and non-existant neighbor.
    The neighbor then is located in the rightmost grid column, index m_cols - 1. 

    We calculate this as follows: (c - 1 + m_cols) % m_cols 
    If m_cols = 10 and c = 0, then (0 - 1 + 10) % 10 = 9 which is m_cols - 1. 

    Similarly, to wrap around for the zero row: 

    r = 0, m_rows = 10, the row above ( r - 1 + m_rows) % m_rows = 9 which is 
    the index for the last row.
    
*/
int GameLife::countLiveNeighbors(int row, int col)
{
    int liveCount = 0;

    for(int i = 0; i < NUM_NEIGHBORS; i++)
    {
        Location neighbor = calcNeighborLocation(row, col, DR[i], DC[i]);
        if(m_grid[neighbor.row][neighbor.col] == ALIVE)
        {
                liveCount++;
        }
    }

    return liveCount;
}

Location GameLife::calcNeighborLocation(int row, int col, int rowOffset, int colOffset)
{
    Location neighbor;
    neighbor.row = (row + rowOffset + m_rows) % m_rows;
    neighbor.col = (col + colOffset + m_cols) % m_cols;
    return neighbor;
}

// returns list of all neighbor locations
std::vector<Location> GameLife::getNeighborList(int row, int col)
{
    std::vector<Location> neighbors(NUM_NEIGHBORS);

    for(int i = 0; i < NUM_NEIGHBORS; i++)
    {
        Location loc = calcNeighborLocation(row, col, GameLife::DR[i], GameLife::DC[i]);
        neighbors[i] = loc;
    }

    return neighbors;
}



void GameLife::draw(sf::RenderWindow& window)
{
    sf::RectangleShape rect(sf::Vector2f{static_cast<float>(m_cell_size - GameLife::OUTLINE_THICKNESS), 
            static_cast<float>(m_cell_size - GameLife::OUTLINE_THICKNESS)});

    for(int r = 0; r < m_rows; r++)
    {
        for(int c = 0; c < m_cols; c++)
        {
            
            if(m_grid[r][c] == GameLife::ALIVE)
            {
                rect.setFillColor(sf::Color::White);
                rect.setPosition(sf::Vector2f{static_cast<float>(c * m_cell_size), static_cast<float>(r * m_cell_size)});
                rect.setOutlineColor(sf::Color::Black);
                rect.setOutlineThickness(GameLife::OUTLINE_THICKNESS);
                window.draw(rect);
            }
        }
    }
}

void GameLife::drawNeighbors(sf::RenderWindow& window, const Location& centerCell, 
    const std::vector<Location>& neighbors)
{
    sf::RectangleShape rect(sf::Vector2f{static_cast<float>(m_cell_size - GameLife::OUTLINE_THICKNESS), 
        static_cast<float>(m_cell_size - GameLife::OUTLINE_THICKNESS)});

    rect.setFillColor(GameLife::TEST_COLOR);
    sf::Vector2f position{static_cast<float>(centerCell.col * m_cell_size), 
                static_cast<float>(centerCell.row * m_cell_size)};
    rect.setPosition(position);
    rect.setOutlineColor(sf::Color::Black);
    rect.setOutlineThickness(GameLife::OUTLINE_THICKNESS);
    window.draw(rect);

    rect.setFillColor(GameLife::NEIGHBOR_COLOR);

    for(auto n : neighbors)
    {             
        rect.setPosition(sf::Vector2f{static_cast<float>(n.col * m_cell_size), static_cast<float>(n.row * m_cell_size)});
        rect.setOutlineColor(sf::Color::Black);
        rect.setOutlineThickness(GameLife::OUTLINE_THICKNESS);
        window.draw(rect);
    }
}

std::ostream& operator << (std::ostream& os, const GameLife& obj)
{
    os  << "\nrows: " << obj.m_rows << ", cols: " << obj.m_cols 
        << ", cell size: " << obj.m_cell_size 
        << "\nCell States\n";

    #if 0
    for(int r = 0; r < obj.m_rows; r++){
        for(int c = 0; c < obj.m_cols; c++){
            os << obj.m_grid[r][c] << " ";
        }
        os << "\n";
    }
    #endif

    return os;
}