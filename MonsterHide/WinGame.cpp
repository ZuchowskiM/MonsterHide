#include "WinGame.h"
#include<iostream>

using std::cout;

WinGame::WinGame(): Game()
{
	//EMPTY
}

WinGame::~WinGame()
{
	//EMPTY
}

void WinGame::show()
{
	Analize();

	for (int i = 0; i < 60; i++)
	{
		for (int j = 0; j < 60; j++)
		{
			if (grid[i][j] == States::Player)
			{
				cout << "P";
			}
			else if (grid[i][j] == States::Monster)
			{
				cout << "M";
			}
			else if (grid[i][j] == States::Diamond)
			{
				cout << "^";
			}
			else if (grid[i][j] == States::Clear)
			{
				cout << " ";
			}
			else if (grid[i][j] == States::Obstacle)
			{
				cout << "#";
			}
			else if (grid[i][j] == States::Watched)
			{
				cout << "!";
			}
		}
		cout << std::endl;

	}
}
