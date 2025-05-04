#ifndef GAME_OF_LIFE
#define GAME_OF_LIFE

#include "raylib.h"

#include <utility>

#include <list>

class GameOfLife
{
private:
    int height;
    int width;
    
    int offset;

    int cellSize;

    char **Map; // Map of Cells [dynamic array]

    int cellsAlive = 0;

    void ProcedureCell(int posX, int posY);

    std::list<std::pair<int, int> > BornCells;
    std::list<std::pair<int, int> > DiedCells;

    double time = 0;

public:
    GameOfLife(int height, int width, int offset, int size=25);

    ~GameOfLife();

    void Update(double time);

    void Draw();

    int AliveCellsCount();

    void ResetMap();

    int GetCellSize();

    void SetRandomCells(int count);

    bool isRunning = false;
    
    float SimDelay = 0.500f;
};



#endif