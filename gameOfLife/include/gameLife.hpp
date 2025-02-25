#ifndef GAMELIFE_HPP
#define GAMELIFE_HPP

#include <vector>

class GameLife{
    public:

    static constexpr int DEAD = 0;
    static constexpr int ALIVE = 1;

    GameLife(int rows, int cols);

    void setInitialPattern();

    void nextGeneration(void);
    
    private:

    int m_rows;
    int m_cols;
    std::vector<std::vector<int>> m_grid;

    int countLiveNeighbors(int row, int col);
    
};


#endif