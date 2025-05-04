#include "GameLife.h"

GameOfLife::GameOfLife(int height, int width, int offset, int size)
{
	//	Init vars
	this->offset = offset;
	this->cellSize = size;

	this->height = height / this->cellSize;
	this->width = width/ this->cellSize;

	//	Init map
	this->Map = new char*[this->height];

	for (int i = 0; i < this->height; i++)
	{
		this->Map[i] = new char[this->width];
	}


	this->ResetMap();
	this->SetRandomCells(150);
}

GameOfLife::~GameOfLife()
{
	//	Delete dynamic data

	for (int i = 0; i < this->height; i++)
	{
		delete[] this->Map[i];
	}

	delete[] this->Map;

}

void GameOfLife::ResetMap()
{
	this->cellsAlive = 0;

	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			this->Map[i][j] = ' ';
		}
	}

}

void GameOfLife::SetRandomCells(int count)
{
	this->ResetMap();

	//	Set some cells
	for (int i = 0; i < count; i++)
	{
		int posY = GetRandomValue(0, this->height - 1);
		int posX = GetRandomValue(0, this->width - 1);

		if (this->Map[posY][posX] == ' ')
		{
			this->Map[posY][posX] = '#';
			this->cellsAlive++;
		}
	}

}

void GameOfLife::Draw()
{
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			if (this->Map[i][j] == '#')
			{
				DrawRectangle(this->cellSize * j + this->offset, this->cellSize * i, this->cellSize, this->cellSize, BLACK);
			}
			else
			{
				DrawLine(	
					this->cellSize * j + this->offset, 
					this->cellSize * i, 
					this->cellSize * j + this->offset + this->cellSize, 
					this->cellSize * i, 
					GRAY
				);

				DrawLine(
					this->cellSize * j + this->offset,
					this->cellSize * i + this->cellSize,
					this->cellSize * j + this->offset + this->cellSize,
					this->cellSize * i + this->cellSize,
					GRAY
				);

				DrawLine(
					this->cellSize * j + this->offset,
					this->cellSize * i,
					this->cellSize * j + this->offset,
					this->cellSize * i + this->cellSize,
					GRAY
				);

				DrawLine(
					this->cellSize * j + this->offset + this->cellSize,
					this->cellSize * i,
					this->cellSize * j + this->offset + this->cellSize,
					this->cellSize * i + this->cellSize,
					GRAY
				);
				

			}

		}
	}
}

void GameOfLife::Update(double time)
{
	if (this->isRunning == false) 
		return;

	if (time - this->time <= this->SimDelay)
		return;

	this->time = time;

	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			this->ProcedureCell(i, j);
		}
	}

	//	Remove died
	for (auto it = this->DiedCells.begin(); it != this->DiedCells.end(); it++)
	{
		this->Map[it->first][it->second] = ' ';
	}

	//	Add born
	for (auto it = this->BornCells.begin(); it != this->BornCells.end(); it++)
	{
		this->Map[it->first][it->second] = '#';
	}

	//	Clear lists
	this->cellsAlive = this->cellsAlive + (this->BornCells.size() - this->DiedCells.size());

	this->DiedCells.clear();
	this->BornCells.clear();
}

void GameOfLife::ProcedureCell(int posY, int posX)
{
	int neigCells = 0;

	for (int i = posY - 1; i < posY + 2; i++)
	{
		for (int j = posX - 1; j < posX + 2; j++)
		{

			if (i < 0 || i >= this->height)
				continue;

			if (j < 0 || j >= this->width)
				continue;

			if (j == posX && i == posY)
				continue;

			if(this->Map[i][j] == '#')
				neigCells++;

		}
	}

	
	//	Birth
	if (this->Map[posY][posX] == ' ' && neigCells == 3)
	{
		this->BornCells.push_back({posY, posX});
	}
	//	Alone death
	else if (this->Map[posY][posX] == '#' && neigCells < 2)
	{
		this->DiedCells.push_back({ posY, posX });
	}
	//	Population density death
	else if (this->Map[posY][posX] == '#' && neigCells > 3)
	{
		this->DiedCells.push_back({ posY, posX });
	}
	//	Survive
	//	Just leave alive if 2 or 3 neigbours cells
}

int GameOfLife::AliveCellsCount()
{
	return this->cellsAlive;
}


int GameOfLife::GetCellSize()
{
	return this->cellSize;
}
