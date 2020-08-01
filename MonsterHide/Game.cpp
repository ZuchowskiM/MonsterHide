#include "Game.h"

Game::Game()
{
	gridSizeX = 60;
	gridSizeY = 60;

	grid = new States*[gridSizeX];

	for (int i = 0; i < gridSizeX; i++)
	{
		grid[i] = new States[gridSizeY];
	}

	for (int i = 0; i < gridSizeX; i++)
	{
		for (int j = 0; j < gridSizeY; j++)
		{
			grid[i][j] = States::Clear;
		}
	}

	grid[2][3] = States::Obstacle;
	grid[3][3] = States::Obstacle;
	grid[4][3] = States::Obstacle;
	grid[5][3] = States::Obstacle;

	grid[54][55] = States::Obstacle;
	grid[55][55] = States::Obstacle;
	grid[56][55] = States::Obstacle;
	grid[57][55] = States::Obstacle;

	player.place(49, 29);
	monster.place(9, 29);

	movesCount = 0;
	diamondsCount = 0;

	//here create pathfinder points list TODO

}

Game::~Game()
{
	for (int i = 0; i < gridSizeX; i++)
	{
		delete[] grid[i];
	}
	delete[] grid;
}

void Game::Analize()
{
	//TODO
}